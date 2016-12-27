#pragma once

#define g_pTimeManager cTimeManager::GetInstance()

class cTimeManager
{
private:
	SINGLETONE(cTimeManager);

private:
	DWORD m_dwLastTimeStamp;
	DWORD m_dwDeltaTime;

	float			m_fTimeElapsed;		//�������Ӵ� ����ð�(1 / 60)
	unsigned long	m_frameRate;		//FPS
	unsigned long	m_FPSFrameCount;	//FPSī��Ʈ

public:
	void Update();
	float GetDeltaTime();

	int GetFPS();
};

