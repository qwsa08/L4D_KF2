#pragma once

class cCrtController;
class cObjMap;

struct ST_WallNear
{
	D3DXVECTOR3 WallPosition;
	float		fRange;
	ST_WallNear() : WallPosition(0, 0, 0), fRange(0.f) {}
	ST_WallNear(D3DXVECTOR3 _WallPoint, float _fRange)
		: WallPosition(_WallPoint), fRange(_fRange) {}
};

class cBulletCollision
{
private:
	//===직접적으로 받는게 이득일까..아니면 이렇게 받아와서 속도를 향샹시킬까....
	// 직접적으로 받으면 약간의 딜레이 + 텍스쳐 씌울때.. 편할텐데... 아닌가..?;;;
	std::vector<ST_PNT_VERTEX>  m_pMap;

	//std::vector<D3DXVECTOR3>	m_vBulletPoint;
	D3DXVECTOR3	m_vBulletPoint;
public:
	cBulletCollision();
	~cBulletCollision();

	void SetUp(cObjMap* Map);
	bool PickBullet(cCrtController* Controller);

	D3DXVECTOR3 GetBulletPosition() { return m_vBulletPoint; }
};

