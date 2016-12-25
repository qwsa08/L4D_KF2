#include "stdafx.h"
#include "cClot.h"
#include "cSkinnedMesh.h"
#include "cDijkstra.h"
#include "cOBB.h"
#include "cFrustum.h"

cClot::cClot()
{
}


cClot::~cClot()
{
	for each(auto p in m_vecSkinnedMesh)
	{
		SAFE_DELETE(p.pSkinnedMesh);
	}
	SAFE_DELETE(m_pDijkstra);
	SAFE_DELETE(m_pOBB);
	SAFE_DELETE(m_pFrustum);
}

void cClot::Setup()
{
	m_pOBB = new cOBB;
	m_pFrustum = new cFrustum;
	//1
	ST_ZOMBIE stZombie;
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	stZombie.vPosition = D3DXVECTOR3(100, -140, -100);
	stZombie.fAngle = D3DX_PI / 2.0f;
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	stZombie.fSpeed = 3.f;
	m_pOBB->SetupOBJ(stZombie.pSkinnedMesh->GetBoundingBox()->_min*0.5f,
		stZombie.pSkinnedMesh->GetBoundingBox()->_max*0.5f, stZombie.OBBBox);
	m_vecSkinnedMesh.push_back(stZombie);
	//2
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	stZombie.vPosition = D3DXVECTOR3(600, -140, 100);
	stZombie.fAngle = D3DX_PI / 2.0f;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	m_pOBB->SetupOBJ(stZombie.pSkinnedMesh->GetBoundingBox()->_min*0.5f,
		stZombie.pSkinnedMesh->GetBoundingBox()->_max*0.5f, stZombie.OBBBox);
	m_vecSkinnedMesh.push_back(stZombie);
	//3
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	stZombie.vPosition = D3DXVECTOR3(360, -105, 490);
	stZombie.fAngle = D3DX_PI / 2.0f;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	m_pOBB->SetupOBJ(stZombie.pSkinnedMesh->GetBoundingBox()->_min*0.5f,
		stZombie.pSkinnedMesh->GetBoundingBox()->_max*0.5f, stZombie.OBBBox);
	m_vecSkinnedMesh.push_back(stZombie);
	//4
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	stZombie.vPosition = D3DXVECTOR3(480, -105, 675);
	stZombie.fAngle = D3DX_PI / 2.0f;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	m_pOBB->SetupOBJ(stZombie.pSkinnedMesh->GetBoundingBox()->_min*0.5f,
		stZombie.pSkinnedMesh->GetBoundingBox()->_max*0.5f, stZombie.OBBBox);
	m_vecSkinnedMesh.push_back(stZombie);
	//5
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	stZombie.vPosition = D3DXVECTOR3(-20, -105, 675);
	stZombie.fAngle = D3DX_PI / 2.0f;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	m_pOBB->SetupOBJ(stZombie.pSkinnedMesh->GetBoundingBox()->_min*0.5f,
		stZombie.pSkinnedMesh->GetBoundingBox()->_max*0.5f, stZombie.OBBBox);
	m_vecSkinnedMesh.push_back(stZombie);
	//6
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	stZombie.vPosition = D3DXVECTOR3(-20, -105, 470);
	stZombie.fAngle = D3DX_PI / 2.0f;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	m_pOBB->SetupOBJ(stZombie.pSkinnedMesh->GetBoundingBox()->_min*0.5f,
		stZombie.pSkinnedMesh->GetBoundingBox()->_max*0.5f, stZombie.OBBBox);
	m_vecSkinnedMesh.push_back(stZombie);
	//7
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	stZombie.vPosition = D3DXVECTOR3(-500, -120, 200);
	stZombie.fAngle = D3DX_PI / 2.0f;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	m_pOBB->SetupOBJ(stZombie.pSkinnedMesh->GetBoundingBox()->_min*0.5f,
		stZombie.pSkinnedMesh->GetBoundingBox()->_max*0.5f, stZombie.OBBBox);
	m_vecSkinnedMesh.push_back(stZombie);
	//8
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	stZombie.vPosition = D3DXVECTOR3(-250, -120, 600);
	stZombie.fAngle = D3DX_PI / 2.0f;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	m_pOBB->SetupOBJ(stZombie.pSkinnedMesh->GetBoundingBox()->_min*0.5f,
		stZombie.pSkinnedMesh->GetBoundingBox()->_max*0.5f, stZombie.OBBBox);
	m_vecSkinnedMesh.push_back(stZombie);
	//9
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	stZombie.vPosition = D3DXVECTOR3(0, -120, 1100);
	stZombie.fAngle = D3DX_PI / 2.0f;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	m_pOBB->SetupOBJ(stZombie.pSkinnedMesh->GetBoundingBox()->_min*0.5f,
		stZombie.pSkinnedMesh->GetBoundingBox()->_max*0.5f, stZombie.OBBBox);
	m_vecSkinnedMesh.push_back(stZombie);
	//10
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	stZombie.vPosition = D3DXVECTOR3(-400, -140, 1500);
	stZombie.fAngle = D3DX_PI / 2.0f;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	m_pOBB->SetupOBJ(stZombie.pSkinnedMesh->GetBoundingBox()->_min*0.5f,
		stZombie.pSkinnedMesh->GetBoundingBox()->_max*0.5f, stZombie.OBBBox);
	m_vecSkinnedMesh.push_back(stZombie);
	//11
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	stZombie.vPosition = D3DXVECTOR3(810, -140, 1400);
	stZombie.fAngle = D3DX_PI / 2.0f;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	m_pOBB->SetupOBJ(stZombie.pSkinnedMesh->GetBoundingBox()->_min*0.5f,
		stZombie.pSkinnedMesh->GetBoundingBox()->_max*0.5f, stZombie.OBBBox);
	m_vecSkinnedMesh.push_back(stZombie);
	//12
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	stZombie.vPosition = D3DXVECTOR3(1400, -140, 1600);
	stZombie.fAngle = D3DX_PI / 2.0f;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	m_pOBB->SetupOBJ(stZombie.pSkinnedMesh->GetBoundingBox()->_min*0.5f,
		stZombie.pSkinnedMesh->GetBoundingBox()->_max*0.5f, stZombie.OBBBox);
	m_vecSkinnedMesh.push_back(stZombie);
}

