#ifndef LIGHTS_H
#define LIGHTS_H

#include "plantProfiles.h"
#include <stdint.h>

/*
 * Channel mapping (TIM1, ARR = 4799):
 *   TIM1_CH1 → PA8  → 440nm Blue
 *   TIM1_CH2 → PA9  → 660nm Red
 *   TIM1_CH3 → PA10 → 850nm NIR
 *   TIM1_CH4 → PA11 → Fan
 *
 * PWM duty cycle formula:
 *   CCR = (percentage / 100.0) * (ARR + 1)
 *       = (percentage / 100.0) * 4800
 */

#define LIGHTS_ARR 4799U   // matches htim1.Init.Period in main.c

// Initialize PWM channels and start outputs at 0%
void Lights_Init(void);

// Apply all three light channels from a plant profile
void Lights_ApplyProfile(const struct plantProfile *profile);

// Set individual channels (0–100%)
void Lights_SetBlue(uint8_t percentage);
void Lights_SetRed(uint8_t percentage);
void Lights_SetNIR(uint8_t percentage);

// Turn all three channels off
void Lights_Off(void);

#endif
