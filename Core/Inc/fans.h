#ifndef FANS_H
#define FANS_H

#include "main.h"
#include <stdint.h>

enum fanState { OFF, LOW, MED, HIGH, MAX };

struct fan {
  TIM_HandleTypeDef *timer;
  uint32_t channel;
  enum fanState state;
};

void runFan(struct fan *fan, enum fanState speed);
void stopFan(struct fan *fan);
void createFan(struct fan *fan, TIM_HandleTypeDef *timer, uint32_t channel);
#endif // !FANS_H
