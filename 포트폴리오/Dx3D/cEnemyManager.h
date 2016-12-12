#pragma once

class cZombie;
class cDijkstra;

class cEnemyManager
{
private:
	cDijkstra*	m_pDijkstra;
	cZombie*	m_pBloat;

public:
	cEnemyManager();
	~cEnemyManager();

	void Setup();
	void UpdateAndRender(D3DXVECTOR3* pTarget);

private:
	void Update(D3DXVECTOR3* pTarget);
	void Render();
};

