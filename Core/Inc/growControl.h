#ifndef GROWCONTROL_H
#define GROWCONTROL_H

#include "FeedProfile.h"
#include "TDS_Sensor_Driver.h"
#include "climateControl.h"
#include "fans.h"
#include "pH_Sensor_Driver.h"
#include "plantProfiles.h"
#include <stdint.h>

typedef enum {
  GROW_STATE_IDLE = 0,     /* no plant selected */
  GROW_STATE_RUNNING,      /* normal closed-loop control */
  GROW_STATE_REFILL,       /* water low — pause chemistry */
  GROW_STATE_FAULT         /* invalid sensors — safe actuators */
} GrowControlState;

typedef struct {
  float waterTempC;
  float enclosureTempC;
  uint8_t waterTempValid;
  uint8_t enclosureTempValid;
  float pH;
  float EC; /* mS/cm */
  uint32_t waterLevelRaw;
  uint8_t hour;   /* 0-23 from RTC */
  uint8_t minute; /* 0-59 */
  uint32_t growthDay;
} GrowSensorSample;

void growControl_init(struct fan *enclosureFan, struct fan *auxFan,
                      struct cooler *cooler, struct TDS *tds, struct pH *ph);

/* Select/clear the active plant. Pass NULL to idle. */
void growControl_setPlant(const struct plantProfile *profile);

/* Call every main-loop iteration with latest sensor sample. */
void growControl_update(const GrowSensorSample *sample);

GrowControlState growControl_getState(void);
enum growthStage growControl_getStage(void);
uint8_t growControl_lightsAreOn(void);
const struct plantProfile *growControl_getPlant(void);

#endif /* GROWCONTROL_H */
