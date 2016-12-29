#include "StdAfx.h"
#include "cUITextView.h"


cUITextView::cUITextView(void)
	: m_pFont(NULL)
	, m_dwDrawTextFormat(DT_TOP | DT_LEFT)
	, m_dwColor(D3DCOLOR_XRGB(255, 255, 255))
{
}

cUITextView::~cUITextView(void)
{
	SAFE_RELEASE(m_pFont);
}

void cUITextView::Render( LPD3DXSPRITE pSprite )
{
	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.fWidth, m_stSize.fHeight);
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&m_matWorld);
	m_pFont->DrawTextA(pSprite, 
		m_sText.c_str(),
		m_sText.length(),
		&rc, 
		m_dwDrawTextFormat, 
		m_dwColor);
	pSprite->End();
}
