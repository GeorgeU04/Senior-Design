/* Doser.h
*	
*	Flow: 
*	->start pump step 
*	-> subtract step from remaining volume 
*	-> wait for pump to complete 
*	-> wait for mixing 
*	-> if remaining volume is '0', set inactive
*
*/

#include "main.h"
#include "PeristalticPump.h"
#include <stdint.h>

typedef struct{
    Pump *pump;                  

    float mlPerSecond;           // flow rate; should be 1.5 mL/sec
    float targetVolumeMl;        // Total volume to be dispensed
    float remainingVolumeMl;     // tracks volume left to dispense
    float stepVolumeMl;          // maximum mL output per step or pulse

    uint32_t mixDelayMs;         // delay for mixing after dispensing
    uint32_t lastEventTime;      // tracking mix timing
	
	//states to keep track of
    uint8_t active;              // current state '1' = active, '0' = off
    uint8_t waitingForMix;       // state if system is mixing
    uint8_t waitingForPump;      // state if pump is running
} Doser;

void doser_init(Doser *doser, Pump *pump, float mlPerSecond, float stepVolumeMl, uint32_t mixDelayMs);

void doser_start(Doser *doser, float volumeMl); // Start a new dose command in mL
void doser_update_inverted(Doser *doser); // call this every loop to update the doser
void doser_update_noninverted(Doser *doser); // call this every loop to update the doser

uint8_t doser_isBusy(Doser *doser); // Returns 1 if doser is busy, 0 if idle

void doser_reset(Doser *doser); // Stop and clear current job
