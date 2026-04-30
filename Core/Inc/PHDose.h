#ifndef PHDOSE_H
#define PHDOSE_H
// PHDose.h

#include "Doser.h"
#include "PeristalticPump.h"
#include "main.h"
#include "pH_Sensor_Driver.h"
#include <string.h>

extern UART_HandleTypeDef huart2;

#define TANK_GALLONS 3.0f

// based on 1:50 pH/water ratio
#define UP_DOSE_ML_PER_GALLON 0.50f // based on 1:50 pH/water ratio
#define DOWN_DOSE_ML_PER_GALLON 0.35f

#define PH_LOW_LIMIT 5.8f
#define PH_HIGH_LIMIT 6.2f

void PHDose_init(struct pH *PHSensor);
void PHDoseUpdate();
void PHDose(struct pH *PHSensor);
#endif
