#pragma once
#include "cZombie.h"

class cBloat : public cZombie
{
public:
	cBloat();
	virtual ~cBloat();

	virtual void Setup();
	virtual void UpdateAndRender(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, bool Shot);
	virtual void SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion);
	virtual bool PickTheBullet(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, int nZombieIndex);
	virtual bool PickThePlayer(ST_OBB* sPlayer, OUT D3DXVECTOR3& monLocation);
};

