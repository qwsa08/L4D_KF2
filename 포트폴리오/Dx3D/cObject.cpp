#include "StdAfx.h"
#include "cObject.h"


cObject::cObject(void)
	: m_nRefCount(1)
{
	g_pObjectManager->AddObject(this);
}

cObject::~cObject(void)
{
	assert(m_nRefCount == 0 && "�̷��� ����..");
	g_pObjectManager->RemoveObject(this);
}

void cObject::AddRef()
{
	assert(m_nRefCount != INT_MAX && "RefCount�� ��� ������ ������ �Ѿ�ϴ�.");
	++m_nRefCount;
}

void cObject::Release()
{
	assert(m_nRefCount > 0 && "�̷� ���� �� �߻��ؾߵ���??");

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
	assert(m_setObject.empty() && "������ cObject�� ��ӹ��� ��ü �� �������� ���� ��ü�� �ֽ��ϴ�.");
}
