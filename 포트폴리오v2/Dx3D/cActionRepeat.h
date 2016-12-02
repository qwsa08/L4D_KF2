#pragma once

#include "cAction.h"

class cActionRepeat
	: public cAction
	, public iActionDelegate
{
protected:
	SYNTHESIZE_ADD_REF(cAction*, m_pAction, Action);

public:
	cActionRepeat(void);
	~cActionRepeat(void);

	// cAction override
	virtual void Update() override;

	// iActionDelegate
	virtual void OnActionFinish(cAction* pAction) override;
};

