#include "stdafx.h"
#include "cPlayer.h"
#include "cSkinnedMesh.h"
#include "cOBB.h"
#include "cCrossHead.h"
cPlayer::cPlayer()
	:m_pPlayer(NULL)
	, m_pOBB(NULL)
	
{
	D3DXMatrixIdentity(&m_Position);
}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_pOBB);
	
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

	D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, 3, 0, 12);
	D3DXMatrixScaling(&matS, 1.5f, 1.5f, 1.5f);

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
