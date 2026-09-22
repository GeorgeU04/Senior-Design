#ifndef PLANTPERSIST_H
#define PLANTPERSIST_H

#include <stdint.h>

/* No plant selected / cleared selection in flash. */
#define PLANT_PERSIST_NONE 0xFFFFFFFFu

/**
 * Load persisted plant index and growth day from internal Flash.
 * Returns 1 if a valid record was found, 0 otherwise.
 */
uint8_t plantPersist_load(uint32_t *plantIndex, uint32_t *growthDays);

/**
 * Save plant index and growth day to the reserved Flash sector.
 * Returns 1 on success, 0 on failure.
 */
uint8_t plantPersist_save(uint32_t plantIndex, uint32_t growthDays);

#endif /* PLANTPERSIST_H */
