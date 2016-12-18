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
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;	
	m_vecSkinnedMesh.push_back(stZombie);

	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Bloat/", "ZED_Bloat.X");
	stZombie.vPosition = D3DXVECTOR3(300, -140, 100);
	stZombie.fAngle = D3DX_PI * 0.0f;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
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
	for (int i = 0; i < m_vecSkinnedMesh.size(); ++i)
	{
		//범위 안에 드는지?
		float distance = D3DXVec3Length(&(m_vecSkinnedMesh[i].vPosition - *vPlayerPos));
		if (distance < 500.f)
		{
			D3DXVECTOR3 v = m_vecSkinnedMesh[i].vPosition - *vPlayerPos;
			D3DXVec3Normalize(&v, &v);
			float fov = D3DXVec3Dot(&m_vecSkinnedMesh[i].vDirection, &v);
			if (fov <= 1 && fov > 0.5f)
			{
				m_vecSkinnedMesh[i].isRecognize = true;
			}

			if (distance < 150.f)
				m_vecSkinnedMesh[i].isRecognize = false;
		}
		

		D3DXMATRIXA16 matS, matR, matT, mat;
		m_vecSkinnedMesh[i].pSkinnedMesh->SetAnimationIndex(m_vecSkinnedMesh[i].eMotion);
		D3DXMatrixScaling(&matS, 0.7f, 0.7f, 0.7f);
		D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &m_vecSkinnedMesh[i].vDirection, &D3DXVECTOR3(0, 1, 0));
		D3DXMatrixTranspose(&matR, &matR);
		D3DXMatrixTranslation(&matT, m_vecSkinnedMesh[i].vPosition.x, m_vecSkinnedMesh[i].vPosition.y, m_vecSkinnedMesh[i].vPosition.z);
		
		std::vector<D3DXVECTOR3> vec = m_pDijkstra->GetRoute(&m_vecSkinnedMesh[0].vPosition, vPlayerPos);
		
		if (m_vecSkinnedMesh[i].isRecognize == true)
		{
			if (m_pDijkstra->IsDirect(&m_vecSkinnedMesh[i].vPosition, vPlayerPos))
			{
				D3DXVECTOR3 vPosition = m_vecSkinnedMesh[i].vPosition;
				D3DXVECTOR3 vDirection = vPosition - (*vPlayerPos - D3DXVECTOR3(0, 70, 0));
				D3DXVec3Normalize(&vDirection, &vDirection);
				vPosition -= vDirection * m_vecSkinnedMesh[i].fSpeed;
				D3DXMatrixTranslation(&matT, vPosition.x, vPosition.y, vPosition.z);
				m_vecSkinnedMesh[i].vPosition = vPosition;
				D3DXVec3Normalize(&m_vecSkinnedMesh[i].vDirection, &vDirection);
			}
			else
			{
				std::vector<D3DXVECTOR3> vecRoute = m_pDijkstra->GetRoute(&m_vecSkinnedMesh[i].vPosition, vPlayerPos);
				for (int j = 0; j < vecRoute.size(); ++j)
				{
					D3DXVECTOR3 vPosition = m_vecSkinnedMesh[i].vPosition;
					D3DXVECTOR3 vDirection = vPosition - vecRoute[j];
					D3DXVec3Normalize(&vDirection, &vDirection);
					vPosition -= vDirection * m_vecSkinnedMesh[i].fSpeed;
					D3DXMatrixTranslation(&matT, vPosition.x, vPosition.y, vPosition.z);
					m_vecSkinnedMesh[i].vPosition = vPosition;
					D3DXVec3Normalize(&m_vecSkinnedMesh[i].vDirection, &vDirection);
				}
			}
		}

		mat = matS * matR * matT;

		m_vecSkinnedMesh[i].pSkinnedMesh->UpdateAndRender(&mat);
	}
}