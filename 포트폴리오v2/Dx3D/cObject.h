#pragma once

class cObject
{
private:
	int m_nRefCount;

public:
	cObject(void);
	virtual ~cObject(void);

	void AddRef();
	void Release();
	void AutoRelease();
};

#define g_pObjectManager cObjectManager::GetInstance()

class cObjectManager
{
private:
	SINGLETONE(cObjectManager);
private:
	std::set<cObject*> m_setObject;

public:
	void AddObject(cObject* pObject);
	void RemoveObject(cObject* pObject);
	void Destroy();
};