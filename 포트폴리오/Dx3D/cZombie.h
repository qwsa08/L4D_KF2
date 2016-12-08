#pragma once

class cSkinnedMesh;
class iMap;

enum ZOMBIE_MOTION
{
	IDLE = 0,
	MOVE,
	SPRINT,
	ATTACK,
	DIE
};

class cZombie
{
protected:
	std::vector<cSkinnedMesh*>	m_vecSkinnedMesh;
	iMap*						m_pMap;
	D3DXVECTOR3					m_vPosition;
	ZOMBIE_MOTION				m_eMotion;

public:
	cZombie();
	virtual ~cZombie();

	virtual void Setup();
	virtual void UpdateAndRender() = 0;
};

