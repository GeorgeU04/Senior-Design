#ifndef PLANTPROFILES_H
#define PLANTPROFILES_H

#include <stdint.h>

enum growthStage {EARLY_GROWTH, LATE_GROWTH, EARLY_BLOOM, MID_LATE_BLOOM };

struct plantProfile {
  char name[32];
  float enclosureTemp;
  float waterTemp;
  enum growthStage stage;
  uint32_t growthDurationDays;
  uint16_t lightOnMinutes;
  uint8_t whiteLightPercentage;
  uint8_t blueLightPercentage;
  uint8_t redLightPercentage;
};

extern const struct plantProfile ARUGULA_PROFILE;
extern const struct plantProfile LETTUCE_PROFILE;
extern const struct plantProfile BASIL_PROFILE;
extern const struct plantProfile SPINACH_PROFILE;
extern const struct plantProfile KALE_PROFILE;
extern const struct plantProfile BOK_CHOY_PROFILE;
extern const struct plantProfile SWISS_CHARD_PROFILE;
extern const struct plantProfile CILANTRO_PROFILE;
extern const struct plantProfile PARSLEY_PROFILE;
extern const struct plantProfile MINT_PROFILE;
extern const struct plantProfile GREEN_ONION_PROFILE;
extern const struct plantProfile ROMAINE_PROFILE;
extern const struct plantProfile BUTTERHEAD_PROFILE;
extern const struct plantProfile MUSTARD_GREENS_PROFILE;

void loadProfile(const struct plantProfile *src);
const char *getStageName(enum growthStage stage);
#endif // !PLANTPROFILES_H