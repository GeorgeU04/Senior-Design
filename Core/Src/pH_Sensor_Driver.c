/*
 * pH_Sensor_Driver.c
 *
 * 	Peripherals Needed:
 * - ADC in
 * - 3.3 - 5V
 *
 *	***Adjust ADC pins as needed***
 *
 * CALIBRATION NOTES:
 * When calibrating, make sure probe is cleaned in purified or distilled water
 * let sensor sit in neutral water for atleast 5 seconds
 * wipe clean, let sit in pH 4 or 7 for atleast 5 seconds
 * record stable voltage reading of each
 * wash in neutral water more than once
 * wipe clean and store.
 * Take recorded pH 4 and 7 voltages and hardcode into slope formula
 */
#include "pH_Sensor_Driver.h"

struct pH pH_init(char *name) {
  struct pH sensor;

  float V4, V7;

  strncpy(sensor.name, name, sizeof(sensor.name));
  sensor.name[sizeof(sensor.name) - 1] = '\0';
  sensor.voltage = 0.0f;
  sensor.pHVal = 0.0f;
  sensor.slope = (4.0f - 7.0f) /
                 (1.95 - 1.44); // hard code V4 and V7 values. FORMAT: (V4 - V7)
  sensor.offset = 7.0f - (sensor.slope * (1.44)); // FORMAT: (sensor.slope* V7)
  return sensor;
}
/*
void calibrate_pH7(pH *sensor){
        readVoltage(&sensor);
        sensor->V7 = sensor->voltage;
}

void calibrate_pH4(pH *sensor){
        readVoltage(&sensor);
        sensor->V4 = sensor->voltage;
}
*/

// Reads analog sensor as voltage
void readVoltage(struct pH *sensor) {
  uint32_t adcValue = 0;

  for (int i = 0; i < 10; i++) {
    HAL_ADC_Start(&hadc2);
    HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY);
    adcValue += HAL_ADC_GetValue(&hadc2); // read 12-bit ADC
  }
  float volt = ((float)(adcValue / 10.0f) / 4095.0f) * 3.3f; // convert to volts
  sensor->voltage = volt;
}

// convert the voltage to pH
void voltageTopH(struct pH *sensor) {
  sensor->pHVal =
      (sensor->slope * sensor->voltage) + sensor->offset; // approximate pH
}

// USE THIS IN MAIN TO GET DATA
void readpH(struct pH *sensor) {
  readVoltage(sensor);
  voltageTopH(sensor);
}
