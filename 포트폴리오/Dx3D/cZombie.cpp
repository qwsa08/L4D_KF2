#include "stdafx.h"
#include "cZombie.h"


cZombie::cZombie()
{
}


cZombie::~cZombie()
{
	for each(auto p in m_vecSkinnedMesh)
	{
		SAFE_DELETE(p.pSkinnedMesh);
	}
}