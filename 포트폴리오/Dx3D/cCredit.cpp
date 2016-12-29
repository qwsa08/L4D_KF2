#include "stdafx.h"
#include "cCredit.h"


cCredit::cCredit()
	: m_pSprite(NULL)
	, m_pTexture(NULL)
	, m_nScroll(0)
{
}


cCredit::~cCredit()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
}

void cCredit::Setup()
{
	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"UI/Credit.jpg",
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
		&m_pTexture);

	GetClientRect(g_hWnd, &m_Rect);
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
}

void cCredit::Update()
{
	m_nScroll--;
}

void cCredit::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	D3DXMATRIXA16 matS, matW;
	D3DXMatrixIdentity(&matW);
	D3DXMatrixIdentity(&matS);
//	D3DXMatrixScaling(&matS, 2.f, 1.5f, 1.f);
	matW *= matS;
	m_pSprite->SetTransform(&matW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pSprite->Draw(m_pTexture,
		&m_Rect,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, m_nScroll, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pSprite->End();
}
