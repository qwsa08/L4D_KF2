#pragma once
#include "cZombie.h"
class cClot : public cZombie
{
public:
	cClot();
	virtual ~cClot();

	virtual void Setup();
	virtual void UpdateAndRender(D3DXVECTOR3* vPlayerPos);
	virtual void SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion);
};

