#pragma once

#include "cAction.h"

class cActionSeq
	: public cAction
	, public iActionDelegate
{
protected:
	std::vector<cAction*>	m_vecAction;
	int						m_nCurrIndex;

public:
	cActionSeq(void);
	virtual ~cActionSeq(void);

	void AddAction(cAction* pAction);

	// cAction override
	virtual void Start() override;
	virtual void Update() override;

	// iActionDelegate
	virtual void OnActionFinish(cAction* pAction) override;
};

