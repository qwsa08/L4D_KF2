#include "stdafx.h"
#include "cEnemyManager.h"
#include "cDijkstra.h"
#include "cZombie.h"
#include "cBloat.h"


cEnemyManager::cEnemyManager()
	: m_pDijkstra(NULL)
	, m_pBloat(NULL)
{
}


cEnemyManager::~cEnemyManager()
{
	SAFE_DELETE(m_pDijkstra);
	SAFE_DELETE(m_pBloat);
}

void cEnemyManager::Setup()
{
	m_pDijkstra = new cDijkstra;
	m_pDijkstra->Setup();

	m_pBloat = new cBloat;
	m_pBloat->Setup();
}

void cEnemyManager::UpdateAndRender(D3DXVECTOR3 * pTarget)
{
	m_pDijkstra->Render();

	m_pBloat->UpdateAndRender(pTarget);
}

void cEnemyManager::Update(D3DXVECTOR3 * pTarget)
{
}

void cEnemyManager::Render()
{
}
