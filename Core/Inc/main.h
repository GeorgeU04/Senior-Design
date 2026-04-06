/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

#include "stm32h7xx_nucleo.h"
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

struct maintainableDevices {
  struct DS18B20_Async *waterTempSensor;
  struct DS18B20_Async *enclosureTempSensor;
  struct fan *fan3;
  struct fan *fan2;
  struct fan *fan1;
  struct fan *fan0;
  struct TDS *tds;
  struct pH *ph;
};

extern struct maintainableDevices devices;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern ADC_HandleTypeDef hadc1;

extern ADC_HandleTypeDef hadc2;

extern I2C_HandleTypeDef hi2c1;

extern TIM_HandleTypeDef htim2;

extern UART_HandleTypeDef huart1;

extern COM_InitTypeDef BspCOMInit;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define WPDS18B20_Pin GPIO_PIN_1
#define WPDS18B20_GPIO_Port GPIOF
#define EDS18B20_Pin GPIO_PIN_2
#define EDS18B20_GPIO_Port GPIOF
#define pHSensor_Pin GPIO_PIN_0
#define pHSensor_GPIO_Port GPIOC
#define TDS_Pin GPIO_PIN_6
#define TDS_GPIO_Port GPIOA
#define heater_Pin GPIO_PIN_7
#define heater_GPIO_Port GPIOE
#define cooler_Pin GPIO_PIN_8
#define cooler_GPIO_Port GPIOE
#define pHDown_Pin GPIO_PIN_10
#define pHDown_GPIO_Port GPIOE
#define pHUp_Pin GPIO_PIN_12
#define pHUp_GPIO_Port GPIOE
#define FloraMicro_Pin GPIO_PIN_15
#define FloraMicro_GPIO_Port GPIOE
#define FloraBloom_Pin GPIO_PIN_10
#define FloraBloom_GPIO_Port GPIOB
#define FloraGrow_Pin GPIO_PIN_11
#define FloraGrow_GPIO_Port GPIOB
#define RSX_Pin GPIO_PIN_6
#define RSX_GPIO_Port GPIOC
#define CDX_Pin GPIO_PIN_7
#define CDX_GPIO_Port GPIOC
#define CSX_Pin GPIO_PIN_8
#define CSX_GPIO_Port GPIOC
#define WRX_Pin GPIO_PIN_9
#define WRX_GPIO_Port GPIOC
#define D0_Pin GPIO_PIN_0
#define D0_GPIO_Port GPIOD
#define D1_Pin GPIO_PIN_1
#define D1_GPIO_Port GPIOD
#define D2_Pin GPIO_PIN_2
#define D2_GPIO_Port GPIOD
#define D3_Pin GPIO_PIN_3
#define D3_GPIO_Port GPIOD
#define D4_Pin GPIO_PIN_4
#define D4_GPIO_Port GPIOD
#define D5_Pin GPIO_PIN_5
#define D5_GPIO_Port GPIOD
#define D6_Pin GPIO_PIN_6
#define D6_GPIO_Port GPIOD
#define D7_Pin GPIO_PIN_7
#define D7_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
