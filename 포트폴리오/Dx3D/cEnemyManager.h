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
	void UpdateAndRender(std::vector<D3DXVECTOR3>* vecNode);
	void SetPlayerMemoryLink(cCrtController* pPlayer) { m_pPlayer = pPlayer; }

private:
	void Update(D3DXVECTOR3* pTarget);
	void Render();
};

