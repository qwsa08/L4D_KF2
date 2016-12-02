#pragma once
#include "iMap.h"
class cMtlTex;
class cGroup;

#define MapSkin 9
class cObjMap : public iMap
{
protected:
	std::vector<cGroup*>		m_vecGroup;
	std::vector<D3DXVECTOR3>	m_vecSurface;
	std::vector<cMtlTex*>		m_pMtltex;
	LPD3DXMESH					m_Map;
	LPDIRECT3DVERTEXBUFFER9 	m_pVertexBuffer;
	std::vector<ST_PNT_VERTEX>	m_vecFloorVertex;
	SYNTHESIZE(std::vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);
public:
	cObjMap(void);
	virtual ~cObjMap(void);

	virtual void Load(char* szMap, D3DXMATRIXA16* pmat = NULL);

	// iMap
	virtual void Render() override;
	virtual bool GetHeight(IN float x, OUT float& y, IN float z) override;
};

