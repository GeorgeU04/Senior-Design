/*
 * pH_Sensor_Driver.h
 *
 */

#ifndef PH_SENSOR_DRIVER_H
#define PH_SENSOR_DRIVER_H

#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern ADC_HandleTypeDef hadc1;

struct pH {
  char name[100];
  float voltage;
  float pHVal;
  float slope;
  float offset;
};

struct pH pH_init(char *name);

// Reads analog sensor as voltage
void readVoltage(struct pH *sensor);

// convert the voltage to pH
void voltageTopH(struct pH *sensor);

// USE THIS IN MAIN TO GET DATA
void readpH(struct pH *sensor);

#endif /* INC_PH_SENSOR_DRIVER_H_ */
