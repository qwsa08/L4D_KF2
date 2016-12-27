#include "stdafx.h"
#include "cEnemyManager.h"
#include "cDijkstra.h"
#include "cZombie.h"
#include "cBloat.h"
#include "cClot.h"
#include "cCrawler.h"
#include "cGorefast.h"
#include "cBoss.h"
#include "cCrtController.h"


cEnemyManager::cEnemyManager()
	: m_pDijkstra(NULL)
	, m_pBloat(NULL)
	, m_pClot(NULL)
	, m_pCrawler(NULL)
	, m_pGorefast(NULL)
	, m_pBoss(NULL)
{
}


cEnemyManager::~cEnemyManager()
{
	SAFE_DELETE(m_pDijkstra);
	SAFE_DELETE(m_pBloat);
	SAFE_DELETE(m_pClot);
	SAFE_DELETE(m_pCrawler);
	SAFE_DELETE(m_pGorefast);
	SAFE_DELETE(m_pBoss);
}

void cEnemyManager::Setup()
{
	m_pDijkstra = new cDijkstra;
	m_pDijkstra->Setup();

	m_pBloat = new cBloat;
	m_pBloat->Setup();
	m_pBloat->SetDijkstraMemoryLink(m_pDijkstra);

	m_pClot = new cClot;
	m_pClot->Setup();
	m_pClot->SetDijkstraMemoryLink(m_pDijkstra);

	m_pCrawler = new cCrawler;
	m_pCrawler->Setup();
	m_pCrawler->SetDijkstraMemoryLink(m_pDijkstra);

	m_pGorefast = new cGorefast;
	m_pGorefast->Setup();
	m_pGorefast->SetDijkstraMemoryLink(m_pDijkstra);

	m_pBoss = new cBoss;
	m_pBoss->Setup();
	m_pBoss->SetDijkstraMemoryLink(m_pDijkstra);
	
}

void cEnemyManager::UpdateAndRender(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, bool* Shot, GUN_NAME ePlayerGun)
{
	m_pBloat->UpdateAndRender(vPlayerPos, vPlayerDir, Shot, ePlayerGun);
	m_pClot->UpdateAndRender(vPlayerPos, vPlayerDir, Shot, ePlayerGun);
	m_pCrawler->UpdateAndRender(vPlayerPos, vPlayerDir, Shot, ePlayerGun);
	m_pGorefast->UpdateAndRender(vPlayerPos, vPlayerDir, Shot, ePlayerGun);
	m_pBoss->UpdateAndRender(vPlayerPos, vPlayerDir, Shot, ePlayerGun);

//	m_pDijkstra->Update(vPlayerPos);
//	m_pDijkstra->Render();
}
bool cEnemyManager::PickTheMonster(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir)
{
//	if(m_pClot->PickTheBullet(vPlayerPos, vPlayerDir)) return true;
//	else return false;

	return true;
}
bool cEnemyManager::PickThePlayer(ST_OBB* s_Player, OUT D3DXVECTOR3& monDirection)
{
	if (m_pClot->PickThePlayer(s_Player, monDirection))
	{
		return true;
	}
	return false;
}