#ifndef NUTRIENTDOSE_H
#define NUTRIENTDOSE_H

// NutrientDose.h

#include "Doser.h"
#include "FeedProfile.h"
#include "TDS_Sensor_Driver.h"
#include "plantProfiles.h"
#include <stdio.h>
#include <string.h>

extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;

typedef enum {
  STATE_IDLE,
  STATE_DOSE_MICRO,
  STATE_DOSE_GROW,
  STATE_DOSE_BLOOM,
  STATE_DONE
} SystemState;

void nutrientDose_init(struct TDS *TDSSenor);
void nutrientDoseUpdate(void);
void nutrientDose(struct TDS *TDSSenor);
void nutrientDose_Demo(struct TDS *TDSSenor);
#endif
