#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <time.h>
#include "Regulator.h"

#define AUTOTUNE

// Controller parameter
float xKp = 0.5;
float xKi = 0.05;
float xKd = 0.0;    // We want only a PI-Regulator
unsigned long updateInterval_us = 100000;
float reference = 37.0;
float tolerance = 0.001;
float minSystemInput = -24.0;
float maxSystemInput = 24.0;
// System parameter
float systemOutput = 10.0; // Actual value e.g. temperature
float systemInput = 0.0;   // Value for the actuator e.g. input voltage/current for peltier-element

int main(void)
{
    struct timespec timeInterval = {
        .tv_sec = 0,
        .tv_nsec = updateInterval_us * 1000};

    // Setup controller
    RegulatorSetRegFactors(xKp, xKi, xKd);
    RegulatorSetUpdateInterval(updateInterval_us);
    RegulatorSetReference(reference);
    RegulatorSetTolerance(tolerance);
    RegulatorSetMinMaxSystemInput(minSystemInput, maxSystemInput);

    // Regulate temperature
    printf("Regulate | Kp:%3f Ki:%.3f Ref:%.1f Int:%ldus\n",
           RegulatorGetKp(), RegulatorGetKi(), RegulatorGetReference(), RegulatorGetUpdateInterval());
    for (;;)
    {
        // Get the actual output value of the system -> temperature
        // systemOutput = getTemperature();
        RegulatorRegulate(systemOutput, &systemInput);

        printf("t:%.5f si:%.5f\n", systemOutput, systemInput);

        // Set the actuator
        // setPeltier(systemInput);
        systemOutput += systemInput / 2;

        nanosleep(&timeInterval, NULL);
    }

    return 0;
}