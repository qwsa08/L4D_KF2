#include "StdAfx.h"
#include "cAutoReleasePool.h"

cAutoReleasePool::cAutoReleasePool(void)
{
}

cAutoReleasePool::~cAutoReleasePool(void)
{
}

void cAutoReleasePool::AddObject( cObject* pObject )
{
	m_setPool.insert(pObject);
}

void cAutoReleasePool::Drain()
{
	for each(auto p in m_setPool)
	{
		SAFE_RELEASE(p);
	}
	m_setPool.clear();
}
