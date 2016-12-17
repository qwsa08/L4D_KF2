#include "stdafx.h"
#include "cBloat.h"
#include "cSkinnedMesh.h"
#include "cDijkstra.h"


cBloat::cBloat()
{
}


cBloat::~cBloat()
{
}

void cBloat::Setup()
{
	ST_ZOMBIE stZombie;
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Bloat/", "ZED_Bloat.X");
	stZombie.vPosition = D3DXVECTOR3(-700, -140, 2200);
	stZombie.fAngle = D3DX_PI / 2.0f;
	stZombie.eMotion = IDLE;	
	m_vecSkinnedMesh.push_back(stZombie);

	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Bloat/", "ZED_Bloat.X");
	stZombie.vPosition = D3DXVECTOR3(300, -140, 100);
	stZombie.fAngle = D3DX_PI * 0.0f;
	stZombie.eMotion = IDLE;
	m_vecSkinnedMesh.push_back(stZombie);
}

void cBloat::UpdateAndRender(D3DXVECTOR3* vPlayerPos)
{
	//for each(auto p in m_vecSkinnedMesh)
	//{
	//	D3DXMATRIXA16 matS, matR, matT, mat;
	//	p.pSkinnedMesh->SetAnimationIndex(p.eMotion);
	//	D3DXMatrixScaling(&matS, 0.7f, 0.7f, 0.7f);
	//	D3DXMatrixRotationY(&matR, p.fAngle);

	//	D3DXVECTOR3 vDirection = p.vPosition - (*vecNode)[(*vecNode).size() - 1];
	//	D3DXVECTOR3 vPosition = p.vPosition;
	//	vPosition -= vDirection * 0.01f;
	//	p.vPosition = vPosition;
	//	D3DXMatrixTranslation(&matT, vPosition.x, vPosition.y, vPosition.z);
	//	mat = matS * matR * matT;

	//	p.pSkinnedMesh->UpdateAndRender(&mat);
	//}
	if (g_pKeyManager->isOnceKeyDown(VK_RBUTTON))
	{
		if (m_vecSkinnedMesh[0].isRecognize)
		{
			m_vecSkinnedMesh[0].isRecognize = false;
		}
		else
		{
			m_vecSkinnedMesh[0].isRecognize = true;
		}		
	}
	for (int i = 0; i < m_vecSkinnedMesh.size(); ++i)
	{
		D3DXMATRIXA16 matS, matR, matT, mat;
		m_vecSkinnedMesh[i].pSkinnedMesh->SetAnimationIndex(m_vecSkinnedMesh[i].eMotion);
		D3DXMatrixScaling(&matS, 0.7f, 0.7f, 0.7f);
		D3DXMatrixRotationY(&matR, m_vecSkinnedMesh[i].fAngle);
		D3DXMatrixIdentity(&matT);
		
		std::vector<D3DXVECTOR3> vec = m_pDijkstra->GetRoute(&m_vecSkinnedMesh[0].vPosition, vPlayerPos);
		
		if (m_vecSkinnedMesh[i].isRecognize == true)
		{

		}
		else
		{
			D3DXMatrixTranslation(&matT, m_vecSkinnedMesh[i].vPosition.x, m_vecSkinnedMesh[i].vPosition.y, m_vecSkinnedMesh[i].vPosition.z);
		}

		mat = matS * matR * matT;
		m_vecSkinnedMesh[i].pSkinnedMesh->UpdateAndRender(&mat);
	}
//	D3DXVECTOR3 line[4];
//	line[0] = m_vecSkinnedMesh[0].vPosition;
//	line[1] = *vPlayerPos;
//	line[2] = m_vecSkinnedMesh[1].vPosition;
//	line[3] = *vPlayerPos;
//	D3DXMATRIXA16 mt;
//	D3DXMatrixIdentity(&mt);
//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mt);
//	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, 2, &line[0], sizeof(D3DXVECTOR3));
}