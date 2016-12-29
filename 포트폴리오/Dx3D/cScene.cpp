#include "stdafx.h"
#include "cScene.h"
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"

enum eUITag
{
	E_START,
	E_QUIT,
};
cScene::cScene()
	: m_pUIRoot(NULL)
	, m_isSelected(true)
{
}


cScene::~cScene()
{
	SAFE_RELEASE(m_pUIRoot);
	SAFE_RELEASE(m_pSprite);
}

void cScene::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	cUIImageView* pImageView = new cUIImageView;
	D3DXIMAGE_INFO stImageInfo;
	ZeroMemory(&stImageInfo, sizeof(D3DXIMAGE_INFO));
	LPDIRECT3DTEXTURE9 pTexture = g_pTextureManager->GetSpriteTexture(
		"./UI/L4D.jpg",
		&stImageInfo);
	pImageView->SetTexture(pTexture);
	pImageView->SetSize(ST_SIZE(stImageInfo.Width, stImageInfo.Height));
	pImageView->SetLocalPos(D3DXVECTOR3(0, 0, 0));
	m_pUIRoot = pImageView;

	cUIButton* pButton = NULL;
	pButton = new cUIButton;
	pButton->SetTexture("./UI/UIButton_Start.png",
		"./UI/UIButton_Start.png",
		"./UI/UIButton_Start_Selected.png");
	pButton->SetLocalPos(D3DXVECTOR3(400, 330, 0));
	pButton->SetDelegate(this);
	pButton->SetTag(E_START);
	pButton->AutoRelease();
	m_pUIRoot->AddChild(pButton);

	pButton = new cUIButton;
	pButton->SetTexture("./UI/UIButton_Quit.png",
		"./UI/UIButton_Quit.png",
		"./UI/UIButton_Quit_Selected.png");
	pButton->SetLocalPos(D3DXVECTOR3(400, 380, 0));
	pButton->SetDelegate(this);
	pButton->SetTag(E_QUIT);
	pButton->AutoRelease();
	m_pUIRoot->AddChild(pButton);
}

void cScene::Update(int* button)
{
	if (g_pKeyManager->isOnceKeyDown(VK_UP) || g_pKeyManager->isOnceKeyDown(VK_DOWN))
	{
		if (m_isSelected) m_isSelected = false;
		else m_isSelected = true;
	}

	if (m_pUIRoot)
		m_pUIRoot->Update(m_isSelected, button);
}

void cScene::Render()
{
	if (m_pUIRoot)
	{
		m_pUIRoot->Render(m_pSprite);
	}
}

void cScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

int cScene::OnClick(cUIButton * pSender)
{
	if (pSender->GetTag() == E_START)
	{
		return 1;
//		pTextView->SetText("E_BUTTON1");
	}
	else if (pSender->GetTag() == E_QUIT)
	{
		return 2;
//		pTextView->SetText("E_BUTTON2");
	}
}
