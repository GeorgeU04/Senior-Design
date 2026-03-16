/*
 * TDS_Sensor_Driver.c
 *
 * 	SEN0244
 * 	Required Peripherals:
 * 	- ADC
 * 	- 3.3V - 5V
 * 	***Adjust ADC pins as needed***
 */

#include "TDS_Sensor_Driver.h"



#define VREF 3.3f   // STM32 ADC reference voltage **swap 3.3 for 5 if neeeded**

// Make sure to initialize first
TDS TDS_init(char* name){
    TDS sensor;

	strncpy(sensor.name, name, sizeof(sensor.name));
    sensor.name[sizeof(sensor.name)-1] = '\0';
    sensor.voltage = 0;
    sensor.ECVal = 0;
    sensor.TDSVal = 0;

	return sensor;
}

// Reads sensor input and stores voltage value
void measureVoltage(TDS *sensor){
	//start ADC conversion
	HAL_ADC_Start(&hadc1);
	// Poll ADC1 Peripheral & TimeOut = 10mSec
	HAL_ADC_PollForConversion(&hadc1, 10);
	// Read The ADC Conversion Result
	sensor->voltage =(((float) HAL_ADC_GetValue(&hadc1))/4095.0f)*VREF;
}

// convert voltage to EC
void voltageToEC(TDS *sensor){
	float V = sensor->voltage;
    // DFRobot polynomial: outputs EC in µS/cm
    float ec_uS = 133.42f*V*V*V - 255.86f*V*V + 857.39f*V;
    sensor->ECVal = ec_uS / 1000.0f;  // convert µS/cm to mS/cm
}

//Convert EC value to TDS
void ECToTDS(TDS *sensor){
	sensor->TDSVal = sensor->ECVal * 500;
}

// USE THIS IN MAIN TO GET DATA
void readTDS(TDS *sensor){
	measureVoltage(sensor);
	voltageToEC(sensor);
	ECToTDS(sensor);
}



