#pragma once
#include "cZombie.h"

class cBoss : public cZombie
{
private:
	ST_ZOMBIE	m_stBoss;

public:
	cBoss();
	virtual ~cBoss();

	virtual void Setup();
	virtual void UpdateAndRender(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, bool Shot);
	virtual void SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion);
	virtual bool PickTheBullet(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, int nZombieIndex);
};

