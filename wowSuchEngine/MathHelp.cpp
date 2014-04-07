#include "stdafx.h"

#include "MathHelp.h"

using namespace JoshoEngine;

// Linear interpolation
float MathHelp::lerp(float value1, float value2, float amount)
{
	return value1 + ((value2 - value1) * amount);
}

float MathHelp::toDegrees(float radians)
{
	// uses double internally.
	return (float)(radians * 57.295779513082320876798154814105);
}

float MathHelp::toRadians(float degrees)
{
	// uses double internally.
	return (float)(degrees * 0.017453292519943295769236907684886);
}

bool MathHelp::isPowerOfTwo(int value)
{
	return (value > 0) && ((value & (value - 1)) == 0);
}

unsigned int MathHelp::nextPowerOfTwo(unsigned int value)
{
	unsigned int rval = 1;

	while (rval < value) 
		rval <<= 1;

	return rval;
}
