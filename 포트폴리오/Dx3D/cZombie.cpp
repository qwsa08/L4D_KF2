#include "stdafx.h"
#include "cZombie.h"


cZombie::cZombie()
	: m_pDijkstra(NULL)
	, m_pFrustum(NULL)
	, m_pBlood(NULL)
	, m_pSprite(NULL)
	, m_Blood(false)
	, m_fBloodTime(0.f)
{
}


cZombie::~cZombie()
{
	for each(auto p in m_vecSkinnedMesh)
	{
		SAFE_DELETE(p.pSkinnedMesh);
	}
//	SAFE_DELETE(m_pDijkstra);
//	SAFE_DELETE(m_pOBB);
//	SAFE_DELETE(m_pFrustum);
	SAFE_RELEASE(m_pBlood);
	SAFE_RELEASE(m_pSprite);
}

void cZombie::SetBlood()
{
	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"Effect/blood3.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 0, 0),
		NULL,
		NULL,
		&m_pBlood);

	GetClientRect(g_hWnd, &m_Rect);
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
}


void cZombie::AttackBlood()
{
	if (m_Blood)
	{
		m_fBloodTime += g_pTimeManager->GetDeltaTime();

		if (m_fBloodTime > 0.2f)
		{
			m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
			D3DXMATRIXA16 matS, matW;
			D3DXMatrixIdentity(&matW);
			//D3DXMatrixIdentity(&matS);
			D3DXMatrixScaling(&matS, 1.2f, 1.f, 1.f);
			matW *= matS;
			m_pSprite->SetTransform(&matW);
			g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
			g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
			m_pSprite->Draw(m_pBlood,
				&m_Rect,
				&D3DXVECTOR3(0, 0, 0),
				&D3DXVECTOR3(0, 0, 0),
				D3DCOLOR_XRGB(255, 255, 255));
			m_pSprite->End();
		}
		if (m_fBloodTime > 2.f)
		{
			m_Blood = false;
			m_fBloodTime = 0.f;
		}
	}
}
