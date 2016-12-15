#include "stdafx.h"
#include "cPlayer.h"
#include "cSkinnedMesh.h"
#include "cOBB.h"
#include "cCrossHead.h"
cPlayer::cPlayer()
	:m_pPlayer(NULL)
	, m_pOBB(NULL)
	, m_Tblood(NULL)
	, m_pSprite(NULL)
	
{
	D3DXMatrixIdentity(&m_Position);
}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_pOBB);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_Tblood);
}


void cPlayer::SetUp()
{
	m_pPlayer = new cSkinnedMesh("Weapon X File/test/", "test.X");
	m_pPlayer->SetPosition(D3DXVECTOR3(0, 0, 0));

	m_pOBB = new cOBB;
	m_pOBB->Setup(m_pPlayer->GetBoundingBox()->_min, m_pPlayer->GetBoundingBox()->_max, m_pPlayerBox);


	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"Effect/blood.png",
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
		&m_Tblood);

	

	GetClientRect(g_hWnd, &rc);
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

}
void cPlayer::Update(D3DXMATRIXA16* pmat)
{

	D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	//D3DXMatrixTranslation(&matT, 3, 0, 12);
	//D3DXMatrixScaling(&matS, 1.5f, 1.5f, 1.5f);

	if (pmat)
		m_Position = matS  *matT *(*pmat);
	else
		m_Position = matS * matT;

	m_pPlayer->Update(&m_Position, 0);
	m_pOBB->Update(&m_Position, m_pPlayerBox);
	

}
void cPlayer::Render()
{
	m_pPlayer->Render(&m_Position);
	m_pOBB->DebugRender(D3DCOLOR_XRGB(255, 0, 255));
}
void cPlayer::Blood()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	D3DXMATRIXA16 matS,matW;
	D3DXMatrixIdentity(&matW);
	D3DXMatrixScaling(&matS, 6, 4, 0);

	matW *= matS;
	m_pSprite->SetTransform(&matW);
	m_pSprite->Draw(m_Tblood,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pSprite->End();
}