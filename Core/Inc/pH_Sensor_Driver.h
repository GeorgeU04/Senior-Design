/*
 * pH_Sensor_Driver.h
 *
 *  Created on: Mar 9, 2026
 *      Author: Rainer
 */

#ifndef INC_PH_SENSOR_DRIVER_H_
#define INC_PH_SENSOR_DRIVER_H_

#include "stm32l4xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct {
	char name [100];
	float voltage;
	float pHVal;
} pH;

pH pH_init(char *name);

// Reads analog sensor as voltage
void readVoltage(pH *sensor);

// convert the voltage to pH
void voltageTopH(pH *sensor);

// USE THIS IN MAIN TO GET DATA
void readpH(pH *sensor);

float getpH(pH *sensor);

float getVoltage(pH *sensor);


#endif /* INC_PH_SENSOR_DRIVER_H_ */
