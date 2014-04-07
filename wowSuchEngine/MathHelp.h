#ifndef JOSHOENGINE_MATH_HELP_H_
#define JOSHOENGINE_MATH_HELP_H_

#include "JoshoEngine.h"

namespace JoshoEngine
{
	class JOSHO_API MathHelp
	{
	public:
		static float lerp(float value1, float value2, float amount);

		static float toDegrees(float radians);
		static float toRadians(float degrees);

		static bool isPowerOfTwo(int value);
		static unsigned int nextPowerOfTwo(unsigned int value);
	};
}

#endif
