#include "StdAfx.h"
#include "cCube.h"
#include "cCamera.h"

cCube::cCube(void)
	: m_fAngle(0.0f)
	, m_fAngleVel(0.0f)
	, m_vTranslation(0, 0, 0)
{
	D3DXMatrixIdentity(&m_matWorldTM);
}

cCube::~cCube(void)
{
}

void cCube::Setup(D3DXMATRIXA16* pmat)
{
	std::vector<D3DXVECTOR3> vecVertex;
	vecVertex.push_back(D3DXVECTOR3(-1,-1,-1));
	vecVertex.push_back(D3DXVECTOR3(-1, 1,-1));
	vecVertex.push_back(D3DXVECTOR3( 1, 1,-1));
	vecVertex.push_back(D3DXVECTOR3( 1,-1,-1));
	vecVertex.push_back(D3DXVECTOR3(-1,-1, 1));
	vecVertex.push_back(D3DXVECTOR3(-1, 1, 1));
	vecVertex.push_back(D3DXVECTOR3( 1, 1, 1));
	vecVertex.push_back(D3DXVECTOR3( 1,-1, 1));

	if(pmat)
	{
		for (size_t i = 0; i < vecVertex.size(); ++i)
		{
			D3DXVec3TransformCoord(&vecVertex[i], &vecVertex[i], pmat);
		}
	}
	std::vector<int> vecIndex;
	vecIndex.push_back(0);
	vecIndex.push_back(1);
	vecIndex.push_back(2);

	vecIndex.push_back(0);
	vecIndex.push_back(2);
	vecIndex.push_back(3);

	vecIndex.push_back(4);
	vecIndex.push_back(6);
	vecIndex.push_back(5);

	vecIndex.push_back(4);
	vecIndex.push_back(7);
	vecIndex.push_back(6);

	vecIndex.push_back(4);
	vecIndex.push_back(5);
	vecIndex.push_back(1);

	vecIndex.push_back(4);
	vecIndex.push_back(1);
	vecIndex.push_back(0);

	vecIndex.push_back(3);
	vecIndex.push_back(2);
	vecIndex.push_back(6);

	vecIndex.push_back(3);
	vecIndex.push_back(6);
	vecIndex.push_back(7);

	vecIndex.push_back(1);
	vecIndex.push_back(5);
	vecIndex.push_back(6);

	vecIndex.push_back(1);
	vecIndex.push_back(6);
	vecIndex.push_back(2);

	vecIndex.push_back(4);
	vecIndex.push_back(0);
	vecIndex.push_back(3);

	vecIndex.push_back(4);
	vecIndex.push_back(3);
	vecIndex.push_back(7);

	D3DCOLOR c = D3DCOLOR_XRGB(0, 0, 0);
	for (size_t i = 0; i < vecIndex.size(); ++i)
	{
		D3DXVECTOR3 p = vecVertex[vecIndex[i]];
		if( i % 6 == 0 )
			c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
		m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	}

	D3DXMatrixIdentity(&m_matWorldTM);
}

void cCube::Update(D3DXMATRIXA16* pParentWorld)
{
	//m_matLocalTM; // °è»ê
	m_fAngle += m_fAngleVel * g_pTimeManager->GetDeltaTime();
	if(m_fAngle < -D3DX_PI / 4.0f)
	{
		m_fAngle = -D3DX_PI / 4.0f;
		m_fAngleVel *= -1;
	}

	if(m_fAngle > D3DX_PI / 4.0f)
	{
		m_fAngle = D3DX_PI / 4.0f;
		m_fAngleVel *= -1;
	}

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationX(&matR, m_fAngle);
	D3DXMatrixTranslation(&matT, m_vTranslation.x, m_vTranslation.y, m_vTranslation.z);
	
	m_matWorldTM = matR * matT;

	if(pParentWorld)
		m_matWorldTM *= *pParentWorld;
	for each(auto p in m_vecChild)
	{
		p->Update(&m_matWorldTM);
	}
}

void cCube::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3, 
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));

	for each(auto p in m_vecChild)
	{
		p->Render();
	}
}

D3DXMATRIXA16* cCube::GetWorldMatrix()
{
	return &m_matWorldTM;
}

void cCube::AddChild( cCube* pCube )
{
	if(pCube)
		m_vecChild.push_back(pCube);
}

