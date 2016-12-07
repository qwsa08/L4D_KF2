#include "stdafx.h"
#include "cPlayer.h"
#include "cSkinnedMesh.h"
#include "cOBB.h"

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
	m_player = new cSkinnedMesh("Weapon X File/test/", "center.X");
	m_player->SetPosition(D3DXVECTOR3(0, 0, 10));
	
	m_test = new cOBB;
	m_test->Setup(m_player->GetBoundingBox()->_min, m_player->GetBoundingBox()->_max, m_pPlayerBox);
}
void cPlayer::Update(D3DXMATRIXA16* pmat)
{
	D3DXMATRIXA16 matS, matR;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	
	D3DXMatrixScaling(&matS, 1.5f, 1.5f, 1.5f);

	m_Position = matS * (*pmat);
	m_player->Update(&m_Position, 0);

	m_test->Update(&m_Position, m_pPlayerBox);
}
void cPlayer::Render()
{
	m_player->Render(&m_Position);
	
	m_test->DebugRender(D3DCOLOR_XRGB(255, 0, 255));
}
ST_OBB* cPlayer::GetPlayerBox()
{
	return m_player->GetOBB();

}