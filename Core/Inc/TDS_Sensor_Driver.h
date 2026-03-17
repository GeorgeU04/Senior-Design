/*
 * TDS_Sensor_Driver.h
 *
 */

#ifndef INC_TDS_SENSOR_DRIVER_H_
#define INC_TDS_SENSOR_DRIVER_H_

#include "main.h"
#include <stdio.h>
#include <string.h>

extern ADC_HandleTypeDef hadc1;

typedef struct {
  char name[100];

  float voltage; // volts
  float ECVal;   // uS/cm
  float TDSVal;  // parts per million (ppm)
} TDS;

// Make sure to initialize first
TDS TDS_init(char *name);

// Reads sensor input and stores voltage value
void measureVoltage(TDS *sensor);

// convert voltage to EC
void voltageToEC(TDS *sensor);

// Convert EC value to TDS
void ECToTDS(TDS *sensor);

// USE THIS IN MAIN TO GET DATA
void readTDS(TDS *sensor);


#endif /* INC_TDS_SENSOR_DRIVER_H_ */
