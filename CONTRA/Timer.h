#pragma once
class Timer
{
public:
	static Timer* Instance();
	static void Release();
	void Reset();
	float DeltaTime();
	void TimeScale(float t);
	float TimeScale();
	void Update();
private:
	Timer();
	~Timer();
	static Timer* sInstance;

	unsigned int mStartedTicks;
	unsigned int mElapsedTicks;
	float mDeltaTime;
	float mTimeScale;
};

