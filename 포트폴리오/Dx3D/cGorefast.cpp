#include "stdafx.h"
#include "cGorefast.h"
#include "cSkinnedMesh.h"
#include "cDijkstra.h"


cGorefast::cGorefast()
{
}


cGorefast::~cGorefast()
{
}

void cGorefast::Setup()
{
	ST_ZOMBIE stZombie;
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Gorefast/", "ZED_Gorefast.X");
	stZombie.vPosition = D3DXVECTOR3(100, -140, 150);
	stZombie.fAngle = D3DX_PI / 2.0f;
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	stZombie.fSpeed = 3.f;
	m_vecSkinnedMesh.push_back(stZombie);
}

void cGorefast::UpdateAndRender(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, bool Shot)
{
}

void cGorefast::SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion)
{
}

bool cGorefast::PickTheBullet(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, int nZombieIndex)
{
	return false;
}
