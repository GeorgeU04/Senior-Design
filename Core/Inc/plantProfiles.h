#ifndef PLANTPROFILES_H
#define PLANTPROFILES_H

#include <stdint.h>

enum growthStage { earlySeedling, seedling, vegetative, mature };

struct plantProfile {
  char name[32];
  char stageName[32];
  float enclosureTemp;
  float waterTemp;
  float pH;
  enum growthStage stage;
  uint32_t growthDurationDays;
  uint16_t lightOnMinutes;
  uint8_t whiteLightPercentage;
  uint8_t blueLightPercentage;
  uint8_t redLightPercentage;
};

void setPlantProfile(struct plantProfile *profile);
#endif // !PLANTPROFILES_H
