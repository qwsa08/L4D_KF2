#pragma once
#include "cZombie.h"
class cCrawler : public cZombie
{
public:
	cCrawler();
	virtual ~cCrawler();

	virtual void Setup();
	virtual void UpdateAndRender(D3DXVECTOR3* vPlayerPos);
	virtual void SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion);
};

