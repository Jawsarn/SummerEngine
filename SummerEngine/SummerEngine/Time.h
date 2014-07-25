#pragma once
#include <Windows.h>

class Time
{
public:
	static Time* GetInstace();
	double GetDeltaTime();
	void Update();

private:
	static Time* m_Singleton;
	Time();
	~Time();

	ULONGLONG* m_PrevTime;
	DOUBLE* m_DeltaTime;
	DOUBLE* m_GameTime;
};

