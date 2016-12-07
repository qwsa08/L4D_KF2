#include "stdafx.h"
#include "cZombie.h"
#include "iMap.h"
#include "cObjMap.h"


cZombie::cZombie()
	: m_pMap(NULL)
	, m_vPosition(0, 0, 0)
{
}


cZombie::~cZombie()
{
	for each(auto p in m_vecSkinnedMesh)
	{
		SAFE_DELETE(p);
	}

	SAFE_RELEASE(m_pMap);
}

void cZombie::Setup()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	cObjMap* pObjMap = new cObjMap;
	pObjMap->Load("./Map/House14.ptop", &mat);
	m_pMap = pObjMap;
}
