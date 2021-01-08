/******************************************************************************/
/*! \file Regulator.c
/******************************************************************************/

/* --------------------------------- imports ---------------------------------*/
#include "Regulator.h" /* Include Headerfile */
#include <math.h>
#include <assert.h>

/* ------------------------- module data declaration -------------------------*/

float g_Kp = 0.0;		  		// Proportional factor
float g_Ki = 0.0;				// Integration factor
float g_Kd = 0.0;				// Differential factor
float g_UpdateInterval_us = 0.0;// Regulation interval
float g_Reference = 0.0;		// Setpoint
float g_Tolerance = 0.0;		// Setpoint Tolerance
float g_MinSystemInput = 0.0;	// Minimal value for actuating variable
float g_MaxSystemInput = 0.0;	// Maximal value for actuating variable

float g_E = 0.0;	 	// measured error
float g_ESum = 0.0; 	// error sum
float g_EOld = 0.0; 	// error sum
float g_YP = 0.0;	 	// Proportional system input
float g_YI = 0.0;	 	// Integral system input
float g_YD = 0.0;	 	// Differential system input
float g_Y = 0.0;	 	// Sum of yP and yI -> actual system input

/* ----------------------- module procedure declaration ----------------------*/

void RegulatorSetRegFactors(const float kp, const float ki, const float kd)
{
	g_Kp = kp;
	g_Ki = ki;
	g_Kd = kd;
}

void RegulatorSetUpdateInterval(const unsigned long updateInterval_us)
{
	assert(updateInterval_us > 0.0);
	g_UpdateInterval_us = updateInterval_us;
}

void RegulatorSetReference(const float reference)
{
	g_Reference = reference;
}

void RegulatorSetTolerance(const float tolerance)
{
	assert(tolerance > 0.0);
	g_Tolerance = tolerance;
}

void RegulatorSetMinMaxSystemInput(float minSystemInput, float maxSystemInput)
{
	assert(minSystemInput < maxSystemInput);
	g_MinSystemInput = minSystemInput;
	g_MaxSystemInput = maxSystemInput;
}

float RegulatorGetKp()
{
	return g_Kp;
}

float RegulatorGetKi()
{
	return g_Ki;
}

float RegulatorGetKd()
{
	return g_Kd;
}

extern float RegulatorGetReference()
{
	return g_Reference;
}

extern unsigned long RegulatorGetUpdateInterval()
{
	return g_UpdateInterval_us;
}

void RegulatorRegulate(const float systemOutput, float *systemInput)
{
	// Calculate error
	g_E = g_Reference - systemOutput;

	// Set error to zero if its in the tolerance
	if (fabs(g_E) < g_Tolerance)
	{
		g_E = 0;
	}

	// Proof oversteering of the control output (Anti-Windup)
	if ((g_Y < g_MaxSystemInput) || (g_Y > g_MinSystemInput))
	{
		g_ESum += g_E;
	}

	// Proportional part
	g_YP = g_E * g_Kp;

	// Integral part
	g_YI = g_Ki * g_ESum * (g_UpdateInterval_us * 0.000001);

	// Differential part
	g_YD = g_Kd * (g_E - g_EOld) / (g_UpdateInterval_us * 0.000001);

	// Total error
	g_Y = g_YP + g_YI;

	// Set input value
	*systemInput = g_Y;

	// Save error to previous error
	g_EOld = g_E;
}