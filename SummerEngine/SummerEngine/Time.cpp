#include "Time.h"

Time* Time::m_Singleton = nullptr;

Time* Time::GetInstace()
{
	if (m_Singleton == nullptr)
	{
		m_Singleton = new Time();
	}
	return m_Singleton;
}

Time::Time()
{
	m_DeltaTime = new DOUBLE();
	m_GameTime = new DOUBLE();
	m_PrevTime = new ULONGLONG();

	*m_DeltaTime = 0;
	*m_GameTime = 0;
	*m_PrevTime = 0;
}


Time::~Time()
{
}

void Time::Update()
{
	ULONGLONG timeCur = GetTickCount64();
	if (*m_PrevTime == 0)
		*m_PrevTime = timeCur;
	*m_DeltaTime = (timeCur - *m_PrevTime) / 1000.0f;
	*m_GameTime += *m_DeltaTime;
	*m_PrevTime = timeCur;
}

double Time::GetDeltaTime()
{
	return *m_DeltaTime;
}
