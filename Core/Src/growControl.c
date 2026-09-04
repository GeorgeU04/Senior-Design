#include "growControl.h"
#include "NutrientDose.h"
#include "PHDose.h"
#include "lights.h"
#include "stm32h7xx_hal.h"
#include <stddef.h>

/* Control thresholds */
#define GROW_ENCL_HYST_C 1.5f
#define GROW_WATER_HYST_C 1.0f
#define GROW_WATER_LOW_RAW 3000U
#define GROW_CHEM_PERIOD_MS 5000U
#define GROW_CLIMATE_PERIOD_MS 1000U
#define GROW_LIGHT_PERIOD_MS 1000U
#define GROW_TANK_GALLONS 3.0f

static GrowControlState state = GROW_STATE_IDLE;
static const struct plantProfile *activePlant = NULL;
static enum growthStage activeStage = EARLY_GROWTH;
static uint8_t lightsOn = 0;

static struct fan *fanPrimary = NULL;
static struct fan *fanSecondary = NULL;
static struct cooler *reservoirCooler = NULL;
static struct heater *airHeater = NULL;
static struct TDS *tdsSensor = NULL;
static struct pH *phSensor = NULL;

static uint32_t lastClimateMs = 0;
static uint32_t lastLightMs = 0;
static uint32_t lastChemMs = 0;
static uint8_t nutrientDoseRequested = 0;

static void safeActuators(void) {
  Lights_Off();
  lightsOn = 0;
  if (fanPrimary)
    stopFan(fanPrimary);
  if (fanSecondary)
    stopFan(fanSecondary);
  if (reservoirCooler)
    turnOffCooler(reservoirCooler);
  if (airHeater)
    turnOffHeater(airHeater);
}

static void applyLightsForSample(const GrowSensorSample *sample) {
  if (!activePlant)
    return;

  uint16_t minutesOfDay =
      (uint16_t)sample->hour * 60U + (uint16_t)sample->minute;
  uint8_t shouldBeOn = minutesOfDay < activePlant->lightOnMinutes;

  if (!shouldBeOn) {
    if (lightsOn) {
      Lights_Off();
      lightsOn = 0;
    }
    return;
  }

  uint8_t blue = 0, red = 0, nir = 0;
  if (!plant_getStageLights(activePlant, activeStage, &blue, &red, &nir)) {
    Lights_Off();
    lightsOn = 0;
    return;
  }

  Lights_SetWhite(activePlant->whiteLightPercentage);
  Lights_SetBlue(blue);
  Lights_SetRed(red);
  Lights_SetNIR(nir);
  lightsOn = 1;
}

static void regulateClimate(const GrowSensorSample *sample) {
  if (!activePlant)
    return;

  /* Enclosure air: fans when hot, heater when cold */
  if (sample->enclosureTempValid) {
    float target = activePlant->enclosureTemp;
    float t = sample->enclosureTempC;

    if (t > target + GROW_ENCL_HYST_C * 2.0f) {
      if (fanPrimary)
        runFan(fanPrimary, HIGH);
      if (fanSecondary)
        runFan(fanSecondary, MED);
      if (airHeater)
        turnOffHeater(airHeater);
    } else if (t > target + GROW_ENCL_HYST_C) {
      if (fanPrimary)
        runFan(fanPrimary, MED);
      if (fanSecondary)
        runFan(fanSecondary, LOW);
      if (airHeater)
        turnOffHeater(airHeater);
    } else if (t < target - GROW_ENCL_HYST_C) {
      if (fanPrimary)
        runFan(fanPrimary, OFF);
      if (fanSecondary)
        runFan(fanSecondary, OFF);
      if (airHeater)
        turnOnHeater(airHeater);
    } else {
      /* In band — gentle airflow, heater off */
      if (fanPrimary)
        runFan(fanPrimary, LOW);
      if (fanSecondary)
        stopFan(fanSecondary);
      if (airHeater)
        turnOffHeater(airHeater);
    }
  }

  /* Reservoir: cooler when warm (matches existing demo path) */
  if (sample->waterTempValid && reservoirCooler) {
    float target = activePlant->waterTemp;
    float t = sample->waterTempC;

    if (t > target + GROW_WATER_HYST_C) {
      turnOnCooler(reservoirCooler);
    } else if (t < target - GROW_WATER_HYST_C * 0.5f) {
      turnOffCooler(reservoirCooler);
    }
  }
}

static const FeedProfile *feedForStage(enum growthStage stage) {
  if ((uint32_t)stage >= GROWTH_STAGE_COUNT)
    stage = EARLY_GROWTH;
  return &lightFeedProfile[stage];
}

