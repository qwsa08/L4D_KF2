#include "stdafx.h"
#include "cPlayer.h"
#include "cSkinnedMesh.h"
#include "cOBB.h"
#include "cCrossHead.h"
#include "cBoss.h"

cPlayer::cPlayer()
	:m_pPlayer(NULL)
	, m_pOBB(NULL)
	, m_Tblood(NULL)
	, m_pSprite(NULL)
	, m_timer(0.6f)
	, m_bZoomIn(false)
	, m_bZoomOut(false)
	, m_isReload(false)
{
	D3DXMatrixIdentity(&m_Position);
	D3DXMatrixIdentity(&m_matT);

}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_pOBB);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_Tblood);


}


void cPlayer::SetUp()
{
	m_pGun[HANDGUN] = new cSkinnedMesh("Weapon X File/test/", "Idle3.X");
	m_pGun[HANDGUN]->SetPosition(D3DXVECTOR3(0, 0, 0));
	m_iGunBullet[HANDGUN] = H_BULLET;
	m_iGunBulletFull[HANDGUN] = 99;
	m_iCurrentBullet[HANDGUN] = H_BULLET;

	m_pGun[BUSTER] = new cSkinnedMesh("Weapon X File/b/", "Idle3.X");
	m_pGun[BUSTER]->SetPosition(D3DXVECTOR3(0, 0, 0));
	m_iGunBullet[BUSTER] = B_BULLET;
	m_iGunBulletFull[BUSTER] = 90;
	m_iCurrentBullet[BUSTER] = B_BULLET;

	m_pGun[KNIFE] = new cSkinnedMesh("Weapon X File/knife/", "Idle2.X");
	m_pGun[KNIFE]->SetPosition(D3DXVECTOR3(0, 0, 0));
	m_iGunBullet[KNIFE] = K_BULLET;
	m_iGunBulletFull[KNIFE] = 99;
	m_iCurrentBullet[KNIFE] = K_BULLET;

	m_pGun[SHOT] = new cSkinnedMesh("Weapon X File/Shot/", "Idle3.X");
	m_pGun[SHOT]->SetPosition(D3DXVECTOR3(0, 0, 0));
	m_iGunBullet[SHOT] = S_BULLET;
	m_iGunBulletFull[SHOT] = 40;
	m_iCurrentBullet[SHOT] = S_BULLET;

	m_pGun[HEAL] = new cSkinnedMesh("Weapon X File/Heal/", "Idle2.X");
	m_pGun[HEAL]->SetPosition(D3DXVECTOR3(0, 0, 0));
	m_iGunBullet[HEAL] = Heal_BULLET;
	m_iGunBulletFull[HEAL] = 1;
	m_iCurrentBullet[HEAL] = Heal_BULLET;

	m_pPlayer = m_pGun[HANDGUN];
	m_eGunName = HANDGUN;
	m_pOBB = new cOBB;
	m_pOBB->Setup(m_pPlayer->GetBoundingBox()->_min, m_pPlayer->GetBoundingBox()->_max, m_pPlayerBox);
	m_pPlayer->SetGunName(HANDGUN);

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
		D3DCOLOR_XRGB(0,0,0),
		&m_stImageInfo,
		NULL,
		&m_Tblood);

	

	GetClientRect(g_hWnd, &rc);
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	

}
void cPlayer::Update(D3DXMATRIXA16* pmat)
{
	if (!g_pSoundManager->isPlaySound("Player_Breath"))
		g_pSoundManager->play("Player_Breath", 0.02f);

	D3DXMATRIXA16 matS, matR, matT;
	/*D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);*/
	//D3DXMatrixTranslation(&matT, 0, 0.5f , 0);
	//D3DXMatrixScaling(&matS, 1.5f, 1.5f, 1.5f);
	D3DXMatrixRotationY(&matR, -D3DX_PI / 2.f);
	D3DXMatrixIdentity(&matS);
	//D3DXMatrixScaling(&matS, 0.5f, 0.5f, 0.5f);
	
	if (pmat)
		m_Position = matS  *matR  * m_matT *(*pmat);
	else
		m_Position = matS * matR *m_matT;

	m_pPlayer->Update(&m_Position, 0);
	m_pOBB->Update(&m_Position, m_pPlayerBox);
	
	WeaponSelect();

	m_pPlayer->SetGunName(m_eGunName);

	ReloadButton();

	ZoomIn();
	
	m_pPlayer = m_pGun[m_eGunName];
}
void cPlayer::SetAni(int num)
{
	m_pPlayer->SetFrameNum(num);
	m_pPlayer->SetAnimationIndex(num);
	
}
void cPlayer::Render()
{
	m_pPlayer->Render(&m_Position);
	m_pOBB->DebugRender(&m_pPlayerBox, D3DCOLOR_XRGB(255, 0, 255));
}
void cPlayer::Blood()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	D3DXMATRIXA16 matS,matW;
	D3DXMatrixIdentity(&matW);
	//D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, 1.5f, 1.2f, 0.f);
	matW *= matS;
	m_pSprite->SetTransform(&matW);
	m_pSprite->Draw(m_Tblood,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pSprite->End();
}

