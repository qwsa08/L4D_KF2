#pragma once

#define g_pTimeManager cTimeManager::GetInstance()

class cTimeManager
{
private:
	SINGLETONE(cTimeManager);

private:
	DWORD m_dwLastTimeStamp;
	DWORD m_dwDeltaTime;

public:
	void Update();
	float GetDeltaTime();
};

