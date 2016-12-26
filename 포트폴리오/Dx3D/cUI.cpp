#include "stdafx.h"
#include "cUI.h"


cUI::cUI()
	: m_pSprite(NULL)
{
}


cUI::~cUI()
{
	for (int i = 0; i < m_vTHP.size(); i++)
	{
		SAFE_RELEASE(m_vTHP[i]);
	}
	for (int i = 0; i < m_vTWeapon.size(); i++)
	{
		SAFE_RELEASE(m_vTWeapon[i]);
	}
	SAFE_RELEASE(m_pSprite);
}

void cUI::SetUp()
{
	GetClientRect(g_hWnd, &rc);
	LPDIRECT3DTEXTURE9 temp;
	//=================================ÃÑ±â·ù ============================================
	D3DXCreateTextureFromFileEx(g_pD3DDevice,"UI/Weapon/9mm.tga",D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT,0,D3DFMT_UNKNOWN,	D3DPOOL_MANAGED,D3DX_FILTER_NONE,
		D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &m_stImageInfo, NULL, &temp);
	m_vTWeapon.push_back(temp);

	D3DXCreateTextureFromFileEx(g_pD3DDevice, "UI/Weapon/bullpup.tga", D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
		D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &m_stImageInfo, NULL, &temp);
	m_vTWeapon.push_back(temp);

	D3DXCreateTextureFromFileEx(g_pD3DDevice, "UI/Weapon/knife.tga", D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
		D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &m_stImageInfo, NULL, &temp);
	m_vTWeapon.push_back(temp);

	D3DXCreateTextureFromFileEx(g_pD3DDevice, "UI/Weapon/shotgun.tga", D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
		D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &m_stImageInfo, NULL, &temp);
	m_vTWeapon.push_back(temp);

	D3DXCreateTextureFromFileEx(g_pD3DDevice, "UI/Weapon/welder.tga", D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
		D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &m_stImageInfo, NULL, &temp);
	m_vTWeapon.push_back(temp);

	//=============================== HP ===============================================
	//D3DXCreateTextureFromFileEx(g_pD3DDevice, "UI/HPback2.png", D3DX_DEFAULT_NONPOW2,
	//	D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
	//	D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &m_stImageInfo, NULL, &temp);
	//m_vTHP.push_back(temp);

	D3DXCreateTextureFromFileEx(g_pD3DDevice, "UI/HPbar.png", D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
		D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &m_stImageInfo, NULL, &temp);
	m_vTHP.push_back(temp);

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
}
void cUI::Update()
{

}
void cUI::HP_Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	D3DXMATRIXA16 matS, matW , matT;
	D3DXMatrixIdentity(&matW);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixScaling(&matS, 1.f, 1.5f, 0.f);
	D3DXMatrixTranslation(&matT, 0, rc.bottom - 50, 0);
	matW = matS * matT;
	m_pSprite->SetTransform(&matW);
	//for (int i = 0; i < m_vTHP.size(); i++)
	{
		m_pSprite->Draw(m_vTHP[0],
			&rc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			//&D3DXVECTOR3(rc.left,rc.bottom-100,0),
			D3DCOLOR_XRGB(255, 255, 255));
	}
	m_pSprite->End();
}

void cUI::Wepon_Render(GUN_NAME _name)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	D3DXMATRIXA16 matS, matW, matT;
	if (_name == HANDGUN) D3DXMatrixScaling(&matS, 0.6f, 0.6f, 0.f);
	else D3DXMatrixScaling(&matS, 0.7f, 0.7f, 0.f);
	D3DXMatrixTranslation(&matT, rc.right-200, rc.bottom - 200, 0);
	matW = matS * matT;
	m_pSprite->SetTransform(&matW);
	m_pSprite->Draw(m_vTWeapon[_name],
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pSprite->End();
}