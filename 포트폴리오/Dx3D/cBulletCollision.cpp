#include "stdafx.h"
#include "cBulletCollision.h"
#include "cCrtController.h"
#include "cObjMap.h"

cBulletCollision::cBulletCollision()
{
}


cBulletCollision::~cBulletCollision()
{
}

void cBulletCollision::SetUp(cObjMap* Map)
{
	m_pMap = Map->GetMap();
	m_vecClipping.resize(6);
}

void cBulletCollision::Render()
{

}
bool cBulletCollision::PickBullet(cCrtController* Controller)
{
	std::vector<ST_WallNear> vecWallNear;
	D3DXVECTOR3 Position = *(Controller->GetPosition());
	D3DXVECTOR3 vRayPos(Position.x, Position.y, Position.z);
	D3DXVECTOR3 vRayDir = Controller->GetDirection();
	m_vOverTex.clear();
	float u, v, d;
	
	for (int i = 0; i < m_pMap.size(); i+=3)
	{
		D3DXVECTOR3 v0 = m_pMap[i].p;
		D3DXVECTOR3 v1 = m_pMap[i + 1].p;
		D3DXVECTOR3 v2 = m_pMap[i + 2].p;

		if (D3DXIntersectTri(&v0, &v1, &v2, &vRayPos, &vRayDir, &u, &v, &d))
		{
			D3DXVECTOR3 BulletPoint(0, 0, 0);
			BulletPoint = v0 + u * (v1 - v0) + v * (v2 - v0);

			vecWallNear.push_back(ST_WallNear(BulletPoint, d,i));
			
		}
	}
	if (vecWallNear.size() > 0)
	{
		for (int i = 0; i < vecWallNear.size(); i++)
		{
			if (vecWallNear[0].fRange > vecWallNear[i].fRange)
			{
				ST_WallNear Temp;
				Temp = vecWallNear[0];
				vecWallNear[0] = vecWallNear[i];
				vecWallNear[i] = Temp;
			}
		}
		m_vBulletPoint = vecWallNear[0].WallPosition;
		for (int i = 0; i < 3; i++)
		{
			m_vOverTex.push_back(m_pMap[vecWallNear[0].num + i]);
		}
		return true;
	}
	return false;
}

D3DXMATRIXA16 cBulletCollision::Clipping()
{
	D3DXMATRIXA16 Cliiping;
	D3DXMatrixPerspectiveFovLH(&Cliiping, D3DX_PI / 4.0f, 2.f, 1, 20);
	
	return Cliiping;
}