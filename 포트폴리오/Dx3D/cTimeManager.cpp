#include "StdAfx.h"
#include "cTimeManager.h"


cTimeManager::cTimeManager(void)
	: m_dwDeltaTime(0)
	, m_dwLastTimeStamp(GetTickCount())
	, m_fTimeElapsed(0.f)
{
}

cTimeManager::~cTimeManager(void)
{
}

void cTimeManager::Update()
{
	DWORD dwCurr = GetTickCount();
	m_dwDeltaTime = dwCurr - m_dwLastTimeStamp;
	m_dwLastTimeStamp = dwCurr;

	//프레임 초기화를 1초마다 진행하기
	if (m_fTimeElapsed > 1.0f)
	{
		m_frameRate = m_FPSFrameCount;
		m_FPSFrameCount = 0;
		m_fTimeElapsed = 0.0f;
	}
}

float cTimeManager::GetDeltaTime()
{
	return m_dwDeltaTime / 1000.f;
}

int cTimeManager::GetFPS()
{
	return m_frameRate;
}
