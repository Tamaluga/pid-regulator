// PID automated tuning (Ziegler-Nichols/relay method) for Arduino and compatible boards
// Copyright (c) 2016-2018 jackw01
// This code is distrubuted under the MIT License, see LICENSE for details

#ifndef PIDAUTOTUNER_H
#define PIDAUTOTUNER_H

#include <stdbool.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef enum
{
    ZNModeBasicPID,
    ZNModeLessOvershoot,
    ZNModeNoOvershoot
} ZNMode;

// Configure parameters for PID tuning
// See README for more details - https://github.com/jackw01/arduino-pid-autotuner/blob/master/README.md
// targetInputValue: the target value to tune to
// loopInterval: PID loop interval in microseconds - must match whatever the PID loop being tuned runs at
// outputRange: min and max values of the output that can be used to control the system (0, 255 for analogWrite)
// znMode: Ziegler-Nichols tuning mode (znModeBasicPID, znModeLessOvershoot, znModeNoOvershoot)
// tuningCycles: number of cycles that the tuning runs for (optional, default is 10)
extern void setTargetInputValue(float target);
extern void setLoopInterval(long interval);
extern void setOutputRange(float min, float max);
extern void setZNMode(ZNMode zn);
extern void setTuningCycles(int tuneCycles);

// Must be called immediately before the tuning loop starts
extern void startTuningLoop(unsigned long us);

// Automatically tune PID
// This function must be run in a loop at the same speed as the PID loop being tuned
// See README for more details - https://github.com/jackw01/arduino-pid-autotuner/blob/master/README.md
extern float tunePID(float input, unsigned long us);

// Get results of most recent tuning
extern float getKp();
extern float getKi();
extern float getKd();

extern bool isFinished(); // Is the tuning finished?

#endif
