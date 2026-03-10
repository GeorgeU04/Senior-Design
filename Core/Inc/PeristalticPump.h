/*
 * PeristalticPump.h
 *
 *  Created on: Mar 5, 2026
 *      Author: Rainer
 *
 *      Notes:
 *      pump V+ ---> Power rail
 *      pump GND ---> MOSFET drain
 *      Pump V+ ---> DIODE Stripe side --> MOS Drain
 *      MOS Gate --> Resistor --> GPIO output
 *      MOS Source ---> GND MCU
 *      12V external V+ --> power rail
 *      12V GND --> GND rail
 */

#ifndef INC_PERISTALTICPUMP_H_
#define INC_PERISTALTICPUMP_H_

#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "stm32l4xx_hal.h"


// Helps individualize each pump
typedef struct{
	char name[100];
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
}Pump;

Pump pump_init(char* Name,GPIO_TypeDef* GPIO, uint16_t Pin);
void runPump(Pump pump,int time);
void runPump_1(Pump pump);
void runPump_10(Pump pump);

#endif /* INC_PERISTALTICPUMP_H_ */
