#pragma once

class cCrtController;
class iMap;
class cObjMap;

struct ST_WallNear
{
	D3DXVECTOR3 WallPosition;
	float		fRange;
	int			num;
	ST_WallNear() : WallPosition(0, 0, 0), fRange(0.f), num(0){}
	ST_WallNear(D3DXVECTOR3 _WallPoint, float _fRange, int _num)
		: WallPosition(_WallPoint), fRange(_fRange),num(_num) {}
};

class cBulletCollision
{
private:
	//===직접적으로 받는게 이득일까..아니면 이렇게 받아와서 속도를 향샹시킬까....
	// 직접적으로 받으면 약간의 딜레이 + 텍스쳐 씌울때.. 편할텐데... 아닌가..?;;;
	std::vector<ST_PNT_VERTEX>  m_pMap;

	std::vector<D3DXPLANE>		m_vecClipping;
	std::vector<ST_PNT_VERTEX>	m_vOverTex;
	D3DXVECTOR3	m_vBulletPoint;
	
	LPDIRECT3DSURFACE9			m_pRenderTargetSurface;
	LPDIRECT3DTEXTURE9			m_pRenderTargetTexture;
	LPD3DXSPRITE				m_pSprite;
	int							m_nRenderTargetWidth;
	int							m_nRenderTargetHeight;
	LPD3DXEFFECT				m_pEffect;

	RECT rc;
	LPD3DXEFFECT				m_pBulletholes;
	LPDIRECT3DTEXTURE9			m_Texture;
	std::vector<ST_PT_VERTEX>	m_vBox;

	int y;
	LPD3DXMESH					m_pMesh;
	SYNTHESIZE(D3DXMATRIX, m_WTM, WTM);
public:
	cBulletCollision();
	~cBulletCollision();

	void SetUp(cObjMap* Map);
	void Render(iMap* Map);
	bool PickBullet(cCrtController* Controller);

	void Fire(iMap* Map, cCrtController* Controller);

	void Bulletholes(cCrtController* Controller);

	D3DXMATRIXA16 Clipping();
	D3DXVECTOR3 GetBulletPosition() { return m_vBulletPoint; }
	std::vector<ST_PNT_VERTEX> GetBulletPlane() { return m_vOverTex; }
	//std::vector<ST_PNT_VERTEX> GetTestMap() { return m_pMap; }
};

