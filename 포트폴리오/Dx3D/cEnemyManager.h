#pragma once

class cZombie;
class cDijkstra;
class cEffect;

class cEnemyManager
{
private:
	cDijkstra*	m_pDijkstra;
	cZombie*	m_pBloat;
	cZombie*	m_pClot;
	cZombie*	m_pCrawler;
	cZombie*	m_pGorefast;
	cZombie*	m_pBoss;
	cEffect*	m_pEffect;

	bool		OnOff;
	D3DXVECTOR3				m_vTemp;
	std::vector<D3DXVECTOR3> m_vMonPosition;
public:
	cEnemyManager();
	~cEnemyManager();

	void Setup();
	void UpdateAndRender(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, bool* Shot, GUN_NAME ePlayerGun);
	
	void RenderEffect(D3DXMATRIX* Rotation);
	bool PickTheMonster(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir);
	bool PickThePlayer(ST_OBB* s_Player, OUT D3DXVECTOR3& monDirection);
	
};

