#pragma once
#include "iMap.h"
class cMtlTex;
class cGroup;

struct BoundingBox
{
	BoundingBox();
	bool isPointInside(D3DXVECTOR3& p);
	D3DXVECTOR3 _min;
	D3DXVECTOR3 _max;
};



class cObjMap : public iMap
{
protected:
	std::vector<cGroup*>		m_vecGroup;
	std::vector<D3DXVECTOR3>	m_vecSurface;

	std::vector<cMtlTex*>		m_pMtltex;
	SYNTHESIZE(std::vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);
	SYNTHESIZE(std::vector<ST_PNT_VERTEX>, m_vecVerWall, VerWall);

	LPD3DXMESH					m_Map;

	LPD3DXMESH					m_pWallMesh;
	BoundingBox*				m_box;

public:
	cObjMap(void);
	virtual ~cObjMap(void);

	virtual void Load(char* szMap, D3DXMATRIXA16* pmat = NULL);

	// iMap
	virtual void Render() override;
	virtual bool GetHeight(IN float x, OUT float& y, IN float z) override;
};

