#include "stdafx.h"
#include "cPlayer.h"
#include "cSkinnedMesh.h"

cPlayer::cPlayer()
	:m_pPlayer(NULL)
{
	D3DXMatrixIdentity(&m_Position);
}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_pPlayer);
}


void cPlayer::SetUp()
{
	m_pPlayer = new cSkinnedMesh("Weapon X File/test/", "center.X");
	m_pPlayer->SetPosition(D3DXVECTOR3(0, 0, 10));
}
void cPlayer::Update(D3DXMATRIXA16* pmat)
{
	D3DXMATRIXA16 matS, matR;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	
	D3DXMatrixScaling(&matS, 1.5f, 1.5f, 1.5f);

	if (pmat)
		m_Position = matS * (*pmat);
	else
		m_Position = matS;

	m_pPlayer->Update(&m_Position, 0);
}
void cPlayer::Render()
{
	m_pPlayer->Render(&m_Position);
}