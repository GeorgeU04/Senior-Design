/*
 * PeristalticPump.c
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

	newPump.RUNFLAG = 0;
	newPump.startTime = 0;
	newPump.runTime = 0;


	return newPump;
}

// Run pump for set amount of time. Remember, dispenses 1.5 mL/Second
// More dynamic

// Functions for inverted setup//
//This is for pump circuits requiring additional 2n2222 transistor for 5V to gate
void runPump_Inverted(Pump *pump,uint32_t ms){
	if(pump->RUNFLAG != 1){
		HAL_GPIO_WritePin(pump->GPIOx, pump->GPIO_Pin, GPIO_PIN_RESET);
		pump->startTime = HAL_GetTick();
		pump->runTime = ms;
		pump->RUNFLAG = 1;
	}
}
void checkPump_Inverted(Pump *pump){
	if(pump->RUNFLAG){
		uint32_t currentTime = HAL_GetTick();
		if(currentTime - pump->startTime >= pump->runTime){
			HAL_GPIO_WritePin(pump->GPIOx, pump->GPIO_Pin, GPIO_PIN_SET);
			pump->RUNFLAG = 0;
		}
	}
}

// Functions for non-inverted setup//
//This is for regular default wired pumps
void runPump_NonInverted(Pump *pump,uint32_t ms){
	if(pump->RUNFLAG != 1){
		HAL_GPIO_WritePin(pump->GPIOx, pump->GPIO_Pin, GPIO_PIN_SET);
		pump->startTime = HAL_GetTick();
		pump->runTime = ms;
		pump->RUNFLAG = 1;
	}
}
void checkPump_NonInverted(Pump *pump){
	if(pump->RUNFLAG){
		uint32_t currentTime = HAL_GetTick();
		if(currentTime - pump->startTime >= pump->runTime){
			HAL_GPIO_WritePin(pump->GPIOx, pump->GPIO_Pin, GPIO_PIN_RESET);
			pump->RUNFLAG = 0;
		}
	}
}

