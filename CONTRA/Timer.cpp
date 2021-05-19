#include "Timer.h"
#include "SDL.h"
Timer* Timer::sInstance = NULL;


Timer* Timer::Instance()
{
	if (!sInstance)
		sInstance = new Timer();
	return sInstance;
}

void Timer::Release()
{
	delete sInstance;
	sInstance = NULL;
}

void Timer::Reset()
{
	mStartedTicks = SDL_GetTicks();
	mElapsedTicks = 0;
	mDeltaTime = 0;
}

float Timer::DeltaTime()
{
	return mDeltaTime;
}

void Timer::TimeScale(float t)
{
	mTimeScale = t;
}

float Timer::TimeScale()
{
	return mTimeScale;
}

void Timer::Update()
{
	mElapsedTicks = SDL_GetTicks() - mStartedTicks;
	mDeltaTime = mElapsedTicks * 0.001f;
}

Timer::Timer()
{
	Reset();
	mTimeScale = 1.0f;
}

Timer::~Timer()
{
	
}
