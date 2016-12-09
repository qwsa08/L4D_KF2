#pragma once

class cSkinnedMesh;

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
};

class cZombie
{
protected:
	std::vector<ST_ZOMBIE>	m_vecSkinnedMesh;

public:
	cZombie();
	virtual ~cZombie();

	virtual void Setup() = 0;
	virtual void UpdateAndRender() = 0;
};

