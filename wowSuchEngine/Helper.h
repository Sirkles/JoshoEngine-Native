#ifndef JOSHOENGINE_HELPER_H_
#define JOSHOENGINE_HELPER_H_

namespace JoshoEngine
{
	class Helper
	{
	public:
		template<typename T>
		static T getMin(T a, T b)
		{
			return (a < b ? a : b);
		}

		template<typename T>
		static T getMax(T a, T b)
		{
			return (a > b ? a : b);
		}

		template <typename T>
		static T clamp(T val, T low, T high)
		{
			return val < low ? low : (val > high ? high : val);
		}
	};
}

#endif
