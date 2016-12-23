#pragma once
#include "cZombie.h"
class cGorefast : public cZombie
{
public:
	cGorefast();
	virtual ~cGorefast();

	virtual void Setup();
	virtual void UpdateAndRender(D3DXVECTOR3* vPlayerPos);
	virtual void SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion);
	virtual bool PickTheBullet(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir);
};

