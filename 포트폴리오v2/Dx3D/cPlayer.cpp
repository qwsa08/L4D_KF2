#include "stdafx.h"
#include "cPlayer.h"
#include "cSkinnedMesh.h"

cPlayer::cPlayer()
	:m_player(NULL)
{
	D3DXMatrixIdentity(&m_Position);
}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_player);
}


void cPlayer::SetUp()
{
	m_player = new cSkinnedMesh("Weapon X File/Weapon/", "9mm_gun.X");
	m_player->SetPosition(D3DXVECTOR3(0, 0, 10));
}
void cPlayer::Update(D3DXMATRIXA16* pmat)
{
	D3DXMATRIXA16 matS, matR;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	
	D3DXMatrixScaling(&matS, 1.5f, 1.5f, 1.5f);

	m_Position = matS * (*pmat);
	m_player->Update(&m_Position, 0);

}
void cPlayer::Render()
{
	m_player->Render(&m_Position);
}