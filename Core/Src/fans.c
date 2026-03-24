#include "fans.h"
#include "stm32h7xx_hal_tim.h"
#include <stdint.h>

static const uint16_t MAX_SPEED = 4800;

static const char *fanStates[] = {"OFF", "LOW", "MED", "HIGH", "MAX"};

void createFan(struct fan *fan, TIM_HandleTypeDef *timer, uint32_t channel) {
  fan->state = OFF;
  fan->channel = channel;
  fan->timer = timer;
}

void runFan(struct fan *fan, enum fanState speed) {
  switch (speed) {
  case OFF:
    fan->state = OFF;
    __HAL_TIM_SET_COMPARE(fan->timer, fan->channel, 0);
    break;
  case LOW:
    fan->state = LOW;
    __HAL_TIM_SET_COMPARE(fan->timer, fan->channel, 600);
    break;
  case MED:
    fan->state = MED;
    __HAL_TIM_SET_COMPARE(fan->timer, fan->channel, 2400);
    break;
  case HIGH:
    fan->state = HIGH;
    __HAL_TIM_SET_COMPARE(fan->timer, fan->channel, 3600);
    break;
  case MAX:
    fan->state = MAX;
    __HAL_TIM_SET_COMPARE(fan->timer, fan->channel, 4800);
    break;
  default:
    fan->state = OFF;
    __HAL_TIM_SET_COMPARE(fan->timer, fan->channel, 0);
    break;
  }
  HAL_TIM_PWM_Start(fan->timer, fan->channel);
}

void stopFan(struct fan *fan) {
  fan->state = OFF;
  __HAL_TIM_SET_COMPARE(fan->timer, fan->channel, 0);
}
