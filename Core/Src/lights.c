#include "lights.h"
#include "main.h"
#include "stm32h7xx_hal.h"

/*
 * light channels:
 *   TIM1_CH1 (PA8)  → 440nm Blue
 *   TIM1_CH2 (PA9)  → 660nm Red
 *   TIM1_CH3 (PA10) → 850nm NIR
 */

// External timer handler
extern TIM_HandleTypeDef htim1;

//Helper: convert 0-100% to CCR value
static uint32_t percentToCCR(uint8_t percentage) {
    if (percentage > 100) percentage = 100;
    return ((uint32_t)percentage * (LIGHTS_ARR + 1)) / 100;
}


void Lights_Init(void) {
    // Start PWM output on all three light channels at 0% duty cycle
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);  /* Blue  440nm */
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);  /* Red   660nm */
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);  /* NIR   850nm */

    __HAL_TIM_MOE_ENABLE(&htim1);

    // Start with all lights off
    Lights_Off();
}

// Read blue/red/nir percentages from a plant profile and apply them.
void Lights_ApplyProfile(const struct plantProfile *profile) {
    if (profile == NULL) return;
    Lights_SetBlue(profile->blueLightPercentage);
    Lights_SetRed(profile->redLightPercentage);
    Lights_SetNIR(profile->nirLightPercentage);
}

//Lights_SetBlue
void Lights_SetBlue(uint8_t percentage) {
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, percentToCCR(percentage));
}

//Lights_SetRed
void Lights_SetRed(uint8_t percentage) {
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, percentToCCR(percentage));
}

//Lights_SetNIR
void Lights_SetNIR(uint8_t percentage) {
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, percentToCCR(percentage));
}

//Lights_Off
void Lights_Off(void) {
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
}
