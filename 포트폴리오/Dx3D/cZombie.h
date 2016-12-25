#pragma once

class cSkinnedMesh;
class cDijkstra;
class cOBB;
class cFrustum;

enum ZOMBIE_MOTION
{
	IDLE = 0,
	MOVE,
	SPRINT,
	HIT_F,
	HIT_B,
	ATTACK_MELEE,
	ATTACK_CHARGE,
	ATTACK_GUN,
	BOSS_HEAL,
	ENTRANCE,
	VICTORY,
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
	float			fElapsedTime;
	bool			isRecognize;
	//
	ST_OBB			OBBBox;
	D3DXMATRIXA16   matWTM;

	ST_ZOMBIE() : pSkinnedMesh(NULL), vPrevPosition(0, 0, 0), vPosition(0, 0, 0), vDirection(0, 0, 0),
		fAngle(0.f), eMotion(IDLE), fSpeed(2.f), fElapsedTime(0.f), isRecognize(false), OBBBox()
	{
		D3DXMatrixIdentity(&matWTM);
	}
};

class cZombie
{
protected:
	std::vector<ST_ZOMBIE>	m_vecSkinnedMesh;
	cDijkstra*				m_pDijkstra;
	cOBB*					m_pOBB;
	cFrustum*				m_pFrustum;

public:
	cZombie();
	virtual ~cZombie();

	virtual void Setup() = 0;
	virtual void UpdateAndRender(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, bool Shot) = 0;
	virtual void SetDijkstraMemoryLink(cDijkstra* pDijkstra) { m_pDijkstra = pDijkstra; }
	virtual void SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion) = 0;
	virtual bool PickTheBullet(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, int nZombieIndex) = 0;
};

