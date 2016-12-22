#pragma once
#include "cZombie.h"

class cBoss : public cZombie
{
private:
	ST_ZOMBIE	m_stBoss;
	float		m_fTime;
	bool		m_isDirChange;

public:
	cBoss();
	virtual ~cBoss();

	virtual void Setup();
	virtual void UpdateAndRender(D3DXVECTOR3* vPlayerPos);
	virtual void SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion);
};

