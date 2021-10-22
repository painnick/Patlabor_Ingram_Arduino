#include "Arduino.h"
#include "Siren.h"

#define FREQ_MIN 634
#define FREQ_MAX 912
#define SIREN_SPEED_MODE true

Siren::Siren(int pinNo) : buzzerPinNo(pinNo), lastMills(0), loopIndex(0), lastFreq(FREQ_MIN)
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

    if (lastMills == 0 || (mills - lastMills >= 5))
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
