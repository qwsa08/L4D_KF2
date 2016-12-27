#pragma once
#include "cZombie.h"

class cBloat : public cZombie
{
private:
	LPDIRECT3DTEXTURE9	m_pPuke;
	LPD3DXSPRITE		m_pSpriteP;
//	RECT				m_Rect;
	bool				m_Vomit;
	float				m_fVomitTime;

public:
	cBloat();
	virtual ~cBloat();

	virtual void Setup();
	virtual void UpdateAndRender(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, bool Shot);
	virtual void SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion);
	virtual bool PickTheBullet(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, int nZombieIndex);
};

