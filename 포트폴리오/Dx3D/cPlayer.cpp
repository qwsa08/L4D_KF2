#include "stdafx.h"
#include "cPlayer.h"
#include "cSkinnedMesh.h"
#include "cOBB.h"

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
	m_pPlayer->SetPosition(D3DXVECTOR3(0, 0, 0));

	m_pOBB = new cOBB;
	m_pOBB->Setup(m_pPlayer->GetBoundingBox()->_min, m_pPlayer->GetBoundingBox()->_max, m_pPlayerBox);

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
	m_pOBB->Update(&m_Position, m_pPlayerBox);
}
void cPlayer::Render()
{
	m_pPlayer->Render(&m_Position);
	m_pOBB->DebugRender(D3DCOLOR_XRGB(255, 0, 255));
}