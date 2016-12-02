#include "StdAfx.h"
#include "cTimeManager.h"


cTimeManager::cTimeManager(void)
	: m_dwDeltaTime(0)
	, m_dwLastTimeStamp(GetTickCount())
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
}

float cTimeManager::GetDeltaTime()
{
	return m_dwDeltaTime / 1000.f;
}
