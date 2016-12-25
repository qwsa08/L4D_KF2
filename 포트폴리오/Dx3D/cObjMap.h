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
	LPD3DXMESH					m_pWallMesh;
	BoundingBox*				m_box;

	
	std::vector<D3DXVECTOR3>  m_vecBoundingBox;
	LPD3DXMESH					m_Map;
	std::vector<D3DXVECTOR3>	m_line;
	std::vector<D3DXVECTOR3>	m_Start;

	LPD3DXMESH					m_LightCon;
	std::vector<cMtlTex*>		m_pConMtl;

	SYNTHESIZE(std::vector<ST_PNT_VERTEX>, m_vecMap, Map);
	SYNTHESIZE(std::vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);
	// 이거 pnt말고 그냥 벡터값만 받으면 좀더 좋아질것같다는...
	//SYNTHESIZE(std::vector<ST_PNT_VERTEX>, m_vecVerWall, VerWall);

	std::vector<LPDIRECT3DTEXTURE9>	m_vecNomal;
	std::vector<LPDIRECT3DTEXTURE9>	m_vecSpecular;
	
	LPD3DXEFFECT			m_pTextureMappingShader;
public:
	cObjMap(void);
	virtual ~cObjMap(void);

	virtual void Load(char* szMap, D3DXMATRIXA16* pmat = NULL);
	virtual void BoxLoad(char* szMap, OUT std::vector<D3DXVECTOR3> &vecBoungdingBox, D3DXMATRIXA16* pmat = NULL);
	// iMap
	virtual void Render();
	virtual void Render(
		IN D3DXVECTOR4* LightPosition, IN D3DXVECTOR4* LightDirection,
		IN D3DXVECTOR4* SpotLightCenter, IN float SpotLightRange,
		IN D3DXVECTOR4* CameraPosition) override;
	virtual bool GetHeight(IN float x, OUT float& y, IN float z) override;
};

