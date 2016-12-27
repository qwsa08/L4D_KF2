#pragma once

#define g_pTimeManager cTimeManager::GetInstance()

class cTimeManager
{
private:
	SINGLETONE(cTimeManager);

private:
	DWORD m_dwLastTimeStamp;
	DWORD m_dwDeltaTime;

	float			m_fTimeElapsed;		//한프레임당 경과시간(1 / 60)
	unsigned long	m_frameRate;		//FPS
	unsigned long	m_FPSFrameCount;	//FPS카운트

public:
	void Update();
	float GetDeltaTime();

	int GetFPS();
};

