#ifndef PLANTSELECTIONSCREEN_H
#define PLANTSELECTIONSCREEN_H

#include "plantProfiles.h"
#include "src/misc/lv_types.h"
#include <stdint.h>

extern const struct plantProfile *currentPlantProfile;

void drawPlantSelectionScreen(lv_obj_t *plantSelectScreen);

/* Index into the on-screen plant list, or 0xFFFFFFFF if not found. */
uint32_t plantSelection_indexOf(const struct plantProfile *p);
const struct plantProfile *plantSelection_profileAt(uint32_t index);
void plantSelection_refreshStyles(void);

#endif /* PLANTSELECTIONSCREEN_H */
