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
	pSkinnedMesh->SetPosition(D3DXVECTOR3(100, 0, 100));
	m_vecSkinnedMesh.push_back(pSkinnedMesh);
}

void cBloat::UpdateAndRender(D3DXMATRIXA16 * pmat, D3DXMATRIXA16 * pScal)
{
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	for each(auto p in m_vecSkinnedMesh)
	{
		D3DXVECTOR3 vPosition = m_vPosition;
		if (m_pMap->GetHeight(vPosition.x, vPosition.y, vPosition.z))
		{
			vPosition.y = -100;
			m_vPosition = vPosition;

			D3DXMATRIXA16 matT;
			D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
			p->UpdateAndRender(&matT, pScal);
		}
	}
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}
