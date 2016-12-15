#pragma once

class cSkinnedMesh;
class cAction;

class iActionDelegate
{
public:
	virtual void OnActionFinish(cAction* pSender) PURE;
};

class cAction
{
protected:
	float m_fPassedActionTime;
	SYNTHESIZE(iActionDelegate*, m_pDelegate, Delegate);
	SYNTHESIZE(float, m_fActionTime, ActionTime);
	SYNTHESIZE(cSkinnedMesh*, m_pTarget, Target);

public:
	cAction(void);
	virtual ~cAction(void);

	virtual void Start();
	virtual void Update();
};

