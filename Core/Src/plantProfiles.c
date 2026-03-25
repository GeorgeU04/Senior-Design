#include "plantProfiles.h"
#include <stdint.h>

char *growthStageNames[] = {"Early Growth", "Late Growth", "Early Bloom",
                            "Mid Late Bloom"};

/* More profiles can be added dynamically here */
// these are also dummy values, will be changed later
const struct plantProfile ARUGULA_PROFILE = {
    .name = "Arugula",
    .enclosureTemp = 22.0f,
    .waterTemp = 20.0f,
    .stage = EARLY_GROWTH,
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
    .stage = EARLY_GROWTH,
    .growthDurationDays = 35,
    .lightOnMinutes = 16 * 60,
    .whiteLightPercentage = 65,
    .blueLightPercentage = 30,
    .redLightPercentage = 35,
};

/* New profiles */
const struct plantProfile BASIL_PROFILE = {
    .name = "Basil",
    .enclosureTemp = 24.0f,
    .waterTemp = 22.0f,
    .stage = EARLY_GROWTH,
    .growthDurationDays = 35,
    .lightOnMinutes = 16 * 60,
    .whiteLightPercentage = 75,
    .blueLightPercentage = 20,
    .redLightPercentage = 45,
};

const struct plantProfile SPINACH_PROFILE = {
    .name = "Spinach",
    .enclosureTemp = 19.0f,
    .waterTemp = 18.0f,
    .stage = EARLY_GROWTH,
    .growthDurationDays = 40,
    .lightOnMinutes = 14 * 60,
    .whiteLightPercentage = 65,
    .blueLightPercentage = 30,
    .redLightPercentage = 30,
};

const struct plantProfile KALE_PROFILE = {
    .name = "Kale",
    .enclosureTemp = 20.0f,
    .waterTemp = 19.0f,
    .stage = EARLY_GROWTH,
    .growthDurationDays = 55,
    .lightOnMinutes = 16 * 60,
    .whiteLightPercentage = 70,
    .blueLightPercentage = 25,
    .redLightPercentage = 35,
};

const struct plantProfile BOK_CHOY_PROFILE = {
    .name = "Bok Choy",
    .enclosureTemp = 21.0f,
    .waterTemp = 19.0f,
    .stage = EARLY_GROWTH,
    .growthDurationDays = 35,
    .lightOnMinutes = 16 * 60,
    .whiteLightPercentage = 70,
    .blueLightPercentage = 25,
    .redLightPercentage = 35,
};

const struct plantProfile SWISS_CHARD_PROFILE = {
    .name = "Swiss Chard",
    .enclosureTemp = 21.0f,
    .waterTemp = 20.0f,
    .stage = EARLY_GROWTH,
    .growthDurationDays = 50,
    .lightOnMinutes = 16 * 60,
    .whiteLightPercentage = 70,
    .blueLightPercentage = 25,
    .redLightPercentage = 35,
};

const struct plantProfile CILANTRO_PROFILE = {
    .name = "Cilantro",
    .enclosureTemp = 20.0f,
    .waterTemp = 19.0f,
    .stage = EARLY_GROWTH,
    .growthDurationDays = 35,
    .lightOnMinutes = 14 * 60,
    .whiteLightPercentage = 65,
    .blueLightPercentage = 30,
    .redLightPercentage = 30,
};

const struct plantProfile PARSLEY_PROFILE = {
    .name = "Parsley",
    .enclosureTemp = 21.0f,
    .waterTemp = 20.0f,
    .stage = EARLY_GROWTH,
    .growthDurationDays = 60,
    .lightOnMinutes = 16 * 60,
    .whiteLightPercentage = 70,
    .blueLightPercentage = 25,
    .redLightPercentage = 35,
};

const struct plantProfile MINT_PROFILE = {
    .name = "Mint",
    .enclosureTemp = 22.0f,
    .waterTemp = 20.0f,
    .stage = EARLY_GROWTH,
    .growthDurationDays = 45,
    .lightOnMinutes = 16 * 60,
    .whiteLightPercentage = 70,
    .blueLightPercentage = 25,
    .redLightPercentage = 35,
};

const struct plantProfile GREEN_ONION_PROFILE = {
    .name = "Green Onion",
    .enclosureTemp = 21.0f,
    .waterTemp = 19.0f,
    .stage = EARLY_GROWTH,
    .growthDurationDays = 35,
    .lightOnMinutes = 14 * 60,
    .whiteLightPercentage = 65,
    .blueLightPercentage = 25,
    .redLightPercentage = 35,
};

const struct plantProfile ROMAINE_PROFILE = {
    .name = "Romaine",
    .enclosureTemp = 21.0f,
    .waterTemp = 19.0f,
    .stage = EARLY_GROWTH,
    .growthDurationDays = 45,
    .lightOnMinutes = 16 * 60,
    .whiteLightPercentage = 65,
    .blueLightPercentage = 30,
    .redLightPercentage = 35,
};

const struct plantProfile BUTTERHEAD_PROFILE = {
    .name = "Butterhead Lettuce",
    .enclosureTemp = 20.0f,
    .waterTemp = 19.0f,
    .stage = EARLY_GROWTH,
    .growthDurationDays = 35,
    .lightOnMinutes = 16 * 60,
    .whiteLightPercentage = 65,
    .blueLightPercentage = 30,
    .redLightPercentage = 35,
};

const struct plantProfile MUSTARD_GREENS_PROFILE = {
    .name = "Mustard Greens",
    .enclosureTemp = 20.0f,
    .waterTemp = 19.0f,
    .stage = EARLY_GROWTH,
    .growthDurationDays = 30,
    .lightOnMinutes = 16 * 60,
    .whiteLightPercentage = 70,
    .blueLightPercentage = 25,
    .redLightPercentage = 35,
};

inline const char *getStageName(enum growthStage stage) {
  if ((uint32_t)stage < sizeof(growthStageNames) / sizeof(growthStageNames[0]))
    return growthStageNames[stage];
  return "Unknown";
}
