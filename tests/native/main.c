#define _POSIX_C_SOURCE       199309L

#include <stdio.h>
#include <time.h>
#include "Regulator.h"

int main(void)
{
    struct RegulatorParam regParam = {
        .xKp = 0.5,
        .xKi = 0.5,
        .xUpdateFrequency = 10.0,
        .xReference = 37.0,
        .xTolerance = 0.001,
        .xMinSystemInput = -24.0,
        .xMaxSystemInput = 24.0
    };

    struct timespec timeInterval = {
        .tv_sec = 0,
        .tv_nsec = (1/regParam.xUpdateFrequency)*1000000000
    };

    float actualTemperature = 10.0;
    float systemInput = 0.0;

    vRegSetParam(regParam);

    for(;;)
    {
        vRegRegulate(actualTemperature, &systemInput);

        printf("t:%.5f si:%.5f\n", actualTemperature, systemInput);

        actualTemperature += systemInput;

        nanosleep(&timeInterval, NULL);
    }

    return 0;
}