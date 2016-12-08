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
	ST_ZOMBIE stZombie;
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Bloat/", "ZED_Bloat.X");
	stZombie.vPosition = D3DXVECTOR3(100, -120, 700);
	stZombie.fAngle = D3DX_PI / 2.0f;
	stZombie.eMotion = IDLE;	
	m_vecSkinnedMesh.push_back(stZombie);

	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Bloat/", "ZED_Bloat.X");
	stZombie.vPosition = D3DXVECTOR3(-270, -120, -900);
	stZombie.fAngle = D3DX_PI * 3 / 4.0f;
	stZombie.eMotion = IDLE;
	m_vecSkinnedMesh.push_back(stZombie);
}

void cBloat::UpdateAndRender()
{
	for each(auto p in m_vecSkinnedMesh)
	{
		p.pSkinnedMesh->SetAnimationIndex(p.eMotion);
		D3DXMATRIXA16 matS, matR, matT, mat;
		D3DXMatrixScaling(&matS, 0.7f, 0.7f, 0.7f);
		D3DXMatrixRotationY(&matR, p.fAngle);
		D3DXMatrixTranslation(&matT, p.vPosition.x, p.vPosition.y, p.vPosition.z);
		mat = matS * matR * matT;
		p.pSkinnedMesh->UpdateAndRender(&mat);
	}
}
