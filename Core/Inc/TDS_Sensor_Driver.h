/*
 * TDS_Sensor_Driver.h
 *
 */

#ifndef TDS_SENSOR_DRIVER
#define TDS_SENSOR_DRIVER

#include "main.h"
#include <stdio.h>
#include <string.h>

extern ADC_HandleTypeDef hadc1;

struct TDS {
  char name[100];

  float voltage; // volts
  float ECVal;   // uS/cm
  float TDSVal;  // parts per million (ppm)
};

// Make sure to initialize first
struct TDS TDS_init(char *name);

// Reads sensor input and stores voltage value
void measureVoltage(struct TDS *sensor);

// convert voltage to EC
void voltageToEC(struct TDS *sensor);

// Convert EC value to TDS
void ECToTDS(struct TDS *sensor);

// USE THIS IN MAIN TO GET DATA
void readTDS(struct TDS *sensor);

#endif /* INC_TDS_SENSOR_DRIVER_H_ */
