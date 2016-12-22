#include "stdafx.h"
#include "cBoss.h"
#include "cSkinnedMesh.h"
#include "cDijkstra.h"


cBoss::cBoss()
{
}


cBoss::~cBoss()
{
}

void cBoss::Setup()
{
	ST_ZOMBIE stZombie;
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/BOSS_Patriarch/", "ZED_BOSS_Patriarch.X");
	stZombie.vPosition = D3DXVECTOR3(100, -130, 150);
	stZombie.fAngle = D3DX_PI;
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	stZombie.fSpeed = 3.f;
	m_vecSkinnedMesh.push_back(stZombie);
}

void cBoss::UpdateAndRender(D3DXVECTOR3 * vPlayerPos)
{
	for (int i = 0; i < m_vecSkinnedMesh.size(); ++i)
	{
		D3DXMATRIXA16 matS, matR, matT, mat;
		SetAnimationIndex(i, m_vecSkinnedMesh[i].eMotion);
		D3DXMatrixScaling(&matS, 0.6f, 0.6f, 0.6f);
		D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &m_vecSkinnedMesh[i].vDirection, &D3DXVECTOR3(0, 1, 0));
		D3DXMatrixTranspose(&matR, &matR);
		D3DXMatrixTranslation(&matT, m_vecSkinnedMesh[i].vPosition.x, m_vecSkinnedMesh[i].vPosition.y, m_vecSkinnedMesh[i].vPosition.z);

		mat = matS * matR * matT;

		m_vecSkinnedMesh[i].pSkinnedMesh->UpdateAndRender(&mat);
	}
}

void cBoss::SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion)
{
	switch (eMotion)
	{
	case IDLE:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(0);
		break;
	case MOVE:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(1);
		break;
	case SPRINT:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(1);
		break;
	case ATTACK_MELEE:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(2);
		break;
	case DIE:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(7);
		break;
	default:
		break;
	}
}
