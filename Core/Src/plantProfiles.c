#include "plantProfiles.h"
#include <stdint.h>

char *growthStageNames[] = {"Early Growth", "Late Growth", "Early Bloom",
                            "Mid Late Bloom"};

/* More profiles can be added dynamically here */
// these are also dummy values, will be changed later
// red, blue, nir light values accurate, don't change
const struct plantProfile ARUGULA_PROFILE = {
    .name                 = "Arugula",
    .enclosureTemp        = 22.0f,
    .waterTemp            = 20.0f,
    .stage                = EARLY_GROWTH,
    .growthDurationDays   = 28,
    .lightOnMinutes       = 16 * 60,
    .whiteLightPercentage = 70,   // original — not Mariam's channel
    .blueLightPercentage  = 15,   // high blue delays bolting
    .redLightPercentage   = 25,   // 660nm primary photosynthesis
    .nirLightPercentage   =  5,   // very low — prevents early bolt
};

// LETTUCE — standard leafy green, 91R+9B research optimum
const struct plantProfile LETTUCE_PROFILE = {
    .name                 = "Lettuce",
    .enclosureTemp        = 21.0f,
    .waterTemp            = 19.0f,
    .stage                = EARLY_GROWTH,
    .growthDurationDays   = 35,
    .lightOnMinutes       = 16 * 60,
    .whiteLightPercentage = 65,
    .blueLightPercentage  = 12,   // ~9-12% blue research-backed
    .redLightPercentage   = 25,   // 660nm drives fresh weight
    .nirLightPercentage   =  8,   // moderate NIR, Emerson effect
};

// BASIL — red boosts rosmarinic acid, moderate NIR okay
const struct plantProfile BASIL_PROFILE = {
    .name                 = "Basil",
    .enclosureTemp        = 24.0f,
    .waterTemp            = 22.0f,
    .stage                = EARLY_GROWTH,
    .growthDurationDays   = 35,
    .lightOnMinutes       = 16 * 60,
    .whiteLightPercentage = 75,
    .blueLightPercentage  = 14,   // higher blue, compact internodes
    .redLightPercentage   = 26,   // red boosts essential oils
    .nirLightPercentage   = 10,   // moderate NIR fine for basil
};

// SPINACH — bolt-prone, shorter photoperiod, very low NIR
const struct plantProfile SPINACH_PROFILE = {
    .name                 = "Spinach",
    .enclosureTemp        = 19.0f,
    .waterTemp            = 18.0f,
    .stage                = EARLY_GROWTH,
    .growthDurationDays   = 40,
    .lightOnMinutes       = 14 * 60,
    .whiteLightPercentage = 65,
    .blueLightPercentage  = 15,   // blue improves quality, ascorbic acid
    .redLightPercentage   = 25,   // 660nm primary driver
    .nirLightPercentage   =  5,   // very low — spinach bolts easily
};

// KALE — less bolt-prone, moderate NIR acceptable
const struct plantProfile KALE_PROFILE = {
    .name                 = "Kale",
    .enclosureTemp        = 20.0f,
    .waterTemp            = 19.0f,
    .stage                = EARLY_GROWTH,
    .growthDurationDays   = 55,
    .lightOnMinutes       = 16 * 60,
    .whiteLightPercentage = 70,
    .blueLightPercentage  = 13,   // 83R+17B reduces height in kale
    .redLightPercentage   = 25,   // 660nm primary photosynthesis
    .nirLightPercentage   = 10,   // moderate NIR okay for kale
};

// BOK CHOY — brassica, similar to kale
const struct plantProfile BOK_CHOY_PROFILE = {
    .name                 = "Bok Choy",
    .enclosureTemp        = 21.0f,
    .waterTemp            = 19.0f,
    .stage                = EARLY_GROWTH,
    .growthDurationDays   = 35,
    .lightOnMinutes       = 16 * 60,
    .whiteLightPercentage = 70,
    .blueLightPercentage  = 13,
    .redLightPercentage   = 25,
    .nirLightPercentage   =  9,
};

// SWISS CHARD — slow growing, less bolt-prone
const struct plantProfile SWISS_CHARD_PROFILE = {
    .name                 = "Swiss Chard",
    .enclosureTemp        = 21.0f,
    .waterTemp            = 20.0f,
    .stage                = EARLY_GROWTH,
    .growthDurationDays   = 50,
    .lightOnMinutes       = 16 * 60,
    .whiteLightPercentage = 70,
    .blueLightPercentage  = 12,
    .redLightPercentage   = 23,
    .nirLightPercentage   = 10,
};

