#ifndef PLANTPROFILES_H
#define PLANTPROFILES_H

#include <stdint.h>

enum growthStage {
  EARLY_GROWTH = 0,
  LATE_GROWTH = 1,
  EARLY_BLOOM = 2,
  MID_LATE_BLOOM = 3,
  GROWTH_STAGE_COUNT = 4
};

/* Per-stage PWM targets from plant_light_profiles.xlsx.
 * durationDays == 0 means the plant is harvested before this stage. */
struct lightStage {
  uint16_t durationDays;
  uint8_t bluePct; /* 440 nm */
  uint8_t redPct;  /* 660 nm */
  uint8_t nirPct;  /* 850 nm */
};

struct plantProfile {
  char name[32];
  float enclosureTemp; /* °C target */
  float waterTemp;     /* °C target */
  uint32_t growthDurationDays;
  uint16_t lightOnMinutes; /* photoperiod length from 00:00 */
  uint8_t whiteLightPercentage; /* on-level while lights are on */
  struct lightStage stages[GROWTH_STAGE_COUNT];
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

const char *getStageName(enum growthStage stage);

/* Resolve which growth stage a plant is in on the given grow day (1-based). */
enum growthStage plant_getStage(const struct plantProfile *profile,
                                uint32_t growthDay);

/* Fill PWM percentages for the active stage. Returns 0 if stage unused. */
uint8_t plant_getStageLights(const struct plantProfile *profile,
                             enum growthStage stage, uint8_t *blue,
                             uint8_t *red, uint8_t *nir);

#endif /* PLANTPROFILES_H */
