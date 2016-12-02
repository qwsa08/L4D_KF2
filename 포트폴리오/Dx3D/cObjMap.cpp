#include "StdAfx.h"
#include "cObjMap.h"
#include "cGroup.h"
#include "cObjLoader.h"
#include "cMtlTex.h"

cObjMap::cObjMap(void)
	:m_Map(NULL)
{
}


cObjMap::~cObjMap(void)
{
	SAFE_RELEASE(m_Map);
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
	m_Map = l.Load(m_vecVertex, szMap, m_pMtltex, pmat);
	std::vector<D3DXVECTOR3>	vecV;

	FILE* fp = NULL;

	int b = m_vecVertex.size();
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

	D3DXVECTOR3 vRayPos(x, 1000, z);
	D3DXVECTOR3 vRayDir( 0,-1, 0);
	float u, v, d;
	for (size_t i = 0; i < m_vecVertex.size(); i += 3)
	{
		D3DXVECTOR3 v0 = m_vecVertex[i].p;
		D3DXVECTOR3 v1 = m_vecVertex[i + 1].p;
		D3DXVECTOR3 v2 = m_vecVertex[i + 2].p;
		if(D3DXIntersectTri(&v0, &v1, &v2, &vRayPos, &vRayDir, &u, &v, &d))
		{
			//y = 1000 - d;
			//return true;
			vY.push_back(1000 - d);
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
