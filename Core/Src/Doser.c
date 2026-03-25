/* Doser.c
*	
* Setup:
*
* Init pump
* Init new doser (use doser_init())
* 	In main() while loop:
*		doser_update()
*		if(sensor conditions)
*			doser_start()
*
*/

#include "Doser.h"

static uint32_t doser_volumeToTimeMs(Doser *doser, float volume){	// calculates the time to turn on pump to dispense X amount of liquid in mL
	//error checking
    if (doser == NULL || doser->mlPerSecond <= 0.0f || volume <= 0.0f)
    {
        return 0;
    }

    // time (ms) = volume (mL) / rate (mL/s) * 1000
    float time = (volume / doser->mlPerSecond)*1000.0f;

    if (time < 1.0f)
    {
        time = 1.0f;
    }

    return (uint32_t)time;
}

void doser_init(Doser *doser, Pump *pump, float mlPerSecond,float stepVolumeMl, uint32_t mixDelayMs){
    if (doser == NULL)
    {
        return;
    }
	

    doser->pump = pump;
    doser->mlPerSecond = mlPerSecond;
    doser->targetVolumeMl = 0.0f;
    doser->remainingVolumeMl = 0.0f;
    doser->stepVolumeMl = stepVolumeMl;
    doser->mixDelayMs = mixDelayMs;
    doser->lastEventTime = 0;
    doser->active = 0;
    doser->waitingForMix = 0;
    doser->waitingForPump = 0;
	
	if (mlPerSecond <= 0.0f || stepVolumeMl <= 0.0f)
	{
		doser->mlPerSecond = 0.0f;
		doser->stepVolumeMl = 0.0f;
	}
}

void doser_start(Doser *doser, float volumeMl){
    if (doser == NULL || doser->pump == NULL) //error checking
    {
        return;
    }
    if (volumeMl <= 0.0f)
    {
        return;
    }
    if (doser->active)     //if already active, move do not start 
    {
        return;
    }

    doser->targetVolumeMl = volumeMl;
    doser->remainingVolumeMl = volumeMl;
    doser->lastEventTime = 0;
    doser->active = 1;
    doser->waitingForMix = 0;
    doser->waitingForPump = 0;
}

void doser_update(Doser *doser){
    uint32_t now;
    float currentStepMl;
    uint32_t runTimeMs;

    if (doser == NULL || doser->pump == NULL)
    {
        return;
    }

    
    checkPump(doser->pump);	// let the pump update 

    if (!doser->active)
    {
        return;
    }
	
	if (doser->stepVolumeMl <= 0.0f)
	{
		doser->active = 0;
		return;
	}

    now = HAL_GetTick();

    if (doser->pump->RUNFLAG)	// If pump is running, wait for completion
    {
        doser->waitingForPump = 1;
        return;
    }

    if (doser->waitingForPump)	//When pump finished, waiting state is active
    {
        doser->waitingForPump = 0;
        doser->waitingForMix = 1;
        doser->lastEventTime = now;
        return;
    }

    if (doser->waitingForMix)  // Wait for mixing to complete
    {
        if ((now - doser->lastEventTime) < doser->mixDelayMs)
        {
            return;
        }

        doser->waitingForMix = 0;
    }

    if (doser->remainingVolumeMl <= 0.0f) // Set doser inactive if volume is satisfied
    {
        doser->active = 0;
        return;
    }

    currentStepMl = doser->stepVolumeMl;
	
    if (doser->remainingVolumeMl < doser->stepVolumeMl)
    {
        currentStepMl = doser->remainingVolumeMl;
    }

    runTimeMs = doser_volumeToTimeMs(doser, currentStepMl);

    if (runTimeMs == 0)
    {
        doser->active = 0;
        return;
    }

    runPump(doser->pump, runTimeMs);
    doser->remainingVolumeMl -= currentStepMl;
    doser->waitingForPump = 1;
}

uint8_t doser_isBusy(Doser *doser){
    if (doser == NULL || doser->pump == NULL)
    {
        return 0;
    }

    if (doser->active || doser->pump->RUNFLAG)
    {
        return 1;
    }

    return 0;
}

void doser_reset(Doser *doser){
    if (doser == NULL)
    {
        return;
    }
    doser->targetVolumeMl = 0.0f;
    doser->remainingVolumeMl = 0.0f;
    doser->lastEventTime = 0;
    doser->active = 0;
    doser->waitingForMix = 0;
    doser->waitingForPump = 0;
}