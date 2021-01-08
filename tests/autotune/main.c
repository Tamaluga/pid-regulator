#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "Regulator.h"
#include "pidautotuner.h"


// Controller parameter
unsigned long updateInterval_us = 100000;
float reference = 37.0;
float tolerance = 0.001;
float minSystemInput = -2.5;
float maxSystemInput = 2.5;
// System parameter
float systemOutput = 20.0; // Actual value e.g. temperature
float systemInput = 0.0;   // Value for the actuator e.g. input voltage/current for peltier-element

unsigned long getActualTimeInMicroSeconds();

int main(void)
{
    struct timespec timeInterval = {
        .tv_sec = 0,
        .tv_nsec = updateInterval_us * 1000};

    //
    // Autotune
    //

    // Setup

    // Set the target value to tune to
    // This will depend on what you are tuning. This should be set to a value within
    // the usual range of the setpoint. For low-inertia systems, values at the lower
    // end of this range usually give better results. For anything else, start with a
    // value at the middle of the range.
    setTargetInputValue(reference);

    // Set the loop interval in microseconds
    // This must be the same as the interval the PID control loop will run at
    setLoopInterval(updateInterval_us);

    // Set the output range
    // These are the maximum and minimum possible output values of whatever you are
    // using to control the system (analogWrite is 0-255)
    setOutputRange(minSystemInput, maxSystemInput);

    // Set the Ziegler-Nichols tuning mode
    // Set it to either PIDAutotuner::ZNModeBasicPID, PIDAutotuner::ZNModeLessOvershoot,
    // or PIDAutotuner::ZNModeNoOvershoot. Test with ZNModeBasicPID first, but if there
    // is too much overshoot you can try the others.
    setZNMode(ZNModeBasicPID);

    // This must be called immediately before the tuning loop
    startTuningLoop(getActualTimeInMicroSeconds());

    // Run a loop until tuner.isFinished() returns true
    unsigned long us;
    while (!isFinished())
    {
        unsigned long us = getActualTimeInMicroSeconds();
        // Get input value for autotuner (temperature, encoder position, velocity, etc)
        // systemOutput=getTemperature();

        // Call tunePID() with the input value
        systemInput = tunePID(systemOutput, us);

        // Do somehing to set the output - tunePID() will return values within the range
        // configured by setOutputRange(). Don't change the value or the tuning results
        // will be incorrect.
        // setPeltier(systemInput);
        systemOutput += systemInput * 0.05 + 0.1;
        printf("AutoTune | Output:%.5f\n", systemOutput);
        while( (getActualTimeInMicroSeconds() - us) < updateInterval_us)
        {
            static struct timespec timeInterval_1 = {
                .tv_sec = 0,
                .tv_nsec = 1000};
            nanosleep(&timeInterval_1, NULL);
        }    
    }
    printf("AutoTune | Kp:%.5f Ki:%.5f Kd:%.5f\n", getKp(), getKi(), getKd());


    //
    // Regulate
    //

    // Setup controller
    RegulatorSetRegFactors(getKp(), getKi(), getKd());
    RegulatorSetUpdateInterval(updateInterval_us);
    RegulatorSetReference(reference);
    RegulatorSetTolerance(tolerance);
    RegulatorSetMinMaxSystemInput(minSystemInput, maxSystemInput);

    // Regulate temperature
    printf("Regulate | Kp:%3f Ki:%.3f Kd:%.3f Ref:%.1f Int:%ldus\n",
           RegulatorGetKp(), RegulatorGetKi(), RegulatorGetKd(), RegulatorGetReference(), RegulatorGetUpdateInterval());
    for (;;)
    {
        // Get the actual output value of the system -> temperature
        // systemOutput = getTemperature();
        RegulatorRegulate(systemOutput, &systemInput);

        printf("t:%.5f si:%.5f\n", systemOutput, systemInput);

        // Set the actuator
        // setPeltier(systemInput);
        systemOutput += systemInput * 0.05 + 0.1;

        nanosleep(&timeInterval, NULL);
    }

    return 0;
}


unsigned long getActualTimeInMicroSeconds()
{
    static struct timeval tv;
    gettimeofday(&tv, NULL);
    return 1000000 * tv.tv_sec + tv.tv_usec;
}