// CILANTRO — very bolt-prone, shortest photoperiod, minimum NIR
const struct plantProfile CILANTRO_PROFILE = {
    .name                 = "Cilantro",
    .enclosureTemp        = 20.0f,
    .waterTemp            = 19.0f,
    .stage                = EARLY_GROWTH,
    .growthDurationDays   = 35,
    .lightOnMinutes       = 14 * 60,
    .whiteLightPercentage = 65,
    .blueLightPercentage  = 16,   // high blue delays bolting
    .redLightPercentage   = 22,
    .nirLightPercentage   =  5,   // minimum NIR — bolts under high FR
};

// PARSLEY — slow, long cycle, not bolt-prone, handles more NIR
const struct plantProfile PARSLEY_PROFILE = {
    .name                 = "Parsley",
    .enclosureTemp        = 21.0f,
    .waterTemp            = 20.0f,
    .stage                = EARLY_GROWTH,
    .growthDurationDays   = 60,
    .lightOnMinutes       = 16 * 60,
    .whiteLightPercentage = 70,   /* original */
    .blueLightPercentage  = 12,
    .redLightPercentage   = 23,
    .nirLightPercentage   = 12,   // more NIR okay — not bolt-prone
};

// MINT — vigorous, tolerates wider light range
const struct plantProfile MINT_PROFILE = {
    .name                 = "Mint",
    .enclosureTemp        = 22.0f,
    .waterTemp            = 20.0f,
    .stage                = EARLY_GROWTH,
    .growthDurationDays   = 45,
    .lightOnMinutes       = 16 * 60,
    .whiteLightPercentage = 70,
    .blueLightPercentage  = 12,
    .redLightPercentage   = 24,
    .nirLightPercentage   = 12,   // mint handles higher NIR well
};

// GREEN ONION — monocot, moderate across all channels
const struct plantProfile GREEN_ONION_PROFILE = {
    .name                 = "Green Onion",
    .enclosureTemp        = 21.0f,
    .waterTemp            = 19.0f,
    .stage                = EARLY_GROWTH,
    .growthDurationDays   = 35,
    .lightOnMinutes       = 14 * 60,
    .whiteLightPercentage = 65,
    .blueLightPercentage  = 12,
    .redLightPercentage   = 23,
    .nirLightPercentage   =  8,
};

// ROMAINE — upright, moderate blue keeps compact
const struct plantProfile ROMAINE_PROFILE = {
    .name                 = "Romaine",
    .enclosureTemp        = 21.0f,
    .waterTemp            = 19.0f,
    .stage                = EARLY_GROWTH,
    .growthDurationDays   = 45,
    .lightOnMinutes       = 16 * 60,
    .whiteLightPercentage = 65,
    .blueLightPercentage  = 12,
    .redLightPercentage   = 25,
    .nirLightPercentage   =  8,
};

// BUTTERHEAD LETTUCE — soft leaf type, 91R+9B documented optimum
const struct plantProfile BUTTERHEAD_PROFILE = {
    .name                 = "Butterhead Lettuce",
    .enclosureTemp        = 20.0f,
    .waterTemp            = 19.0f,
    .stage                = EARLY_GROWTH,
    .growthDurationDays   = 35,
    .lightOnMinutes       = 16 * 60,
    .whiteLightPercentage = 65,
    .blueLightPercentage  = 12,
    .redLightPercentage   = 25,
    .nirLightPercentage   =  8,
};

// MUSTARD GREENS — brassica, moderately bolt-prone, low-moderate NIR
const struct plantProfile MUSTARD_GREENS_PROFILE = {
    .name                 = "Mustard Greens",
    .enclosureTemp        = 20.0f,
    .waterTemp            = 19.0f,
    .stage                = EARLY_GROWTH,
    .growthDurationDays   = 30,
    .lightOnMinutes       = 16 * 60,
    .whiteLightPercentage = 70,
    .blueLightPercentage  = 14,   // slightly higher blue, bolt suppression
    .redLightPercentage   = 25,
    .nirLightPercentage   =  7,
};

inline const char *getStageName(enum growthStage stage) {
  if ((uint32_t)stage < sizeof(growthStageNames) / sizeof(growthStageNames[0]))
    return growthStageNames[stage];
  return "Unknown";
}
