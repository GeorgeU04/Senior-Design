#ifndef NUTRIENTDOSE_H
#define NUTRIENTDOSE_H

//NutrientDose.h

#include "PeristalticPump.h"
#include "Doser.h"
#include "TDS_Sensor_Driver.h"
#include "FeedProfile.h"
#include "plantProfiles.h"
#include <string.h>
#include <stdio.h>

extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;

typedef enum {
    STATE_IDLE,
    STATE_DOSE_MICRO,
    STATE_DOSE_GROW,
    STATE_DOSE_BLOOM,
    STATE_DONE
} SystemState;

void nutrientDose_init(void);
void nutrientDoseUpdate(void);
void nutrientDose(void);
void nutrientDose_Demo(void);
#endif
