#pragma once

class cSkinnedMesh;
class cActionSeq;

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
	D3DXVECTOR3		vPosition;
	float			fAngle;
	ZOMBIE_MOTION	eMotion;

	ST_ZOMBIE() : pSkinnedMesh(NULL), vPosition(0, 0, 0), fAngle(0.f), eMotion(IDLE) { }
};

class cZombie
{
protected:
	SYNTHESIZE_PASS_BY_REF(std::vector<ST_ZOMBIE>, m_vecSkinnedMesh, SkinnedMesh);

public:
	cZombie();
	virtual ~cZombie();

	virtual void Setup() = 0;
	virtual void UpdateAndRender(std::vector<D3DXVECTOR3>* vecNode) = 0;
};

