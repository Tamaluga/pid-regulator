#ifndef __REGULATOR_H_
#define __REGULATOR_H_

/******************************************************************************/
/*! \file Regulator.h
/******************************************************************************/

/*Setters for controller paramenters*/
extern void RegulatorSetRegFactors(const float kp, const float ki, const float kd);
extern void RegulatorSetUpdateInterval(const unsigned long updateInterval_us);
extern void RegulatorSetReference(const float reference);
extern void RegulatorSetTolerance(const float tolerance);
extern void RegulatorSetMinMaxSystemInput(float minSystemInput, float maxSystemInput);
/*Getters for controller paramenters*/
extern float RegulatorGetKp();
extern float RegulatorGetKi();
extern float RegulatorGetKd();
extern float RegulatorGetReference();
extern unsigned long RegulatorGetUpdateInterval();
/*Must be called due to the parametrized frequency resp. interval*/
extern void RegulatorRegulate(const float systemOutput, float* systemInput);

#endif /* __REGULATOR_H_ */
