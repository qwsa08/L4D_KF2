#include "StdAfx.h"
#include "cPyramid.h"


cPyramid::cPyramid(void)
{
}


cPyramid::~cPyramid(void)
{
}

void cPyramid::Setup(D3DCOLOR c, D3DXMATRIXA16* pmat /*= NULL*/)
{
	D3DXVECTOR3 p;
	p = D3DXVECTOR3( 0, 0, 0); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3( 1,-1,-1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3(-1,-1,-1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));

	p = D3DXVECTOR3( 0, 0, 0); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3( 1,-1, 1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3( 1,-1,-1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));

	p = D3DXVECTOR3( 0, 0, 0); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3(-1,-1, 1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3( 1,-1, 1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));

	p = D3DXVECTOR3( 0, 0, 0); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3(-1,-1,-1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3(-1,-1, 1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));

	p = D3DXVECTOR3(-1,-1,-1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3( 1,-1,-1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3( 1,-1, 1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));

	p = D3DXVECTOR3(-1,-1,-1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3( 1,-1, 1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3(-1,-1, 1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	
	if(pmat)
	{
		for(size_t i = 0; i < m_vecVertex.size(); ++i)
		{
			D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, pmat);
		}
	}
}

void cPyramid::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3, 
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));
}
