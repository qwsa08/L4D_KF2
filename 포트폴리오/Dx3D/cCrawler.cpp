#include "stdafx.h"
#include "cCrawler.h"
#include "cSkinnedMesh.h"
#include "cDijkstra.h"


cCrawler::cCrawler()
{
}


cCrawler::~cCrawler()
{
}

void cCrawler::Setup()
{
	ST_ZOMBIE stZombie;
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Crawler/", "ZED_Crawler.X");
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

void cCrawler::UpdateAndRender(D3DXVECTOR3 * vPlayerPos)
{
}

void cCrawler::SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion)
{
}

bool cCrawler::PickTheBullet(D3DXVECTOR3 * vPlayerPos, D3DXVECTOR3 * vPlayerDir)
{
	return false;
}
