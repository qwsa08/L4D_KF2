#pragma once

class cZombie;
class cDijkstra;

class cEnemyManager
{
private:
	cDijkstra*	m_pDijkstra;
	cZombie*	m_pBloat;
	cZombie*	m_pClot;
	cZombie*	m_pCrawler;
	cZombie*	m_pGorefast;
	cZombie*	m_pBoss;
public:
	cEnemyManager();
	~cEnemyManager();

	void Setup();
	void UpdateAndRender(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, bool* Shot, GUN_NAME ePlayerGun);
	
	bool PickTheMonster(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir);
	bool PickThePlayer(ST_OBB* s_Player, OUT D3DXVECTOR3& monDirection);
	
};

