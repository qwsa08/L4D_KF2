#pragma once
#include "cZombie.h"

class cBloat : public cZombie
{
public:
	cBloat();
	virtual ~cBloat();

	virtual void Setup();
	virtual void UpdateAndRender(D3DXMATRIXA16* pmat = NULL, D3DXMATRIXA16* pScal = NULL);
};

