#pragma once
#include "cZombie.h"
class cOBB;
class cClot : public cZombie
{
private:
	cOBB*			m_pOBB;
public:
	cClot();
	virtual ~cClot();

	virtual void Setup();
	virtual void UpdateAndRender(D3DXVECTOR3* vPlayerPos);
	virtual void SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion);
	virtual bool PickTheBullet(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir);
};

