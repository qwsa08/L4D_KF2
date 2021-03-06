#pragma once
#include "cZombie.h"

class cBoss : public cZombie
{
private:
	ST_ZOMBIE	m_stBoss;
	bool		m_Pick;
	D3DXVECTOR3			m_pPosition;

public:
	cBoss();
	virtual ~cBoss();

	virtual void Setup();
	virtual bool UpdateAndRender(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, bool* Shot, GUN_NAME ePlayerGun);
	virtual void SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion);
	virtual bool PickTheBullet(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, int nZombieIndex);
	virtual bool PickThePlayer(ST_OBB* sPlayer, OUT D3DXVECTOR3& monDirection);
	virtual bool GetZombiePosition();
	virtual D3DXVECTOR3 GetPosition();

	void IdleSoundOn();
	void IdleSoundOff();

	void StepSoundOn();
	void StepSoundOff();
};

