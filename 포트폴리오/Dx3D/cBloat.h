#pragma once
#include "cZombie.h"

class cBloat : public cZombie
{
public:
	cBloat();
	virtual ~cBloat();

	virtual void Setup();
	virtual void UpdateAndRender(D3DXVECTOR3* vPlayerPos);
	virtual void SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion);
};

