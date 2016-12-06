#include "stdafx.h"
#include "cZed.h"
#include "cSkinnedMesh.h"
#include "cFrustum.h"

cZed::cZed()
	: m_pSkinnedMesh(NULL)
	, m_pFrustum(NULL)

{
}


cZed::~cZed()
{
	for each(auto p in m_vecSkinnedMesh)
	{
		SAFE_DELETE(p);
	}
	SAFE_DELETE(m_pFrustum);
}

void cZed::SetUp()
{
	m_pFrustum = new cFrustum;

	m_pSkinnedMesh = new cSkinnedMesh("Zombie/Bloat/", "ZED_Bloat.X");
	//m_pSkinnedMesh->SetRandomTrackPosition();
	m_pSkinnedMesh->SetPosition(D3DXVECTOR3(0, 0, 20));
	m_vecSkinnedMesh.push_back(m_pSkinnedMesh);
}
void cZed::Update()
{

	if (m_pFrustum)
	{
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
			//	m_pFrustum->Update();
		}
	}
}
void cZed::Render(D3DXMATRIXA16* WorldTM)
{
	D3DXMATRIXA16 matI, matT, matS, matPosition;
	D3DXMatrixIdentity(&matI);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixScaling(&matS, 0.5, 0.5, 0.5);
	for each(auto p in m_vecSkinnedMesh)
	{
		if (m_pFrustum->IsIn(p->GetBoundingSphere()))
		{
			p->UpdateAndRender(WorldTM, &matS);
		}
	}
}