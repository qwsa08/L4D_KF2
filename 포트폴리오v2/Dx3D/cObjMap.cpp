#include "StdAfx.h"
#include "cObjMap.h"
#include "cGroup.h"
#include "cObjLoader.h"
#include "cMtlTex.h"

cObjMap::cObjMap(void)
	:m_Map(NULL)
	, m_pWallMesh(NULL)
{
}


cObjMap::~cObjMap(void)
{
	SAFE_RELEASE(m_Map);
	SAFE_RELEASE(m_pWallMesh);
	for each(auto p in m_vecGroup)
	{
		SAFE_DELETE(p);
	}

	for each(auto p in m_pMtltex)
	{
		SAFE_RELEASE(p);
	}
}

void cObjMap::Load( char* szMap,D3DXMATRIXA16* pmat /*= NULL*/ )
{
	cObjLoader l;
	m_Map = l.Load(this, szMap, m_pMtltex, pmat);
	std::vector<D3DXVECTOR3>	vecV;

	
	int b = 0;
}

void cObjMap::Render()
{
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	
	for (int i = 0; i < m_pMtltex.size(); i++)
	{
		g_pD3DDevice->SetTexture(0, m_pMtltex[i]->GetTexture());
		g_pD3DDevice->SetMaterial(&m_pMtltex[i]->GetMtl());
		m_Map->DrawSubset(i);
	}
}

bool cObjMap::GetHeight( IN float x, OUT float& y, IN float z )
{
	std::vector<float> vY;

	D3DXVECTOR3 vRayPos(x, y + 100, z);
	D3DXVECTOR3 vRayDir( 0,-1, 0);
	float u, v, d;
	int temp = y;

	for (size_t i = 0; i < m_vecVertex.size(); i += 3)
	{
		D3DXVECTOR3 v0 = m_vecVertex[i].p;
		D3DXVECTOR3 v1 = m_vecVertex[i + 1].p;
		D3DXVECTOR3 v2 = m_vecVertex[i + 2].p;
		if(D3DXIntersectTri(&v0, &v1, &v2, &vRayPos, &vRayDir, &u, &v, &d))
		{
			//return true;
			vY.push_back(y+100 -d);
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
