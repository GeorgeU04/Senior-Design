#include "plantProfiles.h"
#include <stdint.h>

static const char *const growthStageNames[] = {
    "Early", "Late", "E.Bloom", "M.Bloom"};

/* Light stage tables from Downloads/plant_light_profiles.xlsx.
 * Temps kept from prior greenhouse targets (spreadsheet is lights-only).
 * White stays as previous on-level; sheet notes T5 white is not PWM-tuned. */

const struct plantProfile ARUGULA_PROFILE = {
    .name = "Arugula",
    .enclosureTemp = 22.0f,
    .waterTemp = 20.0f,
    .growthDurationDays = 28,
    .lightOnMinutes = 960,
    .whiteLightPercentage = 70,
    .stages =
        {
            {14, 15, 25, 5},  /* Early Growth */
            {10, 12, 28, 5},  /* Late Growth */
            {4, 8, 32, 8},    /* Early Bloom */
            {0, 0, 0, 0},     /* Mid-Late Bloom — not used */
        },
};

const struct plantProfile LETTUCE_PROFILE = {
    .name = "Lettuce",
    .enclosureTemp = 21.0f,
    .waterTemp = 19.0f,
    .growthDurationDays = 35,
    .lightOnMinutes = 960,
    .whiteLightPercentage = 65,
    .stages =
        {
            {18, 12, 25, 8},
            {12, 10, 28, 8},
            {5, 8, 32, 10},
            {0, 0, 0, 0},
        },
};

const struct plantProfile BASIL_PROFILE = {
    .name = "Basil",
    .enclosureTemp = 24.0f,
    .waterTemp = 22.0f,
    .growthDurationDays = 35,
    .lightOnMinutes = 960,
    .whiteLightPercentage = 75,
    .stages =
        {
            {14, 14, 26, 10},
            {12, 12, 28, 10},
            {5, 10, 32, 12},
            {4, 8, 35, 15},
        },
};

const struct plantProfile SPINACH_PROFILE = {
    .name = "Spinach",
    .enclosureTemp = 19.0f,
    .waterTemp = 18.0f,
    .growthDurationDays = 40,
    .lightOnMinutes = 840,
    .whiteLightPercentage = 65,
    .stages =
        {
            {20, 15, 25, 5},
            {14, 12, 28, 5},
            {6, 8, 30, 7},
            {0, 0, 0, 0},
        },
};

const struct plantProfile KALE_PROFILE = {
    .name = "Kale",
    .enclosureTemp = 20.0f,
    .waterTemp = 19.0f,
    .growthDurationDays = 55,
    .lightOnMinutes = 960,
    .whiteLightPercentage = 70,
    .stages =
        {
            {25, 13, 25, 10},
            {18, 11, 28, 10},
            {8, 9, 32, 12},
            {4, 7, 35, 14},
        },
};

const struct plantProfile BOK_CHOY_PROFILE = {
    .name = "Bok Choy",
    .enclosureTemp = 21.0f,
    .waterTemp = 19.0f,
    .growthDurationDays = 35,
    .lightOnMinutes = 960,
    .whiteLightPercentage = 70,
    .stages =
        {
            {18, 13, 25, 9},
            {12, 11, 28, 9},
            {5, 8, 30, 11},
            {0, 0, 0, 0},
        },
};

const struct plantProfile SWISS_CHARD_PROFILE = {
    .name = "Swiss Chard",
    .enclosureTemp = 21.0f,
    .waterTemp = 20.0f,
    .growthDurationDays = 50,
    .lightOnMinutes = 960,
    .whiteLightPercentage = 70,
    .stages =
        {
            {22, 12, 23, 10},
            {18, 10, 26, 10},
            {7, 8, 30, 12},
            {3, 6, 33, 13},
        },
};

const struct plantProfile CILANTRO_PROFILE = {
    .name = "Cilantro",
    .enclosureTemp = 20.0f,
    .waterTemp = 19.0f,
    .growthDurationDays = 35,
    .lightOnMinutes = 840,
    .whiteLightPercentage = 65,
    .stages =
        {
            {14, 16, 22, 5},
            {12, 13, 25, 5},
            {5, 10, 28, 7},
            {4, 8, 30, 10},
        },
};