static void regulateChemistry(const GrowSensorSample *sample) {
  if (!activePlant || !phSensor || !tdsSensor)
    return;

  /* Always service doser state machines */
  PHDoseUpdate();
  nutrientDoseUpdate();

  if (state == GROW_STATE_REFILL)
    return;

  const FeedProfile *feed = feedForStage(activeStage);
  float phLow = feed->targetPH - feed->phRange;
  float phHigh = feed->targetPH + feed->phRange;
  float ecLow = feed->targetEC - feed->ECRange;

  /* Prefer FeedProfile band; fall back to PHDose defaults if needed */
  if (sample->pH > 0.1f && sample->pH < 14.0f) {
    if (sample->pH < phLow || sample->pH > phHigh) {
      PHDose(phSensor);
    }
  }

  SystemState nState = getState();
  if (nState == STATE_DONE) {
    setState(STATE_IDLE);
    nutrientDoseRequested = 0;
  }

  if (!nutrientDoseRequested && nState == STATE_IDLE && sample->EC > 0.01f &&
      sample->EC < ecLow) {
    nutrientDose_loadFeed(feed, GROW_TANK_GALLONS);
    nutrientDoseRequested = 1;
  }

  if (nutrientDoseRequested && (nState == STATE_IDLE || nState == STATE_DOSE_MICRO ||
                                nState == STATE_DOSE_GROW ||
                                nState == STATE_DOSE_BLOOM)) {
    nutrientDose(tdsSensor);
  }
}

void growControl_init(struct fan *enclosureFan, struct fan *auxFan,
                      struct cooler *cooler, struct heater *heater,
                      struct TDS *tds, struct pH *ph) {
  fanPrimary = enclosureFan;
  fanSecondary = auxFan;
  reservoirCooler = cooler;
  airHeater = heater;
  tdsSensor = tds;
  phSensor = ph;
  state = GROW_STATE_IDLE;
  activePlant = NULL;
  activeStage = EARLY_GROWTH;
  lightsOn = 0;
  nutrientDoseRequested = 0;
  lastClimateMs = lastLightMs = lastChemMs = 0;
  safeActuators();
}

void growControl_setPlant(const struct plantProfile *profile) {
  activePlant = profile;
  nutrientDoseRequested = 0;
  setState(STATE_IDLE);

  if (!profile) {
    state = GROW_STATE_IDLE;
    safeActuators();
    return;
  }

  activeStage = plant_getStage(profile, 1);
  state = GROW_STATE_RUNNING;

  uint8_t blue = 0, red = 0, nir = 0;
  if (plant_getStageLights(profile, activeStage, &blue, &red, &nir)) {
    Lights_SetWhite(profile->whiteLightPercentage);
    Lights_SetBlue(blue);
    Lights_SetRed(red);
    Lights_SetNIR(nir);
    lightsOn = 1;
  }
}

void growControl_update(const GrowSensorSample *sample) {
  if (!sample)
    return;

  uint32_t now = HAL_GetTick();

  if (!activePlant) {
    state = GROW_STATE_IDLE;
    return;
  }

  activeStage = plant_getStage(activePlant, sample->growthDay);

  /* Water / sensor fault handling */
  uint8_t sensorsOk =
      sample->waterTempValid || sample->enclosureTempValid; /* at least one */
  if (!sensorsOk &&
      (now - lastClimateMs > 30000U)) { /* prolonged missing temps */
    /* Don't latch fault immediately at boot before first reading */
  }

  if (sample->waterLevelRaw < GROW_WATER_LOW_RAW) {
    if (state != GROW_STATE_REFILL) {
      state = GROW_STATE_REFILL;
      /* Pause nutrient dosing while waiting for refill */
      if (getState() != STATE_IDLE && getState() != STATE_DONE)
        ; /* let in-progress dose finish via updates */
      nutrientDoseRequested = 0;
    }
  } else if (state == GROW_STATE_REFILL || state == GROW_STATE_FAULT) {
    state = GROW_STATE_RUNNING;
  } else {
    state = GROW_STATE_RUNNING;
  }

  if (now - lastLightMs >= GROW_LIGHT_PERIOD_MS) {
    lastLightMs = now;
    applyLightsForSample(sample);
  }

  if (now - lastClimateMs >= GROW_CLIMATE_PERIOD_MS) {
    lastClimateMs = now;
    regulateClimate(sample);
  }

  if (now - lastChemMs >= GROW_CHEM_PERIOD_MS) {
    lastChemMs = now;
    regulateChemistry(sample);
  } else {
    /* Dosers still need frequent polling */
    PHDoseUpdate();
    nutrientDoseUpdate();
  }
}

GrowControlState growControl_getState(void) { return state; }

enum growthStage growControl_getStage(void) { return activeStage; }

uint8_t growControl_lightsAreOn(void) { return lightsOn; }

const struct plantProfile *growControl_getPlant(void) { return activePlant; }
