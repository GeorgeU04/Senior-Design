#include "plantPersist.h"
#include "stm32h7xx_hal.h"
#include <stddef.h>
#include <string.h>

/* Last sector of Bank 2 — excluded from linker FLASH region (1920K). */
#define PLANT_PERSIST_ADDR 0x081E0000u
#define PLANT_PERSIST_MAGIC 0x504C4E54u /* "PLNT" */
#define PLANT_PERSIST_VERSION 1u

struct PlantPersistRecord {
  uint32_t magic;
  uint32_t version;
  uint32_t plantIndex;
  uint32_t growthDays;
  uint32_t crc;
  uint32_t reserved[3];
};

_Static_assert(sizeof(struct PlantPersistRecord) == 32,
               "PlantPersistRecord must be one H7 flash word");

static uint32_t crc32_calc(const uint8_t *data, uint32_t len) {
  uint32_t crc = 0xFFFFFFFFu;
  for (uint32_t i = 0; i < len; ++i) {
    crc ^= data[i];
    for (uint32_t b = 0; b < 8; ++b) {
      uint32_t mask = -(crc & 1u);
      crc = (crc >> 1) ^ (0xEDB88320u & mask);
    }
  }
  return ~crc;
}

static uint32_t record_crc(const struct PlantPersistRecord *rec) {
  /* CRC over fields preceding crc. */
  return crc32_calc((const uint8_t *)rec,
                    offsetof(struct PlantPersistRecord, crc));
}

uint8_t plantPersist_load(uint32_t *plantIndex, uint32_t *growthDays) {
  if (!plantIndex || !growthDays)
    return 0;

  const struct PlantPersistRecord *rec =
      (const struct PlantPersistRecord *)PLANT_PERSIST_ADDR;

  if (rec->magic != PLANT_PERSIST_MAGIC ||
      rec->version != PLANT_PERSIST_VERSION)
    return 0;
  if (rec->crc != record_crc(rec))
    return 0;

  *plantIndex = rec->plantIndex;
  *growthDays = rec->growthDays;
  return 1;
}

uint8_t plantPersist_save(uint32_t plantIndex, uint32_t growthDays) {
  /* Flash controller on H7 reads the program word over AXI — not DTCM stack. */
  static struct PlantPersistRecord progBuf __attribute__((aligned(32)));

  memset(&progBuf, 0, sizeof(progBuf));
  progBuf.magic = PLANT_PERSIST_MAGIC;
  progBuf.version = PLANT_PERSIST_VERSION;
  progBuf.plantIndex = plantIndex;
  progBuf.growthDays = growthDays;
  progBuf.crc = record_crc(&progBuf);

  if (HAL_FLASH_Unlock() != HAL_OK)
    return 0;

  FLASH_EraseInitTypeDef erase = {0};
  uint32_t sectorError = 0;
  erase.TypeErase = FLASH_TYPEERASE_SECTORS;
  erase.Banks = FLASH_BANK_2;
  erase.Sector = FLASH_SECTOR_7;
  erase.NbSectors = 1;
  erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;

  HAL_StatusTypeDef st = HAL_FLASHEx_Erase(&erase, &sectorError);
  if (st != HAL_OK) {
    HAL_FLASH_Lock();
    return 0;
  }

  st = HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, PLANT_PERSIST_ADDR,
                         (uint32_t)&progBuf);
  HAL_FLASH_Lock();
  return (st == HAL_OK) ? 1 : 0;
}