const struct plantProfile PARSLEY_PROFILE = {
    .name = "Parsley",
    .enclosureTemp = 21.0f,
    .waterTemp = 20.0f,
    .growthDurationDays = 60,
    .lightOnMinutes = 960,
    .whiteLightPercentage = 70,
    .stages =
        {
            {28, 12, 23, 12},
            {20, 10, 26, 12},
            {8, 8, 30, 13},
            {4, 6, 33, 15},
        },
};

const struct plantProfile MINT_PROFILE = {
    .name = "Mint",
    .enclosureTemp = 22.0f,
    .waterTemp = 20.0f,
    .growthDurationDays = 45,
    .lightOnMinutes = 960,
    .whiteLightPercentage = 70,
    .stages =
        {
            {20, 12, 24, 12},
            {15, 10, 27, 12},
            {7, 8, 30, 14},
            {3, 6, 33, 16},
        },
};

const struct plantProfile GREEN_ONION_PROFILE = {
    .name = "Green Onion",
    .enclosureTemp = 21.0f,
    .waterTemp = 19.0f,
    .growthDurationDays = 35,
    .lightOnMinutes = 840,
    .whiteLightPercentage = 65,
    .stages =
        {
            {18, 12, 23, 8},
            {12, 10, 26, 8},
            {5, 8, 28, 10},
            {0, 0, 0, 0},
        },
};

const struct plantProfile ROMAINE_PROFILE = {
    .name = "Romaine",
    .enclosureTemp = 21.0f,
    .waterTemp = 19.0f,
    .growthDurationDays = 45,
    .lightOnMinutes = 960,
    .whiteLightPercentage = 65,
    .stages =
        {
            {22, 12, 25, 8},
            {15, 10, 28, 8},
            {8, 8, 32, 10},
            {0, 0, 0, 0},
        },
};

const struct plantProfile BUTTERHEAD_PROFILE = {
    .name = "Butterhead Lettuce",
    .enclosureTemp = 20.0f,
    .waterTemp = 19.0f,
    .growthDurationDays = 35,
    .lightOnMinutes = 960,
    .whiteLightPercentage = 65,
    .stages =
        {
            {18, 12, 25, 8},
            {12, 10, 28, 8},
            {5, 8, 30, 10},
            {0, 0, 0, 0},
        },
};

const struct plantProfile MUSTARD_GREENS_PROFILE = {
    .name = "Mustard Greens",
    .enclosureTemp = 20.0f,
    .waterTemp = 19.0f,
    .growthDurationDays = 30,
    .lightOnMinutes = 960,
    .whiteLightPercentage = 70,
    .stages =
        {
            {14, 14, 25, 7},
            {12, 11, 28, 7},
            {4, 8, 30, 9},
            {0, 0, 0, 0},
        },
};

const char *getStageName(enum growthStage stage) {
  if ((uint32_t)stage < GROWTH_STAGE_COUNT)
    return growthStageNames[stage];
  return "Unknown";
}

enum growthStage plant_getStage(const struct plantProfile *profile,
                                uint32_t growthDay) {
  if (!profile)
    return EARLY_GROWTH;

  uint32_t day = growthDay == 0 ? 1 : growthDay;
  uint32_t cursor = 0;

  for (uint32_t i = 0; i < GROWTH_STAGE_COUNT; ++i) {
    uint16_t dur = profile->stages[i].durationDays;
    if (dur == 0)
      continue;
    cursor += dur;
    if (day <= cursor)
      return (enum growthStage)i;
  }

  /* Past tabulated stages — stay on last defined stage */
  for (int i = GROWTH_STAGE_COUNT - 1; i >= 0; --i) {
    if (profile->stages[i].durationDays != 0)
      return (enum growthStage)i;
  }
  return EARLY_GROWTH;
}

uint8_t plant_getStageLights(const struct plantProfile *profile,
                             enum growthStage stage, uint8_t *blue,
                             uint8_t *red, uint8_t *nir) {
  if (!profile || stage >= GROWTH_STAGE_COUNT)
    return 0;

  const struct lightStage *s = &profile->stages[stage];
  if (s->durationDays == 0)
    return 0;

  if (blue)
    *blue = s->bluePct;
  if (red)
    *red = s->redPct;
  if (nir)
    *nir = s->nirPct;
  return 1;
}
