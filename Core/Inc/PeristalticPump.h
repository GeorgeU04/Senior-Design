/*
 * PeristalticPump.h
 *
 *  Created on: Mar 5, 2026
 *      Author: Rainer
 */

#ifndef INC_PERISTALTICPUMP_H_
#define INC_PERISTALTICPUMP_H_

#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// Helps individualize each pump
typedef struct{
	char name[50];
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
}Pump;

Pump pump_init(char* Name,GPIO_TypeDef* GPIO, uint16_t Pin);
void runPump_1(Pump pump);
void runPump_10(Pump pump);

#endif /* INC_PERISTALTICPUMP_H_ */
