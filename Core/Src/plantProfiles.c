#include "plantProfiles.h"
#include <stdint.h>

char *growthStageNames[] = {"Early Seedling", "Seedling", "Vegetative",
                            "Mature"};

/* More profiles can be added dynamically here */
// these are also dummy values, will be changed later
const struct plantProfile ARUGULA_PROFILE = {
    .name = "Arugula",
    .enclosureTemp = 22.0f,
    .waterTemp = 20.0f,
    .pH = 6.0f,
    .TDS = 600.0f,
    .stage = EARLY_SEEDLING,
    .growthDurationDays = 28,
    .lightOnMinutes = 16 * 60,
    .whiteLightPercentage = 70,
    .blueLightPercentage = 25,
    .redLightPercentage = 40,
};

const struct plantProfile LETTUCE_PROFILE = {
    .name = "Lettuce",
    .enclosureTemp = 21.0f,
    .waterTemp = 19.0f,
    .pH = 5.8f,
    .TDS = 500.0f,
    .stage = EARLY_SEEDLING,
    .growthDurationDays = 35,
    .lightOnMinutes = 16 * 60,
    .whiteLightPercentage = 65,
    .blueLightPercentage = 30,
    .redLightPercentage = 35,
};

void loadProfile(struct plantProfile *dest, const struct plantProfile *src) {
  *dest = *src;
}

inline const char *getStageName(enum growthStage stage) {
  if ((uint32_t)stage < sizeof(growthStageNames) / sizeof(growthStageNames[0]))
    return growthStageNames[stage];
  return "Unknown";
}
