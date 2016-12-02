#pragma once

#include "cMtlTex.h"

class cGroup
{
private:
	SYNTHESIZE(std::vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);
	SYNTHESIZE_ADD_REF(cMtlTex*, m_pMtlTex, MtlTex);

public:
	cGroup(void);
	virtual ~cGroup(void);
	void Render();
};

