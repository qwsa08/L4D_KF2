#include "StdAfx.h"
#include "cUIButton.h"


cUIButton::cUIButton(void)
	: m_eButtonState(E_STATE_NORMAL)
	, m_pDelegate(NULL)
{
	for (int i = 0; i < E_STATE_COUNT; ++i)
	{
		m_aTexture[i] = NULL;
	}
}

cUIButton::~cUIButton(void)
{
	for (int i = 0; i < E_STATE_COUNT; ++i)
	{
		SAFE_RELEASE(m_aTexture[i]);
	}
}

void cUIButton::SetTexture( char* szNor, char* szOvr, char* szSel )
{
	D3DXIMAGE_INFO stImageInfo;
	
	m_aTexture[E_STATE_NORMAL] = g_pTextureManager->GetSpriteTexture(szNor, &stImageInfo);
	SAFE_ADD_REF(m_aTexture[E_STATE_NORMAL]);

	m_aTexture[E_STATE_MOVER] = g_pTextureManager->GetSpriteTexture(szOvr, &stImageInfo);
	SAFE_ADD_REF(m_aTexture[E_STATE_MOVER]);

	m_aTexture[E_STATE_SELECTED] = g_pTextureManager->GetSpriteTexture(szSel, &stImageInfo);
	SAFE_ADD_REF(m_aTexture[E_STATE_SELECTED]);

	m_stSize.fWidth = stImageInfo.Width;
	m_stSize.fHeight = stImageInfo.Height;
}

void cUIButton::Update(bool isSelected, OUT int* button)
{
	cUIObject::Update(isSelected, button);

	if (isSelected)
	{
		m_eButtonState = E_STATE_SELECTED;
	}
	else
	{
		m_eButtonState = E_STATE_NORMAL;
	}

	if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
	{
		if (m_eButtonState == E_STATE_SELECTED)
		{
			//			if (m_pDelegate)
			//			{
			//				*button = m_pDelegate->OnClick(this);
			//			}
			*button = 1;
		}
		else
			*button = 2;
	}
	//POINT pt;
	//GetCursorPos(&pt);
	//ScreenToClient(g_hWnd, &pt);

	//RECT rc;
	//SetRect(&rc,
	//	m_matWorld._41,
	//	m_matWorld._42,
	//	m_matWorld._41 + m_stSize.fWidth,
	//	m_matWorld._42 + m_stSize.fHeight);


	//bool isLButtonDown = (bool)(GetKeyState(VK_LBUTTON) & 0x8000);

	//if (PtInRect(&rc, pt))
	//{
	//	if (isLButtonDown)
	//	{
	//		if (m_eButtonState == E_STATE_MOVER)
	//		{
	//			m_eButtonState = E_STATE_SELECTED;
	//		}
	//	}
	//	else
	//	{
	//		if (m_eButtonState == E_STATE_SELECTED)
	//		{
	//			if (m_pDelegate)
	//			{
	//				m_pDelegate->OnClick(this);
	//			}
	//		}
	//		m_eButtonState = E_STATE_MOVER;
	//	}
	//}
	//else
	//{
	//	if (!isLButtonDown)
	//	{
	//		m_eButtonState = E_STATE_NORMAL;
	//	}
	//}
}

void cUIButton::Render( LPD3DXSPRITE pSprite )
{
	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.fWidth, m_stSize.fHeight);
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&m_matWorld);
	pSprite->Draw(m_aTexture[m_eButtonState],
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	pSprite->End();

	cUIObject::Render(pSprite);
}
