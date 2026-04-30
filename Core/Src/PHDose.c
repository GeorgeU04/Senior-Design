// PHDose.c
#include "PHDose.h"
#include <stdio.h>

struct Pump upPump = {0};
struct Pump downPump = {0};
static Doser upDoser;
static Doser downDoser;
static float upStepMl;
static float downStepMl;
static uint8_t wasBusyUp = 0;
static uint8_t wasBusyDown = 0;
static uint8_t firstCycle = 1;

void PHDose_init(struct pH *PHSensor) {
  upStepMl = UP_DOSE_ML_PER_GALLON * TANK_GALLONS;
  downStepMl = DOWN_DOSE_ML_PER_GALLON * TANK_GALLONS;

  wasBusyUp = 0;
  wasBusyDown = 0;
  firstCycle = 1;

  upPump = pump_init("upPump", GPIOB, GPIO_PIN_1);
  downPump = pump_init("downPump", GPIOB, GPIO_PIN_6);

  *PHSensor = pH_init("pH");

  doser_init(&upDoser, &upPump, 1.5f, upStepMl, 5000);
  doser_init(&downDoser, &downPump, 1.5f, downStepMl, 5000);

  printf("Tank: %.2f gal | Up step: %.2f mL | Down step: %.2f mL\r\n",
         TANK_GALLONS, upStepMl, downStepMl);
  readpH(PHSensor);
  printf("pH: %.2f  Busy(U/D): %d/%d\r\n", PHSensor->pHVal,
         doser_isBusy(&upDoser), doser_isBusy(&downDoser));
}

void PHDoseUpdate() {
  doser_update_noninverted(&upDoser);
  doser_update_noninverted(&downDoser);
}

void PHDose(struct pH *PHSensor) {
  uint8_t busyUp = doser_isBusy(&upDoser);
  uint8_t busyDown = doser_isBusy(&downDoser);

  // Detect "just finished" (busy -> idle)
  uint8_t upJustFinished = (wasBusyUp && !busyUp);
  uint8_t downJustFinished = (wasBusyDown && !busyDown);

  // Only read: once at startup OR after a dose+mix completes
  if (firstCycle || upJustFinished || downJustFinished) {
    firstCycle = 0;

    readpH(PHSensor);

    printf("pH: %.2f  Busy(U/D): %d/%d\r\n", PHSensor->pHVal, busyUp, busyDown);

    // Only dose if both pumps are idle
    if (!busyUp && !busyDown) {
      if (PHSensor->pHVal < PH_LOW_LIMIT) {
        printf("pH low. Dosing UP: %.2f mL\r\n", upDoser.stepVolumeMl);

        doser_start(&upDoser, upDoser.stepVolumeMl);
      } else if (PHSensor->pHVal > PH_HIGH_LIMIT) {
        printf("pH high: %.2f Dosing DOWN: %.2f mL\r\n", PHSensor->pHVal,
               downDoser.stepVolumeMl);

        doser_start(&downDoser, downDoser.stepVolumeMl);
      } else {
        printf("pH within range.\r\n");
      }
    }
  }

  // Update previous state
  wasBusyUp = busyUp;
  wasBusyDown = busyDown;
}
