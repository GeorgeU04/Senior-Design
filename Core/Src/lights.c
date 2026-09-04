#include "lights.h"
#include "main.h"
#include "stm32h7xx_hal_tim.h"
#include <stdint.h>

/*
 * light channels:
 *   TIM3_CH1 (PB1)  → 440nm Blue
 *   TIM1_CH2 (PE11)  → 660nm Red
 *   TIM1_CH3 (PE13) → 850nm NIR
 *   TIM4_CH1 (PD12)
 */

// External timer handler

// Helper: convert 0-100% to CCR value
static uint32_t percentToCCR(uint8_t percentage) {
  if (percentage > 100)
    percentage = 100;
  return ((uint32_t)percentage * (LIGHTS_ARR + 1)) / 100;
}

void Lights_Init(void) {
  // Start PWM output on all four light channels at 0% duty cycle
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4); /* Blue  440nm */
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2); /* Red   660nm */
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3); /* NIR   850nm */
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1); /* White */

  __HAL_TIM_MOE_ENABLE(&htim1);
  __HAL_TIM_MOE_ENABLE(&htim3);
  __HAL_TIM_MOE_ENABLE(&htim4);

  // Start with all lights off
  Lights_Off();
}

/* Apply early-growth stage lights (selection / fallback). */
void Lights_ApplyProfile(const struct plantProfile *profile) {
  if (profile == NULL)
    return;

  uint8_t blue = 0, red = 0, nir = 0;
  enum growthStage stage = plant_getStage(profile, 1);
  if (!plant_getStageLights(profile, stage, &blue, &red, &nir))
    return;

  Lights_SetWhite(profile->whiteLightPercentage);
  Lights_SetBlue(blue);
  Lights_SetRed(red);
  Lights_SetNIR(nir);
}

// Lights_SetBlue
void Lights_SetBlue(uint8_t percentage) {
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, percentToCCR(percentage));
}

// Lights_SetRed
void Lights_SetRed(uint8_t percentage) {
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, percentToCCR(percentage));
}

// Lights_SetNIR
void Lights_SetNIR(uint8_t percentage) {
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, percentToCCR(percentage));
}

void Lights_SetWhite(uint8_t percentage) {
  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, percentToCCR(percentage));
}

// Lights_Off
void Lights_Off(void) {
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
}
