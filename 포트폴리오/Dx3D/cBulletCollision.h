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
	//===���������� �޴°� �̵��ϱ�..�ƴϸ� �̷��� �޾ƿͼ� �ӵ��� �⼧��ų��....
	// ���������� ������ �ణ�� ������ + �ؽ��� ���ﶧ.. �����ٵ�... �ƴѰ�..?;;;
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

