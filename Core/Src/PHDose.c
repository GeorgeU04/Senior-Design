// PHDose.c
#include "PHDose.h"
#include <stdio.h>
#include <string.h>

struct Pump upPump ={0};
struct Pump downPump ={0};
struct pH PHSensor ={0};
static Doser upDoser;
static Doser downDoser;
static char msg[200];
static float upStepMl;
static float downStepMl;
static uint8_t wasBusyUp = 0;
static uint8_t wasBusyDown = 0;
static uint8_t firstCycle = 1;

void PHDose_init(){
	upStepMl   = UP_DOSE_ML_PER_GALLON   * TANK_GALLONS;
	downStepMl = DOWN_DOSE_ML_PER_GALLON * TANK_GALLONS;
	
	wasBusyUp = 0;
	wasBusyDown = 0;
	firstCycle = 1;

	upPump = pump_init("upPump",GPIOB, GPIO_PIN_1);
	downPump = pump_init("downPump",GPIOB, GPIO_PIN_6);

	PHSensor = pH_init("pH");
	
	doser_init(&upDoser, &upPump, 1.5f, upStepMl, 5000);
	doser_init(&downDoser, &downPump, 1.5f, downStepMl, 5000);
	
	snprintf(msg, sizeof(msg),"Tank: %.2f gal | Up step: %.2f mL | Down step: %.2f mL\r\n",TANK_GALLONS, upStepMl, downStepMl);
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	readpH(&PHSensor);
	snprintf(msg, sizeof(msg),"pH: %.2f  Busy(U/D): %d/%d\r\n",PHSensor.pHVal,doser_isBusy(&upDoser),doser_isBusy(&downDoser));
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}

void PHDoseUpdate(){
	doser_update_noninverted(&upDoser);
	doser_update_noninverted(&downDoser);
}

void PHDose(){
	uint8_t busyUp = doser_isBusy(&upDoser);
	uint8_t busyDown = doser_isBusy(&downDoser);

	      // Detect "just finished" (busy -> idle)
	uint8_t upJustFinished   = (wasBusyUp && !busyUp);
	uint8_t downJustFinished = (wasBusyDown && !busyDown);

	      // Only read: once at startup OR after a dose+mix completes
	if (firstCycle || upJustFinished || downJustFinished){
		firstCycle = 0;

	        readpH(&PHSensor);

	        snprintf(msg, sizeof(msg),"pH: %.2f  Busy(U/D): %d/%d\r\n",PHSensor.pHVal, busyUp, busyDown);
	        HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	        // Only dose if both pumps are idle
	        if (!busyUp && !busyDown)
	        {
	          if (PHSensor.pHVal < PH_LOW_LIMIT)
	          {
	            snprintf(msg, sizeof(msg),"pH low. Dosing UP: %.2f mL\r\n",upDoser.stepVolumeMl);
	            HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	            doser_start(&upDoser, upDoser.stepVolumeMl);
	          }
	          else if (PHSensor.pHVal > PH_HIGH_LIMIT)
	          {
	            snprintf(msg, sizeof(msg),"pH high: %.2f Dosing DOWN: %.2f mL\r\n",PHSensor.pHVal,downDoser.stepVolumeMl);
	            HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	            doser_start(&downDoser, downDoser.stepVolumeMl);
	          }
	          else
	          {
	            snprintf(msg, sizeof(msg),"pH within range.\r\n");
	            HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	          }
	        }
	      }

	      // Update previous state
	      wasBusyUp = busyUp;
	      wasBusyDown = busyDown;
	
}
