#include "stdafx.h"
#include "cEnemyManager.h"
#include "cDijkstra.h"
#include "cAStar.h"
#include "cZombie.h"
#include "cBloat.h"
#include "cActionSeq.h"
#include "cAction.h"
#include "cActionMove.h"
#include "cCrtController.h"


cEnemyManager::cEnemyManager()
	: m_pDijkstra(NULL)
	, m_pBloat(NULL)
	, m_pAstar(NULL)
{
}


cEnemyManager::~cEnemyManager()
{
	SAFE_DELETE(m_pDijkstra);
	SAFE_DELETE(m_pBloat);
	SAFE_DELETE(m_pAstar);
}

void cEnemyManager::Setup()
{
	m_pDijkstra = new cDijkstra;
	m_pDijkstra->Setup();

	m_pAstar = new cAStar;
	m_pAstar->Setup();
	
	m_pBloat = new cBloat;
	m_pBloat->Setup();
}

void cEnemyManager::UpdateAndRender(std::vector<D3DXVECTOR3>* vecNode)
{
	m_pDijkstra->Render();
	
	m_pAstar->Update(&D3DXVECTOR3(900, -60, 1200), &D3DXVECTOR3(0, 0, 0));

	int nStart = m_pDijkstra->GetStartNode(m_pPlayer->GetPosition());

	for each(auto p in m_pBloat->GetSkinnedMesh())
	{
		int nDest = m_pDijkstra->GetDestNode(&p.vPosition);
		m_pBloat->UpdateAndRender(&m_pDijkstra->GetNodeTable(nStart, nDest));
	}	
}

void cEnemyManager::Update(D3DXVECTOR3 * pTarget)
{
}

void cEnemyManager::Render()
{
}