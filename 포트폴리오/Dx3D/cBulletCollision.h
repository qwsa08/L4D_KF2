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
	
public:
	cBulletCollision();
	~cBulletCollision();

	void SetUp(cObjMap* Map);
	void Render();
	bool PickBullet(cCrtController* Controller);

	D3DXMATRIXA16 Clipping();
	D3DXVECTOR3 GetBulletPosition() { return m_vBulletPoint; }
	std::vector<ST_PNT_VERTEX> GetBulletPlane() { return m_vOverTex; }
	//std::vector<ST_PNT_VERTEX> GetTestMap() { return m_pMap; }
};

