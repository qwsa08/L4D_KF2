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
	
	m_pGun[HANDGUN] = new cSkinnedMesh("Weapon X File/test/", "Idle.X");
	m_pGun[HANDGUN]->SetPosition(D3DXVECTOR3(0, 0, 0));

	m_pGun[BUSTER] = new cSkinnedMesh("Weapon X File/b/", "Idle.X");
	m_pGun[BUSTER]->SetPosition(D3DXVECTOR3(0, 0, 0));

	m_pGun[KNIFE] = new cSkinnedMesh("Weapon X File/knife/", "Idle.X");
	m_pGun[KNIFE]->SetPosition(D3DXVECTOR3(0, 0, 0));

	m_pGun[SHOT] = new cSkinnedMesh("Weapon X File/Shot/", "Idle.X");
	m_pGun[SHOT]->SetPosition(D3DXVECTOR3(0, 0, 0));

	m_pGun[HEAL] = new cSkinnedMesh("Weapon X File/Heal/", "Idle.X");
	m_pGun[HEAL]->SetPosition(D3DXVECTOR3(0, 0, 0));

	m_pPlayer = m_pGun[HANDGUN];
	m_pOBB = new cOBB;
	m_pOBB->Setup(m_pPlayer->GetBoundingBox()->_min, m_pPlayer->GetBoundingBox()->_max, m_pPlayerBox);
	m_eGunName = HANDGUN;

	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"Effect/BloodOverlay.png",
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
	
	if (g_pKeyManager->isOnceKeyDown('1'))
	{
		m_pPlayer = m_pGun[BUSTER];
		m_eGunName = BUSTER;
	}
	if (g_pKeyManager->isOnceKeyDown('2'))
	{
		m_pPlayer = m_pGun[KNIFE];
		m_eGunName = KNIFE;
	}
	if (g_pKeyManager->isOnceKeyDown('3'))
	{
		m_pPlayer = m_pGun[SHOT];
		m_eGunName = SHOT;
	}
	if (g_pKeyManager->isOnceKeyDown('4'))
	{
		m_pPlayer = m_pGun[HEAL];
		m_eGunName = HEAL;
	}
	if (g_pKeyManager->isOnceKeyDown('R'))
	{
		//m_pPlayer->SetFrameNum(2);
		//두번 호출하는 이유는...?;; 그 한번만하면 보간이된다..그래서 2번호출함으로써.. 초기화;;
		//이걸 고쳐야한다.. 한번만하면되도록
		
		m_pPlayer->SetAnimationIndex(2);
		m_pPlayer->SetAnimationIndex(2);
		//m_pPlayer->SetFrameNum(2);
		m_pPlayer->SetAction(true);
	}

}
void cPlayer::SetAni(int num)
{
	m_pPlayer->SetFrameNum(num);
	m_pPlayer->SetAnimationIndex(num);
	m_pPlayer->SetAction(true);
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
	D3DXMatrixScaling(&matS, 1.5f, 1.f, 0.f);
	matW *= matS;
	m_pSprite->SetTransform(&matW);
	m_pSprite->Draw(m_Tblood,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pSprite->End();
}