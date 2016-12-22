#pragma once
#include "cZombie.h"

class cBoss : public cZombie
{
public:
	cBoss();
	virtual ~cBoss();

	virtual void Setup();
	virtual void UpdateAndRender(D3DXVECTOR3* vPlayerPos);
	virtual void SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion);
};

