#include "stdafx.h"
#include "cClot.h"
#include "cSkinnedMesh.h"
#include "cDijkstra.h"


cClot::cClot()
{
}


cClot::~cClot()
{
}

void cClot::Setup()
{
	ST_ZOMBIE stZombie;
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	stZombie.vPosition = D3DXVECTOR3(100, -140, 150);
	stZombie.fAngle = D3DX_PI / 2.0f;
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	stZombie.fSpeed = 3.f;
	m_vecSkinnedMesh.push_back(stZombie);

	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	stZombie.vPosition = D3DXVECTOR3(600, -140, 100);
	stZombie.fAngle = D3DX_PI / 2.0f;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	m_vecSkinnedMesh.push_back(stZombie);

	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	stZombie.vPosition = D3DXVECTOR3(500, -140, 0);
	stZombie.fAngle = D3DX_PI / 2.0f;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	m_vecSkinnedMesh.push_back(stZombie);

	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	stZombie.vPosition = D3DXVECTOR3(-280, -140, -450);
	stZombie.fAngle = D3DX_PI / 2.0f;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	m_vecSkinnedMesh.push_back(stZombie);

	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	stZombie.vPosition = D3DXVECTOR3(-280, -140, -750);
	stZombie.fAngle = D3DX_PI / 2.0f;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	m_vecSkinnedMesh.push_back(stZombie);
}

void cClot::UpdateAndRender(D3DXVECTOR3 * vPlayerPos)
{
	for (int i = 0; i < m_vecSkinnedMesh.size(); ++i)
	{
		//범위?
		D3DXVECTOR3 v = m_vecSkinnedMesh[i].vPosition - (*vPlayerPos - D3DXVECTOR3(0, 70, 0));
		float fDistance = D3DXVec3Length(&v);
		D3DXVec3Normalize(&v, &v);

		if (fDistance < 500.f)
		{
			//시야
			float fFov = D3DXVec3Dot(&m_vecSkinnedMesh[i].vDirection, &v);
			if (fFov <= 1 && fFov > 0.5f)
			{
				m_vecSkinnedMesh[i].isRecognize = true;
			}
		}
		else if (fDistance > 1000.f)
		{
		}

		if (m_vecSkinnedMesh[i].isRecognize)
		{
			//디렉션을 먼저 바꾸고 움직이고 싶은데 어떻게 드드드돌게 하지
			if (m_pDijkstra->IsDirect(&m_vecSkinnedMesh[i].vPosition, vPlayerPos))
			{
				if (fDistance < 70.f)
				{
					m_vecSkinnedMesh[i].eMotion = ATTACK_MELEE;
				}
				else
				{
					float fFov = D3DXVec3Dot(&m_vecSkinnedMesh[i].vDirection, &v);
					if (1 - fabs(fFov) < EPSILON)
					{
						m_vecSkinnedMesh[i].eMotion = MOVE;
						m_vecSkinnedMesh[i].vPosition -= m_vecSkinnedMesh[i].vDirection * m_vecSkinnedMesh[i].fSpeed;
					}
					else
					{
						D3DXVECTOR3 v0 = m_vecSkinnedMesh[i].vPosition + fDistance * m_vecSkinnedMesh[i].vDirection;
						D3DXVECTOR3 v1 = *vPlayerPos - D3DXVECTOR3(0, 70, 0);
						D3DXVECTOR3 vPos(0, 0, 0);
						D3DXVec3Lerp(&vPos, &v0, &v1, D3DXVec3Length(&v0) / fDistance);
						D3DXVec3Normalize(&m_vecSkinnedMesh[i].vDirection, &(m_vecSkinnedMesh[i].vPosition - vPos));
					}
				}
				m_vecSkinnedMesh[i].vPrevPosition = m_vecSkinnedMesh[i].vPosition;
			}
			else//다익스트라
			{
				std::vector<D3DXVECTOR3> vecRoute = m_pDijkstra->GetRoute(&m_vecSkinnedMesh[i].vPosition, vPlayerPos);

				m_vecSkinnedMesh[i].eMotion = MOVE;

				if (vecRoute.size() < 2)
				{
					D3DXVec3Normalize(&m_vecSkinnedMesh[i].vDirection, &(m_vecSkinnedMesh[i].vPosition - vecRoute[0]));
					m_vecSkinnedMesh[i].vPosition -= m_vecSkinnedMesh[i].vDirection * m_vecSkinnedMesh[i].fSpeed;
				}
				else if (vecRoute.size() < 6)
				{
					if (m_vecSkinnedMesh[i].vPrevPosition != vecRoute[0])
					{
						D3DXVec3Normalize(&m_vecSkinnedMesh[i].vDirection, &(m_vecSkinnedMesh[i].vPosition - vecRoute[0]));
						m_vecSkinnedMesh[i].vPosition -= m_vecSkinnedMesh[i].vDirection * m_vecSkinnedMesh[i].fSpeed;

						float l = D3DXVec3Dot(&(m_vecSkinnedMesh[i].vPosition - vecRoute[0]), &(m_vecSkinnedMesh[i].vPrevPosition - vecRoute[0]));
						if (l <= 0)
						{
							m_vecSkinnedMesh[i].vPrevPosition = vecRoute[0];
						}
					}
					else
					{
						D3DXVec3Normalize(&m_vecSkinnedMesh[i].vDirection, &(m_vecSkinnedMesh[i].vPosition - vecRoute[1]));
						m_vecSkinnedMesh[i].vPosition -= m_vecSkinnedMesh[i].vDirection * m_vecSkinnedMesh[i].fSpeed;
					}
				}
				else
				{
					m_vecSkinnedMesh[i].eMotion = IDLE;
					m_vecSkinnedMesh[i].isRecognize = false;
				}
			}
		}

		D3DXMATRIXA16 matS, matR, matT, mat;
		SetAnimationIndex(i, m_vecSkinnedMesh[i].eMotion);
		D3DXMatrixScaling(&matS, 0.6f, 0.6f, 0.6f);
		D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &m_vecSkinnedMesh[i].vDirection, &D3DXVECTOR3(0, 1, 0));
		D3DXMatrixTranspose(&matR, &matR);
		D3DXMatrixTranslation(&matT, m_vecSkinnedMesh[i].vPosition.x, m_vecSkinnedMesh[i].vPosition.y, m_vecSkinnedMesh[i].vPosition.z);

		mat = matS * matR * matT;

		m_vecSkinnedMesh[i].pSkinnedMesh->UpdateAndRender(&mat);
	}
}

void cClot::SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion)
{
	switch (eMotion)
	{
	case IDLE:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(0);
		break;
	case MOVE:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(1);
		break;
	case SPRINT:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(1);
		break;
	case ATTACK_MELEE:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(2);
		break;
	case DIE:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(7);
		break;
	default:
		break;
	}
}
