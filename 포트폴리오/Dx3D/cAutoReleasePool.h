#pragma once

#define g_pAutoReleasePool cAutoReleasePool::GetInstance()

class cObject;

class cAutoReleasePool
{
private:
	SINGLETONE(cAutoReleasePool);

private:
	std::set<cObject*> m_setPool;

public:
	void AddObject(cObject* pObject);
	void Drain();
};

