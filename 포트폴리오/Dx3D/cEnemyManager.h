#pragma once

class cZombie;
class cDijkstra;
class cAStar;
class cAction;
class cActionMove;
class cCrtController;

class cEnemyManager
{
private:
	cDijkstra*	m_pDijkstra;
	cAStar*		m_pAstar;
	cZombie*	m_pBloat;

	cCrtController*	m_pPlayer;

public:
	cEnemyManager();
	~cEnemyManager();

	void Setup();
	void UpdateAndRender(D3DXVECTOR3* vPlayerPos);

private:
	void Update(D3DXVECTOR3* pTarget);
	void Render();
};

