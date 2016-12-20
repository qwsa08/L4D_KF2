#include "stdafx.h"
#include "cEnemyManager.h"
#include "cDijkstra.h"
#include "cZombie.h"
#include "cBloat.h"
#include "cClot.h"
#include "cCrtController.h"


cEnemyManager::cEnemyManager()
	: m_pDijkstra(NULL)
	, m_pBloat(NULL)
	, m_pClot(NULL)
{
}


cEnemyManager::~cEnemyManager()
{
	SAFE_DELETE(m_pDijkstra);
	SAFE_DELETE(m_pBloat);
	SAFE_DELETE(m_pClot);
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
}

void cEnemyManager::UpdateAndRender(D3DXVECTOR3* vPlayerPos)
{
//	m_pBloat->UpdateAndRender(vPlayerPos);
//	m_pClot->UpdateAndRender(vPlayerPos);

	m_pDijkstra->Render();
}