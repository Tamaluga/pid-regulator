#ifndef __REGULATOR_H_
#define __REGULATOR_H_

/******************************************************************************/
/*! \file Regulator.h
/******************************************************************************/

struct RegulatorParam
{
	float xKp;				// Proportional factor
	float xKi;				// Integration factor
	float xUpdateFrequency;	// Regulation frequency
	float xReference;		// Setpoint
	float xTolerance;		// Setpoint Tolerance
	float xMinSystemInput;	// Minimal value for actuating variable
	float xMaxSystemInput;	// Maximal value for actuating variable
};

/*Sets the the paramenter needed by the regulator parameters for the regulation*/
extern void vRegSetParam(const struct RegulatorParam xRegulatorParam);
/*Must be called due to the parametrized frequency resp. interval*/
extern void vRegRegulate(const float xSystemOutput, float* xSystemInput);

#endif /* __REGULATOR_H_ */
