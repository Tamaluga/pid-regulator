/******************************************************************************/
/*! \file Regulator.c
/******************************************************************************/

/* --------------------------------- imports ---------------------------------*/
#include "Regulator.h" /* Include Headerfile */
#include <math.h>
#include <assert.h>

/* ------------------------- module data declaration -------------------------*/

static struct RegulatorParam xMyRegulatorParam;

/* ----------------------- module procedure declaration ----------------------*/

void vRegSetParam(const struct RegulatorParam xRegulatorParam)
{
	assert(xRegulatorParam.xKp > 0.0);
	assert(xRegulatorParam.xKi > 0.0);
	assert(xRegulatorParam.xUpdateFrequency > 0.0);
	assert(xRegulatorParam.xTolerance > 0.0);
	assert(xRegulatorParam.xMinSystemInput < xRegulatorParam.xMaxSystemInput);
	xMyRegulatorParam = xRegulatorParam;
}

void vRegRegulate(const float xSystemOutput, float* xSystemInput)
{
	static float e = 0;		// error
	static float e_sum = 0; // error sum
	static float yP = 0;    // Proportional system input
	static float yI = 0;    // Integral system input
	static float y = 0;     // System input

	// Calculate error
	e = xMyRegulatorParam.xReference - xSystemOutput;

	// Set error to zero if its in the tolerance
	if (fabs(e) < xMyRegulatorParam.xTolerance)
	{
		e = 0;
	}

	// Proof oversteering of the control output (Anti-Windup)
	if ((y < xMyRegulatorParam.xMaxSystemInput) || (y > xMyRegulatorParam.xMinSystemInput))
	{
		e_sum += e;
	}

	// Proportional part
	yP = e * xMyRegulatorParam.xKp;

	// Integral part
	yI = xMyRegulatorParam.xKi * e_sum / xMyRegulatorParam.xUpdateFrequency;

	// Total error
	y = yP + yI;

	// Set input value
	*xSystemInput = y;
}