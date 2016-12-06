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

	//시작점과 직선
	
	
	for (int i = 0; i < m_vecVerWall.size(); i += 3)
	{
		D3DXVECTOR3 _halfSpot;
		_halfSpot = (m_vecVerWall[i + 1].p + m_vecVerWall[i + 2].p) /2;
		m_line.push_back(_halfSpot - m_vecVerWall[i].p);
		m_Start.push_back(m_vecVerWall[i].p);
	}
	
	int a = 0;
}

void cObjMap::Render()
{
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	

	for (int i = 0; i < m_pMtltex.size(); i++)
	{
		if (true)
		{
			g_pD3DDevice->SetTexture(0, m_pMtltex[i]->GetTexture());
			g_pD3DDevice->SetMaterial(&m_pMtltex[i]->GetMtl());
			m_Map->DrawSubset(i);
		}
		
	}
	
	/*for (int i = 0; i <36; i += 3)
	{
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			1,
			&m_vecVerWall[i],
			sizeof(ST_PNT_VERTEX));
	}*/
}

bool cObjMap::GetHeight( IN float x, OUT float& y, IN float z )
{
	std::vector<float> vY;

	D3DXVECTOR3 vRayPos(x, y + 100, z);
	D3DXVECTOR3 vRayDir( 0,-1, 0);
	float u, v, d;
	
	D3DXVECTOR3 vPos(x, y, z);
	float Range;
	

	for (int i = 0; i < m_vecVerWall.size(); i+=3)
	{

		float LineMag;
		float U;
		D3DXVECTOR3 vIntersection;
		D3DXVECTOR3 _halfSpot;
		_halfSpot = (m_vecVerWall[i + 1].p + m_vecVerWall[i + 2].p) / 2;

		LineMag = D3DXVec3Length(&(_halfSpot - m_vecVerWall[i].p));

		U = (
			((vPos.x - m_vecVerWall[i].p.x) * (_halfSpot.x - m_vecVerWall[i].p.x)) +
			((vPos.y - m_vecVerWall[i].p.y) * (_halfSpot.y - m_vecVerWall[i].p.y)) +
			((vPos.z - m_vecVerWall[i].p.z) * (_halfSpot.z - m_vecVerWall[i].p.z))
			) / (LineMag * LineMag);

		if (U < 0.f || U >1.f) continue;

		vIntersection.x = m_vecVerWall[i].p.x + U *(_halfSpot.x - m_vecVerWall[i].p.x);
		vIntersection.y = m_vecVerWall[i].p.y + U *(_halfSpot.y - m_vecVerWall[i].p.y);
		vIntersection.z = m_vecVerWall[i].p.z + U *(_halfSpot.z - m_vecVerWall[i].p.z);

		Range = D3DXVec3Length(&(vIntersection - vPos));

		if (Range < 50.f)
		{
			return false;
		}
	}

	for (int i = 0; i < m_line.size(); i++)
	{
		D3DXVECTOR3 _line;
		_line = vPos - m_Start[i];
		D3DXVECTOR3 _lineNomal;
		D3DXVec3Normalize(&_lineNomal, &m_line[i]);

		D3DXVECTOR3 m_Spot , m_test;
		float numtest;
		numtest = D3DXVec3Dot(&_lineNomal, &_line);// *m_line[i];
		m_Spot = m_Start[i] + D3DXVec3Dot(&_lineNomal, &_line) * m_line[i];


		m_Spot = vPos - m_Spot;
		Range = D3DXVec3Length(&m_Spot);

		if (fabs(Range) < 35)
		{
			return false;
		}
	}
	
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
		y = hMax + 70;
		return true;
	}
	y = 0;
	return false;
	
}
bool cObjMap::Plane(D3DXVECTOR3 center, float radius)
{
	D3DXVECTOR3 V2_0;
	D3DXVECTOR3 V1_0;
	D3DXVECTOR3 vCross;
	float Range;
	for (int i = 0; i < m_vecVerWall.size(); i += 3)
	{
		V2_0 = m_vecVerWall[2].p - m_vecVerWall[0].p;
		V1_0 = m_vecVerWall[1].p - m_vecVerWall[0].p;
		D3DXVec3Cross(&vCross, &V2_0, &V1_0);
		D3DXVec3Normalize(&vCross, &vCross);

		Range = D3DXVec3Dot(&center, &vCross);

		if (Range < radius) return false;
	}
	return true;
}