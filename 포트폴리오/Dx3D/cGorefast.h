#pragma once
#include "cZombie.h"
class cGorefast : public cZombie
{
private:
	bool		m_Pick;
	D3DXVECTOR3			m_pPosition;
public:
	cGorefast();
	virtual ~cGorefast();

	virtual void Setup();
	virtual void UpdateAndRender(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, bool* Shot, GUN_NAME ePlayerGun);
	virtual void SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion);
	virtual bool PickTheBullet(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, int nZombieIndex);
	virtual bool PickThePlayer(ST_OBB* sPlayer, OUT D3DXVECTOR3& monDirection);
	virtual bool GetZombiePosition();
	virtual D3DXVECTOR3 GetPosition();

	void IdleSoundOn(int n);
	void IdleSoundOff(int n);

	void StepSoundOn(int n);
	void StepSoundOff(int n);
};

