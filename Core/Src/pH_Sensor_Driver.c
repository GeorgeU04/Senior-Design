/*
 * pH_Sensor_Driver.c
 *
 * 	Peripherals Needed:
 * - ADC in
 * - 3.3 - 5V
 *
 *	***Adjust ADC pins as needed***
 */
#include "pH_Sensor_Driver.h"


pH pH_init(char *name){
	pH sensor;

	strncpy(sensor.name, name, sizeof(sensor.name));
    sensor.name[sizeof(sensor.name)-1] = '\0';
    sensor.voltage = 0.0f;
    sensor.pHVal = 0.0f;
	return sensor;
}

// Reads analog sensor as voltage
void readVoltage(pH *sensor){
	uint32_t adcValue =0;
	for(int i = 0; i < 10; i++){
		HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
		adcValue += HAL_ADC_GetValue(&hadc1);      // read 12-bit ADC
	}
	float volt = ((float)(adcValue/10) / 4095.0f) * 3.3f; // convert to volts
	sensor->voltage =volt / 6.0f;                // compensate sensor amplifier
}

// convert the voltage to pH
void voltageTopH(pH *sensor){
	sensor->pHVal=(3.5f * sensor->voltage); // approximate pH
}

// USE THIS IN MAIN TO GET DATA
void readpH(pH *sensor){
	readVoltage(sensor);
	voltageToPH(sensor);
}

float getpH(pH *sensor){
	return sensor->pHVal;
}

float getVoltage(pH *sensor){
	return sensor->voltage;
}


