/*
 * pH_Sensor_Driver.h
 *
 */

#ifndef INC_PH_SENSOR_DRIVER_H_
#define INC_PH_SENSOR_DRIVER_H_

#include "main.h"
#include "stm32l4xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
extern ADC_HandleTypeDef hadc1;


typedef struct {
	char name [100];
	float voltage;
	float pHVal;
	float slope;
	float offset;
} pH;

pH pH_init(char *name);

// Reads analog sensor as voltage
void readVoltage(pH *sensor);

// convert the voltage to pH
void voltageTopH(pH *sensor);

// USE THIS IN MAIN TO GET DATA
void readpH(pH *sensor);


#endif /* INC_PH_SENSOR_DRIVER_H_ */
