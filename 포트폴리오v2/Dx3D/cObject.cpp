#include "StdAfx.h"
#include "cObject.h"


cObject::cObject(void)
	: m_nRefCount(1)
{
	g_pObjectManager->AddObject(this);
}

cObject::~cObject(void)
{
	assert(m_nRefCount == 0 && "이러지 말자..");
	g_pObjectManager->RemoveObject(this);
}

void cObject::AddRef()
{
	assert(m_nRefCount != INT_MAX && "RefCount가 사용 가능한 범위를 넘어섭니다.");
	++m_nRefCount;
}

void cObject::Release()
{
	assert(m_nRefCount > 0 && "이런 일이 왜 발생해야되죠??");

	--m_nRefCount;
	if (m_nRefCount == 0)
	{
		delete this;
	}
}

void cObject::AutoRelease()
{
	g_pAutoReleasePool->AddObject(this);
}

cObjectManager::cObjectManager()
{

}

cObjectManager::~cObjectManager()
{

}

void cObjectManager::AddObject( cObject* pObject )
{
	m_setObject.insert(pObject);
}

void cObjectManager::RemoveObject( cObject* pObject )
{
	m_setObject.erase(pObject);
}

void cObjectManager::Destroy()
{
	assert(m_setObject.empty() && "생성된 cObject를 상속받은 객체 중 삭제되지 않은 객체가 있습니다.");
}
