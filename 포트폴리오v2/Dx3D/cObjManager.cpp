#include "stdafx.h"
#include "cObjManager.h"
#include "cObjMap.h"

cObjManager::cObjManager()
	:m_Map(NULL)
{
	m_Map = new cObjMap;
}


cObjManager::~cObjManager()
{
	SAFE_DELETE(m_Map);
}

bool cObjManager::GetHeight(IN float x, OUT float& y, IN float z)
{
	std::vector<float> vY;

	D3DXVECTOR3 vRayPos(x, y + 100, z);
	D3DXVECTOR3 vRayDir(0, -1, 0);
	float u, v, d;
	int temp = y;

	for (size_t i = 0; i < m_Map->GetVertex().size(); i += 3)
	{
		D3DXVECTOR3 v0 = m_Map->GetVertex()[i].p;
		D3DXVECTOR3 v1 = m_Map->GetVertex()[i + 1].p;
		D3DXVECTOR3 v2 = m_Map->GetVertex()[i + 2].p;
		if (D3DXIntersectTri(&v0, &v1, &v2, &vRayPos, &vRayDir, &u, &v, &d))
		{
			//return true;
			vY.push_back(y + 100 - d);
		}
	}
	if (vY.size() > 0)
	{
		float hMax = vY[0];
		for (int i = 0; i < vY.size(); ++i)
		{
			if (hMax < vY[i])
			{
				hMax = vY[i];
			}
		}
		y = hMax;
		return true;
	}
	y = 0;
	return false;
}
bool cObjManager::Plane(D3DXVECTOR3 center, float radius)
{
	/*float Range = 0;
	for (int i = 0; i < m_Map->GetPlane().size(); i++)
	{
		Range = D3DXVec3Dot(&center, &m_Map->GetPlane()[i]);

		if (Range < radius) return false;
	}*/
	return true;
}