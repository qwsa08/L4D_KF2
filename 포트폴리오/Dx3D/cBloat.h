#pragma once
#include "cZombie.h"

class cBloat : public cZombie
{
public:
	cBloat();
	virtual ~cBloat();

	virtual void Setup();
	virtual void UpdateAndRender(int nDest);
};