void cClot::UpdateAndRender(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir)
{
	m_pFrustum->Update();

	for (int i = 0; i < m_vecSkinnedMesh.size(); ++i)
	{		
		//범위?
		if ((*vPlayerPos).y < -50)
		{
			D3DXVECTOR3 v = m_vecSkinnedMesh[i].vPosition - (*vPlayerPos - D3DXVECTOR3(0, 70, 0));
			float fDistance = D3DXVec3Length(&v);
			D3DXVec3Normalize(&v, &v);


			if (m_vecSkinnedMesh[i].eMotion == IDLE)
			{
				if (fDistance < 500.f)
				{
					//시야
					float fFov = D3DXVec3Dot(&m_vecSkinnedMesh[i].vDirection, &v);
					if (fFov <= 1 && fFov > 0.5f)
					{
						m_vecSkinnedMesh[i].eMotion = MOVE;
						m_vecSkinnedMesh[i].pSkinnedMesh->ResetTrackPosition();
					}
				}
			}
			else if (m_vecSkinnedMesh[i].eMotion == MOVE)
			{
				if (m_pDijkstra->IsDirect(&m_vecSkinnedMesh[i].vPosition, vPlayerPos))
				{
					if (fDistance < 100.f)
					{
						m_vecSkinnedMesh[i].eMotion = ATTACK_MELEE;
						m_vecSkinnedMesh[i].pSkinnedMesh->ResetTrackPosition();
					}
					else
					{
						float fFov = D3DXVec3Dot(&m_vecSkinnedMesh[i].vDirection, &v);
						if (1 - fabs(fFov) < EPSILON)
						{
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
					/*std::vector<D3DXVECTOR3> vecRoute = m_pDijkstra->GetRoute(&m_vecSkinnedMesh[i].vPosition, vPlayerPos);

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
					}*/
				}
			}
			else if (m_vecSkinnedMesh[i].eMotion == ATTACK_MELEE)
			{
				m_vecSkinnedMesh[i].fElapsedTime += g_pTimeManager->GetDeltaTime();
				float fActinoTime = m_vecSkinnedMesh[i].pSkinnedMesh->AnimationFrame(2);
				if (m_vecSkinnedMesh[i].fElapsedTime > fActinoTime)
				{
					m_vecSkinnedMesh[i].eMotion = MOVE;
					m_vecSkinnedMesh[i].pSkinnedMesh->ResetTrackPosition();
					m_vecSkinnedMesh[i].fElapsedTime = 0.f;
				}
			}			
		}
		else
		{
			m_vecSkinnedMesh[i].eMotion = IDLE;
		}

		D3DXMATRIXA16 matS, matR, matT, mat , matBT, matB ,matBS;
		SetAnimationIndex(i, m_vecSkinnedMesh[i].eMotion);
		D3DXMatrixScaling(&matS, 0.6f, 0.6f, 0.6f);
		D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &m_vecSkinnedMesh[i].vDirection, &D3DXVECTOR3(0, 1, 0));
		D3DXMatrixTranspose(&matR, &matR);
		D3DXMatrixTranslation(&matT, m_vecSkinnedMesh[i].vPosition.x, m_vecSkinnedMesh[i].vPosition.y, m_vecSkinnedMesh[i].vPosition.z);

		mat = matS * matR * matT;
		
		if(m_pFrustum->IsIn(m_vecSkinnedMesh[i].pSkinnedMesh->GetBoundingSphere()))
			m_vecSkinnedMesh[i].pSkinnedMesh->UpdateAndRender(&mat);
		//
		D3DXMatrixScaling(&matBS, 0.6f, 0.8f, 0.6f);
		D3DXMatrixTranslation(&matBT, m_vecSkinnedMesh[i].vPosition.x, m_vecSkinnedMesh[i].vPosition.y+30.f , m_vecSkinnedMesh[i].vPosition.z);
		matB = matBS * matR *matBT;
		m_vecSkinnedMesh[i].matWTM = matB;
		m_pOBB->Update(&matB, m_vecSkinnedMesh[i].OBBBox);
		m_pOBB->DebugRender(&m_vecSkinnedMesh[i].OBBBox, D3DCOLOR_XRGB(255, 0, 255));
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
bool cClot::PickTheBullet(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, int nZombieIndex)
{
	if (m_pOBB->GetFaceBoxIntersect(&m_vecSkinnedMesh[nZombieIndex].OBBBox, vPlayerPos, vPlayerDir, &m_vecSkinnedMesh[nZombieIndex].matWTM))
	{
		return true;
	}

	return false;
}
