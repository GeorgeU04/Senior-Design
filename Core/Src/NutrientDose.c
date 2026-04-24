// NutrientDose.c

#include "NutrientDose.h"

struct Pump growPump = {0};
struct Pump microPump = {0};
struct Pump bloomPump = {0};

static Doser grow;
static Doser micro;
static Doser bloom;

static char msg[200];

static const float GALLONS = 0.5f; // edit this accordingly

// mL/Gal --> Specified in feed profile

static float microDosePerGallon = 3.6f;
static float growDosePerGallon = 3.4f;
static float bloomDosePerGallon = 2.6f;

static float microDose = 0.0f;
static float growDose = 0.0f;
static float bloomDose = 0.0f;

static SystemState state = STATE_IDLE;

void nutrientDose_init(struct TDS *TDSSensor) {
  microDose = GALLONS * microDosePerGallon;
  growDose = GALLONS * growDosePerGallon;
  bloomDose = GALLONS * bloomDosePerGallon;

  *TDSSensor = TDS_init("TDS Sensor");

  // change pins accordingly
  microPump = pump_init("FloraMicro", GPIOB, GPIO_PIN_1); //	D6
  growPump = pump_init("FloraGrow", GPIOB, GPIO_PIN_6);   //	D5
  bloomPump = pump_init("FloraBloom", GPIOB, GPIO_PIN_7); //	D4

  // Necessary because nutrient pumps will use an INVERTED setup. (SET == off,
  // RESET == on)
  //  If not initialized early, it the pumps will continuously run on their own
  HAL_GPIO_WritePin(microPump.GPIOx, microPump.GPIO_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(growPump.GPIOx, growPump.GPIO_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(bloomPump.GPIOx, bloomPump.GPIO_Pin, GPIO_PIN_SET);

  // edit final param (mix time) as needed
  doser_init(&grow, &growPump, 1.5, 0.5, 1000);
  doser_init(&micro, &microPump, 1.5, 0.5, 1000);
  doser_init(&bloom, &bloomPump, 1.5, 0.5, 1000);
}

void nutrientDoseUpdate() {
  doser_update_inverted(&micro);
  doser_update_inverted(&grow);
  doser_update_inverted(&bloom);
}

// Place this in main loop
void nutrientDose(struct TDS *TDSSensor) {
  switch (state) {
  case STATE_IDLE:
    // Start sequence once
    printf("Starting Micro dose...\r\n");
    doser_start(&micro, microDose);

    state = STATE_DOSE_MICRO;
    break;

  case STATE_DOSE_MICRO:
    if (!doser_isBusy(&micro)) {
      printf("Micro complete. Starting Grow...\r\n");
      doser_start(&grow, growDose);
      state = STATE_DOSE_GROW;
    }
    break;

  case STATE_DOSE_GROW:
    if (!doser_isBusy(&grow)) {
      printf("Grow complete. Starting Bloom...\r\n");
      doser_start(&bloom, bloomDose);
      state = STATE_DOSE_BLOOM;
    }
    break;

  case STATE_DOSE_BLOOM:
    if (!doser_isBusy(&bloom)) {
      printf("Bloom complete. Reading TDS...\r\n");

      // Final TDS read
      readTDS(TDSSensor);
      printf("Final TDS: %.2f\r\n", TDSSensor->TDSVal);
      state = STATE_DONE;
      printf("Reservoir nutrient balancing complete.\r\n");

      // make sure to set pins high when pumping is complete
      HAL_GPIO_WritePin(microPump.GPIOx, microPump.GPIO_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(growPump.GPIOx, growPump.GPIO_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(bloomPump.GPIOx, bloomPump.GPIO_Pin, GPIO_PIN_SET);
    }
    break;

  case STATE_DONE:
    break;
  }
}

void nutrientDose_Demo(struct TDS *TDSSensor) {
  doser_update_inverted(&micro);
  doser_update_inverted(&grow);
  doser_update_inverted(&bloom);
  switch (state) {
  case STATE_IDLE:
    // Start sequence once
    printf("Starting Micro dose...\r\n");
    doser_start(&micro, microDose);

    state = STATE_DOSE_MICRO;
    break;

  case STATE_DOSE_MICRO:
    if (!doser_isBusy(&micro)) {
      printf("Micro complete. Starting Grow...\r\n");
      doser_start(&grow, growDose);
      state = STATE_DOSE_GROW;
    }
    break;

  case STATE_DOSE_GROW:
    if (!doser_isBusy(&grow)) {
      printf("Grow complete. Starting Bloom...\r\n");
      doser_start(&bloom, bloomDose);
      state = STATE_DOSE_BLOOM;
    }
    break;

  case STATE_DOSE_BLOOM:
    if (!doser_isBusy(&bloom)) {
      printf("Bloom complete. Reading TDS...\r\n");

      // Final TDS read
      readTDS(TDSSensor);
      printf("Final TDS: %.2f\r\n", TDSSensor->TDSVal);
      state = STATE_DONE;
      printf("Reservoir nutrient balancing complete.\r\n");

      // make sure to set pins high when pumping is complete
      HAL_GPIO_WritePin(microPump.GPIOx, microPump.GPIO_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(growPump.GPIOx, growPump.GPIO_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(bloomPump.GPIOx, bloomPump.GPIO_Pin, GPIO_PIN_SET);
      // remove this and delay after demo
      for (int i = 0; i < 3; i++) {
        readTDS(TDSSensor);
        printf("Final TDS: %.2f\r\n", TDSSensor->TDSVal);
        HAL_Delay(1000);
      }
    }
    break;

  case STATE_DONE:
    break;
  }
}
