#ifndef JOSHOENGINE_TIMER_H_
#define JOSHOENGINE_TIMER_H_

#include "JoshoEngine.h"
#include <chrono>

namespace JoshoEngine
{
	class JOSHO_API Timer
	{
	public:
		// Instantiates new Timer instance.
		Timer();

		//Returns the amount of time in seconds that has elapsed since the last time the timer was reset.
		double elapsed() const;

		// Returns the amount of time in seconds that has elapsed since the last time the timer was reset, and then resets it.
		double tick();

		// Returns the amount of time in seconds since the timer was started.
		double totalTime() const;

		// Resets the timer to 0.
		void reset();

		// Pauses the timer.
		void pause();

		// Resumes the timer.
		void resume();

		// Returns true if the timer is currently paused, false otherwise.
		bool paused() const;

	private:
		std::chrono::steady_clock clock;
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point lastTime;
		std::chrono::steady_clock::time_point pauseTime;
		double skipped;
		bool isPaused;

		double timeSince(std::chrono::steady_clock::time_point) const;
	};
}

#endif
