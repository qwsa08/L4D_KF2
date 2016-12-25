#include "stdafx.h"
#include "cZombie.h"


cZombie::cZombie()
	: m_pDijkstra(NULL)
	, m_pFrustum(NULL)
{
}


cZombie::~cZombie()
{
	for each(auto p in m_vecSkinnedMesh)
	{
		SAFE_DELETE(p.pSkinnedMesh);
	}
//	SAFE_DELETE(m_pDijkstra);
//	SAFE_DELETE(m_pOBB);
//	SAFE_DELETE(m_pFrustum);
}