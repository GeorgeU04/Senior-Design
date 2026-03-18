#ifndef PLANTPROFILES_H
#define PLANTPROFILES_H

#include <stdint.h>

enum growthStage { EARLY_SEEDLING, SEEDLING, VEGETATIVE, MATURE };

struct plantProfile {
  char name[32];
  float enclosureTemp;
  float waterTemp;
  float pH;
  float TDS;
  enum growthStage stage;
  uint32_t growthDurationDays;
  uint16_t lightOnMinutes;
  uint8_t whiteLightPercentage;
  uint8_t blueLightPercentage;
  uint8_t redLightPercentage;
};

extern const struct plantProfile LETTUCE_PROFILE;
extern const struct plantProfile ARUGULA_PROFILE;

void loadProfile(struct plantProfile *dest, const struct plantProfile *src);
const char *getStageName(enum growthStage stage);
#endif // !PLANTPROFILES_H
