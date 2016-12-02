#pragma once
#include "iMap.h"
class cMtlTex;
class cGroup;

class cObjMap : public iMap
{
protected:
	std::vector<cGroup*>		m_vecGroup;
	std::vector<D3DXVECTOR3>	m_vecSurface;

	std::vector<cMtlTex*>		m_pMtltex;
	SYNTHESIZE(std::vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);
	
	LPD3DXMESH					m_Map;

public:
	cObjMap(void);
	virtual ~cObjMap(void);

	virtual void Load(char* szMap, char* szSurface, D3DXMATRIXA16* pmat = NULL);

	// iMap
	virtual void Render() override;
	virtual bool GetHeight(IN float x, OUT float& y, IN float z) override;
};

