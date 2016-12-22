#pragma once

class cZombie;
class cDijkstra;
class cCrtController;

class cEnemyManager
{
private:
	cDijkstra*	m_pDijkstra;
	cZombie*	m_pBloat;
	cZombie*	m_pClot;
	cZombie*	m_pCrawler;
	cZombie*	m_pGorefast;
	cZombie*	m_pBoss;

	cCrtController*	m_pPlayer;

public:
	cEnemyManager();
	~cEnemyManager();

	void Setup();
	void UpdateAndRender(D3DXVECTOR3* vPlayerPos);
};

