/*
 * PeristalticPump.c
 *
 *  Created on: Mar 3, 2026
 *      Author: Rainer
 */
#include "PeristalticPump.h"

/* Required Peripherals:
 *
 * GPIO
 *
 *
 */

// Make sure to initialize the new pump first. Initialize a new name, and pin info.
//will return a pump struct object
Pump pump_init(char* Name,GPIO_TypeDef* GPIO, uint16_t Pin){
	Pump newPump;
	strcpy(newPump.name, Name);
	newPump.GPIOx = GPIO;
	newPump.GPIO_Pin = Pin;

	return newPump;
}

// Run pump for set amount of time. Remember, dispenses 1.5 mL/Second
// More dynamic
void runPump(Pump pump,int time){
	HAL_GPIO_WritePin(pump.GPIOx, pump.GPIO_Pin, GPIO_PIN_SET);
	HAL_Delay(time*1000);
	HAL_GPIO_WritePin(pump.GPIOx, pump.GPIO_Pin, GPIO_PIN_RESET);
	HAL_Delay(500); // Wait delay after stopping Pump to allow sensors time to measure and analyze
}

// Run pump for 1 second. Dispenses 1.5 mL/Second
void runPump_1(Pump pump){
	HAL_GPIO_WritePin(pump.GPIOx, pump.GPIO_Pin, GPIO_PIN_SET);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(pump.GPIOx, pump.GPIO_Pin, GPIO_PIN_RESET);
	HAL_Delay(50); // Wait delay after stopping Pump to allow sensors time to measure and analyze
}

// Run pump for 10 seconds. Dispenses 10.5 mL/10 Seconds
void runPump_10(Pump pump){
	HAL_GPIO_WritePin(pump.GPIOx, pump.GPIO_Pin, GPIO_PIN_SET);
	HAL_Delay(10000);
	HAL_GPIO_WritePin(pump.GPIOx, pump.GPIO_Pin, GPIO_PIN_RESET);
	HAL_Delay(500);
}
