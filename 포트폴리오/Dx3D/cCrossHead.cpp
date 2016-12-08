#include "stdafx.h"
#include "cCrossHead.h"
#include "cCrtController.h"

cCrossHead::cCrossHead()
	:m_pSprite(NULL)
	, m_pTexture(NULL)
{
	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"CrossHead.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stImageInfo,
		NULL,
		&m_pTexture);

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
}


cCrossHead::~cCrossHead()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
}

void cCrossHead::Render()
{
	SetRect(&rc, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);
	GetClientRect(g_hWnd, &rcClient);
	
	
	D3DXMATRIXA16 matWorld, matS, matT;
	D3DXMatrixIdentity(&matWorld);
	//D3DXMatrixScaling(&matS, 1, 1, 1.5);
	D3DXMatrixTranslation(&matT,
		rcClient.right / 2 - m_stImageInfo.Width / 2,
		rcClient.bottom / 2 - m_stImageInfo.Height / 2,
		0);
	matWorld = matT;

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(m_pTexture,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pSprite->End();
}