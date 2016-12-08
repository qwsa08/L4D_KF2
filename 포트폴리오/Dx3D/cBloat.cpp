#include "stdafx.h"
#include "cBloat.h"
#include "cSkinnedMesh.h"
#include "iMap.h"
#include "cObjMap.h"


cBloat::cBloat()
{
}


cBloat::~cBloat()
{
}

void cBloat::Setup()
{
	cZombie::Setup();

	cSkinnedMesh* pSkinnedMesh = new cSkinnedMesh("Zombie/Bloat/", "ZED_Bloat.X");
	pSkinnedMesh->SetPosition(D3DXVECTOR3(100, -180, 100));
	m_vecSkinnedMesh.push_back(pSkinnedMesh);
}

void cBloat::UpdateAndRender()
{
	for each(auto p in m_vecSkinnedMesh)
	{
		D3DXMATRIXA16 matT, matS;
		D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
		D3DXMatrixScaling(&matS, 0.7f, 0.7f, 0.7f);
		p->UpdateAndRender(&matT, &matS);
	}
}
