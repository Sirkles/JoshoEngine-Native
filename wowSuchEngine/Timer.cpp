#include "stdafx.h"

#include "JoshoEngine.h"
#include "Timer.h"

#include <chrono>
using namespace std::chrono;

using namespace JoshoEngine;

Timer::Timer()
{
	this->skipped = 0.0;
	this->isPaused = false;

	this->startTime = this->lastTime = this->clock.now();
}

double Timer::elapsed() const
{
	double ret = this->timeSince(lastTime) - this->skipped;

	if (this->isPaused)
		ret -= this->timeSince(this->pauseTime);

	return ret;
}

double Timer::tick()
{
	double ret = this->elapsed();
	this->reset();
	return ret;
}

double Timer::totalTime() const
{
	return this->timeSince(this->startTime) - this->skipped;
}

void Timer::reset()
{
	this->isPaused = false;
	this->skipped = 0.0;
	this->lastTime = this->clock.now();
}

void Timer::pause()
{
	if (!isPaused)
	{
		pauseTime = clock.now();
		isPaused = true;
	}
}

void Timer::resume()
{
	if (this->isPaused)
	{
		this->skipped += timeSince(this->pauseTime);
		this->isPaused = false;
	}
}

bool Timer::paused() const 
{
	return this->isPaused;
}

double Timer::timeSince(std::chrono::steady_clock::time_point old) const
{
	return duration_cast<duration<double>>(this->clock.now() - old).count();
}
