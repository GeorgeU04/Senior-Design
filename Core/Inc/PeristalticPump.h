/*
 * PeristalticPump.h
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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helps individualize each pump
struct Pump {
  char name[100];
  GPIO_TypeDef *GPIOx;
  uint16_t GPIO_Pin;
  uint8_t RUNFLAG;
  uint32_t startTime;
  uint32_t runTime;
};

struct Pump pump_init(char *Name, GPIO_TypeDef *GPIO, uint16_t Pin);
void runPump_Inverted(struct Pump *pump, uint32_t ms);
void checkPump_Inverted(struct Pump *pump);
void runPump_NonInverted(struct Pump *pump, uint32_t ms);
void checkPump_NonInverted(struct Pump *pump);

#endif /* INC_PERISTALTICPUMP_H_ */
