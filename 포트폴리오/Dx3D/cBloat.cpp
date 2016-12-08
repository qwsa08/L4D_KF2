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

	for (int i = 0; i < 5; ++i)
	{
		cSkinnedMesh* pSkinnedMesh = new cSkinnedMesh("Zombie/Bloat/", "ZED_Bloat.X");

		switch (i)
		{
		case 0:
			pSkinnedMesh->SetPosition(D3DXVECTOR3(100, -182, 100));
			break;
		case 1:
			pSkinnedMesh->SetPosition(D3DXVECTOR3(10, -182, 10));
			break;
		case 2:
			pSkinnedMesh->SetPosition(D3DXVECTOR3(200, -182, 500));
			break;
		case 3:
			pSkinnedMesh->SetPosition(D3DXVECTOR3(1000, -182, -100));
			break;
		case 4:
			pSkinnedMesh->SetPosition(D3DXVECTOR3(-100, -182, -100));
			break;
		case 5:
			pSkinnedMesh->SetPosition(D3DXVECTOR3(-500, -182, 100));
			break;
		case 6:
			pSkinnedMesh->SetPosition(D3DXVECTOR3(-1000, -182, 100));
			break;
		case 7:
			pSkinnedMesh->SetPosition(D3DXVECTOR3(-300, -182, 100));
			break;
		case 8:
			pSkinnedMesh->SetPosition(D3DXVECTOR3(1500, -182, 100));
			break;
		case 9:
			pSkinnedMesh->SetPosition(D3DXVECTOR3(100, -182, 1050));
			break;
		}

		m_vecSkinnedMesh.push_back(pSkinnedMesh);
	}	
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
