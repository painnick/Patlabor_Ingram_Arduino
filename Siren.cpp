#include "Arduino.h"
#include "Siren.h"

#define INIT_MILLS 10000
#define FREQ_MIN 634
#define FREQ_MAX 912

Siren::Siren(int pinNo, bool speedMode) : buzzerPinNo(pinNo),
                                                  lastMills(INIT_MILLS),
                                                  loopIndex(0),
                                                  lastFreq(FREQ_MIN),
                                                  toneDelay(1),
                                                  speedMode(speedMode)
{
    // Do something
}

void Siren::call(unsigned long mills)
{
    if ((loopIndex == 0) && (lastFreq > FREQ_MAX))
    {
        loopIndex = 1;
    }
    else if ((loopIndex == 1) && (lastFreq < FREQ_MIN))
    {
        loopIndex = 0;
    }

    if (speedMode)
    {
        toneDelay = 1;
    }
    else
    {
        if (loopIndex == 0)
            toneDelay = 3;
        else
            toneDelay = 7;
    }

    if (lastMills == INIT_MILLS || (mills - lastMills >= toneDelay))
    {
        tone(buzzerPinNo, lastFreq);

        if (loopIndex == 0)
        {
            lastFreq++;
        }
        else if (loopIndex == 1)
        {
            lastFreq--;
        }

        lastMills = mills;
    }
}