int cPlayer::GetMaxBullet()
{
	return m_iGunBulletFull[m_eGunName];
}
int cPlayer::GetBullet()
{
	return m_iGunBullet[m_eGunName];
}

void cPlayer::fireBullet()
{
	m_iGunBullet[m_eGunName] -= 1;
}

void cPlayer::Reload()
{
	m_isReload = true;

	if (m_eGunName == HANDGUN || m_eGunName == BUSTER || m_eGunName == SHOT)
	{
		m_bZoomIn = false;
		m_pPlayer->AnimationReset();
		m_pPlayer->SetAnimationIndex(2);
		m_pPlayer->SetFrameNum(2);

		if (m_iGunBulletFull[m_eGunName] <= m_iCurrentBullet[m_eGunName])
		{
			m_iGunBullet[m_eGunName] = m_iGunBulletFull[m_eGunName];
			m_iGunBulletFull[m_eGunName] = 0;
		}
		else
		{
			m_iGunBulletFull[m_eGunName] = m_iGunBulletFull[m_eGunName] - (m_iCurrentBullet[m_eGunName] - m_iGunBullet[m_eGunName]);
			m_iGunBullet[m_eGunName] = m_iCurrentBullet[m_eGunName];
		}
	}
}

void cPlayer::WeaponSelect()
{
	if (g_pKeyManager->isOnceKeyDown('0'))
	{
		m_eGunName = HANDGUN;
		m_pPlayer->AnimationReset();
		m_pPlayer->SetNomalAnimationIndex(0);
		g_pSoundManager->play("9mm_Select", 0.2f);
	}

	if (g_pKeyManager->isOnceKeyDown('1'))
	{
		m_eGunName = BUSTER;
		m_pPlayer->AnimationReset();
		m_pPlayer->SetNomalAnimationIndex(0);
		g_pSoundManager->play("Bullpup_Select", 0.2f);
	}

	if (g_pKeyManager->isOnceKeyDown('2'))
	{
		m_eGunName = KNIFE;
		m_pPlayer->AnimationReset();
		m_pPlayer->SetNomalAnimationIndex(0);
		g_pSoundManager->play("Knife_Select", 0.2f);
	}

	if (g_pKeyManager->isOnceKeyDown('3'))
	{
		m_eGunName = SHOT;
		m_pPlayer->AnimationReset();
		m_pPlayer->SetNomalAnimationIndex(0);
		g_pSoundManager->play("Shotgun_Select", 0.2f);
	}

	if (g_pKeyManager->isOnceKeyDown('4'))
	{
		m_eGunName = HEAL;
		m_pPlayer->AnimationReset();
		m_pPlayer->SetNomalAnimationIndex(0);
		g_pSoundManager->play("Heal_Select", 0.2f);
	}
}

void cPlayer::ReloadButton()
{
	if (g_pKeyManager->isOnceKeyDown('R'))
	{
		Reload();

		if (m_eGunName == BUSTER)
			g_pSoundManager->stop("Bullpup_Reload");

		if (m_eGunName == SHOT)
			g_pSoundManager->stop("Shotgun_Reload");

		if (m_eGunName == HANDGUN)
			g_pSoundManager->stop("9mm_Single_Reload");
	}

	if (m_isReload)
	{
		if (m_eGunName == BUSTER)
		{
			if (!g_pSoundManager->isPlaySound("Bullpup_Reload"))
				g_pSoundManager->play("Bullpup_Reload", 0.2f);

			m_isReload = false;
		}

		else if (m_eGunName == SHOT)
		{
			if (!g_pSoundManager->isPlaySound("Shotgun_Reload"))
				g_pSoundManager->play("Shotgun_Reload", 0.2f);

			m_isReload = false;
		}
		
		else if (m_eGunName == HANDGUN)
		{
			if (!g_pSoundManager->isPlaySound("9mm_Single_Reload"))
				g_pSoundManager->play("9mm_Single_Reload", 0.2f);

			m_isReload = false;
		}
	}
}

void cPlayer::ZoomIn()
{
	if (m_eGunName == BUSTER)
	{
		if (g_pKeyManager->isOnceKeyDown(VK_RBUTTON))
		{
			m_timer = 0.f;
			m_bZoomIn = !m_bZoomIn;

			if (!g_pSoundManager->isPlaySound("Bullpup_Aim"))
				g_pSoundManager->play("Bullpup_Aim", 0.5f);
		}
	}

	if (m_bZoomIn)
	{
		if (m_matT._42 < 0.85)
		{
			m_matT._41 -= 0.1;
			m_matT._42 += 0.03;
			m_matT._43 -= 0.2;
		}
	}
	else
	{
		if (m_matT._42 >-0.15)
		{
			m_matT._41 += 0.1;
			m_matT._42 -= 0.03;
			m_matT._43 += 0.2;
		}
	}
}