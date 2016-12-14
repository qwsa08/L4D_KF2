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
	stZombie.vPosition = D3DXVECTOR3(0, -120, 0);
	stZombie.fAngle = D3DX_PI / 2.0f;
	stZombie.eMotion = IDLE;	
	m_vecSkinnedMesh.push_back(stZombie);

	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Bloat/", "ZED_Bloat.X");
	stZombie.vPosition = D3DXVECTOR3(300, -120, 0);
	stZombie.fAngle = D3DX_PI * 3 / 4.0f;
	stZombie.eMotion = IDLE;
	m_vecSkinnedMesh.push_back(stZombie);
}

void cBloat::UpdateAndRender(int nDest)
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
	for (int i = 0; i < m_vecSkinnedMesh.size(); ++i)
	{
		D3DXMATRIXA16 matS, matR, matT, mat;
		m_vecSkinnedMesh[i].pSkinnedMesh->SetAnimationIndex(m_vecSkinnedMesh[i].eMotion);
		D3DXMatrixScaling(&matS, 0.7f, 0.7f, 0.7f);
		D3DXMatrixRotationY(&matR, m_vecSkinnedMesh[i].fAngle);
		
		int nStart = m_pDijkstra->GetDestNode(&m_vecSkinnedMesh[i].vPosition);
		std::vector<D3DXVECTOR3> vecNode = m_pDijkstra->GetNodeTable(nStart, nDest);

		D3DXVECTOR3 vDirection = m_vecSkinnedMesh[i].vPosition - vecNode[0];
		D3DXVECTOR3 vPosition = m_vecSkinnedMesh[i].vPosition;

		vPosition -= vDirection * 0.01f;
		m_vecSkinnedMesh[i].vPosition = vPosition;
		D3DXMatrixTranslation(&matT, vPosition.x, vPosition.y, vPosition.z);
		mat = matS * matR * matT;

		m_vecSkinnedMesh[i].pSkinnedMesh->UpdateAndRender(&mat);
	}
}