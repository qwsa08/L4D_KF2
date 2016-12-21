#pragma once

class cSkinnedMesh;
class cDijkstra;

enum ZOMBIE_MOTION
{
	IDLE = 0,
	MOVE,
	SPRINT,
	ATTACK,
	DIE
};

struct ST_ZOMBIE
{
	cSkinnedMesh*	pSkinnedMesh;
	D3DXVECTOR3		vPrevPosition;
	D3DXVECTOR3		vPosition;
	D3DXVECTOR3		vDirection;
	float			fAngle;
	ZOMBIE_MOTION	eMotion;
	float			fSpeed;
	bool			isRecognize;

	ST_ZOMBIE() : pSkinnedMesh(NULL), vPrevPosition(0, 0, 0), vPosition(0, 0, 0), vDirection(0, 0, 0), 
		fAngle(0.f), eMotion(IDLE), fSpeed(2.f), isRecognize(false) { }
};

class cZombie
{
protected:
	std::vector<ST_ZOMBIE>	m_vecSkinnedMesh;
	cDijkstra*				m_pDijkstra;

public:
	cZombie();
	virtual ~cZombie();

	virtual void Setup() = 0;
	virtual void UpdateAndRender(D3DXVECTOR3* vPlayerPos) = 0;
	virtual void SetDijkstraMemoryLink(cDijkstra* pDijkstra) { m_pDijkstra = pDijkstra; }
	virtual void SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion) = 0;
};

