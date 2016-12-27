#include "stdafx.h"
#include "cBoss.h"
#include "cSkinnedMesh.h"
#include "cDijkstra.h"
#include "cOBB.h"
#include "cFrustum.h"


cBoss::cBoss()
{
}


cBoss::~cBoss()
{
	SAFE_RELEASE(m_pBlood);
	SAFE_RELEASE(m_pSprite);
}

void cBoss::Setup()
{
	m_pOBB = new cOBB;
	m_pFrustum = new cFrustum;

	m_stBoss.pSkinnedMesh = new cSkinnedMesh("Zombie/BOSS_Patriarch/", "ZED_BOSS_Patriarch.X");
	m_stBoss.vPosition = D3DXVECTOR3(2000, -143, 2200);
	m_stBoss.fAngle = 0.f;
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, m_stBoss.fAngle);
	D3DXVec3TransformNormal(&m_stBoss.vDirection, &m_stBoss.vPosition, &matR);
	m_stBoss.vDirection.y = 0;
	D3DXVec3Normalize(&m_stBoss.vDirection, &m_stBoss.vDirection);
	m_stBoss.eMotion = IDLE;
	m_stBoss.fSpeed = 3.f;
}

void cBoss::UpdateAndRender(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, bool Shot)
{
	D3DXVECTOR3 vDest = *vPlayerPos - D3DXVECTOR3(0, 70, 0);

	m_pFrustum->Update();

	if (m_stBoss.eMotion == DIE)
	{
		m_stBoss.vPosition.y -= 1.f;
		m_stBoss.fElapsedTime += g_pTimeManager->GetDeltaTime();
		float fActionTime = m_stBoss.pSkinnedMesh->AnimationFrame(7);
		if (m_stBoss.fElapsedTime > fActionTime)
		{
//			m_vecSkinnedMesh.erase(m_vecSkinnedMesh.begin() + i);
		}
	}
	else
	{
		if (m_stBoss.nHealth < 0)
		{
			m_stBoss.eMotion = DIE;
			m_stBoss.pSkinnedMesh->ResetTrackPosition();
		}
		if (Shot && PickTheBullet(vPlayerPos, vPlayerDir, 0))
		{
			//앞에서 맞나 뒤에서 맞나
			float fAngle = D3DXVec3Dot(vPlayerDir, &m_stBoss.vDirection);
			if (fAngle < 0)
			{
				m_stBoss.eMotion = HIT_B;
				m_stBoss.pSkinnedMesh->ResetTrackPosition();
				m_stBoss.fElapsedTime = 0.f;
			}
			else
			{
				m_stBoss.eMotion = HIT_F;
				m_stBoss.pSkinnedMesh->ResetTrackPosition();
				m_stBoss.fElapsedTime = 0.f;
			}

			m_stBoss.nHealth -= 50;
		}
		//범위?
		D3DXVECTOR3 v = m_stBoss.vPosition - vDest;
		float fDistance = D3DXVec3Length(&v);
		D3DXVec3Normalize(&v, &v);

		if (m_stBoss.eMotion == IDLE)
		{
			if ((*vPlayerPos).y < 0)
			{
				if (fDistance < 1000.f)
				{
					//시야
					float fFov = D3DXVec3Dot(&m_stBoss.vDirection, &v);
					if (fFov <= 1 && fFov > 0.5f)
					{
						float fFov = D3DXVec3Dot(&m_stBoss.vDirection, &v);
						if (1 - fabs(fFov) < EPSILON)
						{
							if (m_stBoss.isRecognize == false)
							{
								m_stBoss.isRecognize = true;
								m_stBoss.eMotion = ENTRANCE;
								m_stBoss.pSkinnedMesh->ResetTrackPosition();
							}
							else
							{
								m_stBoss.eMotion = MOVE;
								m_stBoss.pSkinnedMesh->ResetTrackPosition();
							}
						}
						else
						{
							D3DXVECTOR3 v0 = m_stBoss.vPosition + fDistance * m_stBoss.vDirection;
							D3DXVECTOR3 v1 = vDest;
							D3DXVECTOR3 vPos(0, 0, 0);
							D3DXVec3Lerp(&vPos, &v0, &v1, D3DXVec3Length(&v0) / fDistance);
							D3DXVec3Normalize(&m_stBoss.vDirection, &(m_stBoss.vPosition - vPos));
						}
					}

					if (fDistance < 100.f)
					{
						m_stBoss.eMotion = ATTACK_MELEE;
						m_stBoss.pSkinnedMesh->ResetTrackPosition();
					}
				}
			}
		}
		else if (m_stBoss.eMotion == ENTRANCE)
		{
			m_stBoss.fElapsedTime += g_pTimeManager->GetDeltaTime();
			float fActionTime = m_stBoss.pSkinnedMesh->AnimationFrame(14);
			if (m_stBoss.fElapsedTime > fActionTime)
			{
				m_stBoss.eMotion = ATTACK_CHARGE;
				m_stBoss.pSkinnedMesh->ResetTrackPosition();
				m_stBoss.vPrevPosition = *vPlayerPos - D3DXVECTOR3(0, 70, 0);
				m_stBoss.fElapsedTime = 0.f;
			}
		}
		else if (m_stBoss.eMotion == MOVE)
		{
			if ((*vPlayerPos).y > 0)
			{
				m_stBoss.eMotion = IDLE;
			}
			if (fDistance < 100.f)
			{
				m_stBoss.eMotion = ATTACK_MELEE;
				m_stBoss.pSkinnedMesh->ResetTrackPosition();
			}
			std::vector<D3DXVECTOR3> vecRoute = m_pDijkstra->GetRoute(&m_stBoss.vPosition, &vDest);

			if (vecRoute.size() < 3)
			{
				D3DXVec3Normalize(&m_stBoss.vDirection, &(m_stBoss.vPosition - vDest));
				m_stBoss.vPosition -= m_stBoss.vDirection * m_stBoss.fSpeed;
			}
			else if (vecRoute.size() < 6)
			{
				if (m_stBoss.vPrevPosition != vecRoute[0])
				{
					D3DXVec3Normalize(&m_stBoss.vDirection, &(m_stBoss.vPosition - (vecRoute[0])));
					m_stBoss.vPosition -= m_stBoss.vDirection * m_stBoss.fSpeed;

					float l = D3DXVec3Dot(&(m_stBoss.vPosition - (vecRoute[0])), &(m_stBoss.vPrevPosition - (vecRoute[0])));
					if (l <= 0)
					{
						m_stBoss.vPrevPosition = vecRoute[0];
					}
				}
				else
				{
					D3DXVec3Normalize(&m_stBoss.vDirection, &(m_stBoss.vPosition - (vecRoute[1])));
					m_stBoss.vPosition -= m_stBoss.vDirection * m_stBoss.fSpeed;
				}
			}
			else
			{
				m_stBoss.eMotion = IDLE;
			}
		}
		else if (m_stBoss.eMotion == HIT_F)
		{
			m_stBoss.fElapsedTime += g_pTimeManager->GetDeltaTime();
			float fActionTime = m_stBoss.pSkinnedMesh->AnimationFrame(3);
			if (m_stBoss.fElapsedTime > fActionTime)
			{
				m_stBoss.eMotion = IDLE;
				m_stBoss.pSkinnedMesh->ResetTrackPosition();
				m_stBoss.fElapsedTime = 0.f;
			}
		}
		else if (m_stBoss.eMotion == HIT_B)
		{
			m_stBoss.fElapsedTime += g_pTimeManager->GetDeltaTime();
			float fActionTime = m_stBoss.pSkinnedMesh->AnimationFrame(4);
			if (m_stBoss.fElapsedTime > fActionTime)
			{
				m_stBoss.eMotion = IDLE;
				m_stBoss.pSkinnedMesh->ResetTrackPosition();
				m_stBoss.fElapsedTime = 0.f;
			}
		}
		else if (m_stBoss.eMotion == ATTACK_MELEE)
		{
			m_stBoss.fElapsedTime += g_pTimeManager->GetDeltaTime();
			float fActionTime = m_stBoss.pSkinnedMesh->AnimationFrame(2);
			if (m_stBoss.fElapsedTime > fActionTime)
			{
				m_stBoss.eMotion = IDLE;
				m_stBoss.pSkinnedMesh->ResetTrackPosition();
				m_stBoss.fElapsedTime = 0.f;
			}
		}
		else if (m_stBoss.eMotion == ATTACK_CHARGE)
		{
			m_stBoss.fElapsedTime += g_pTimeManager->GetDeltaTime();
			float fActionTime = m_stBoss.pSkinnedMesh->AnimationFrame(6);
			if (m_stBoss.fElapsedTime > fActionTime)
			{
				m_stBoss.eMotion = IDLE;
				m_stBoss.pSkinnedMesh->ResetTrackPosition();
				m_stBoss.fElapsedTime = 0.f;
			}
			//
			D3DXVec3Normalize(&m_stBoss.vDirection, &(m_stBoss.vPosition - m_stBoss.vPrevPosition));
			m_stBoss.vPosition -= m_stBoss.vDirection * (m_stBoss.fSpeed + 3.f);
		}
		else if (m_stBoss.eMotion == DIE)
		{
			m_stBoss.fElapsedTime += g_pTimeManager->GetDeltaTime();
			float fActionTime = m_stBoss.pSkinnedMesh->AnimationFrame(7);
			if (m_stBoss.fElapsedTime > fActionTime)
			{
				//			m_stBoss.fElapsedTime = 0.f;
			}
		}
	}

	D3DXMATRIXA16 matS, matR, matT, mat, matBT, matB, matBS;
	SetAnimationIndex(0, m_stBoss.eMotion);
	D3DXMatrixScaling(&matS, 0.5f, 0.5f, 0.5f);
	D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &m_stBoss.vDirection, &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&matR, &matR);
	D3DXMatrixTranslation(&matT, m_stBoss.vPosition.x, m_stBoss.vPosition.y, m_stBoss.vPosition.z);

	mat = matS * matR * matT;

	if (m_pFrustum->IsIn(m_stBoss.pSkinnedMesh->GetBoundingSphere()))
		m_stBoss.pSkinnedMesh->UpdateAndRender(&mat);
	//
	D3DXMatrixScaling(&matBS, 0.6f, 0.8f, 0.6f);
	D3DXMatrixTranslation(&matBT, m_stBoss.vPosition.x, m_stBoss.vPosition.y + 30.f, m_stBoss.vPosition.z);
	matB = matBS * matR *matBT;
	m_stBoss.matWTM = matB;
	m_pOBB->Update(&matB, m_stBoss.OBBBox);
	m_pOBB->DebugRender(&m_stBoss.OBBBox, D3DCOLOR_XRGB(255, 0, 255));
	
}

void cBoss::SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion)
{
	switch (eMotion)
	{
	case IDLE:
		m_stBoss.pSkinnedMesh->SetNomalAnimationIndex(0);
		break;
	case MOVE:
		m_stBoss.pSkinnedMesh->SetNomalAnimationIndex(1);
		break;
	case ATTACK_MELEE:
		m_stBoss.pSkinnedMesh->SetNomalAnimationIndex(2);
		break;
	case ATTACK_CHARGE:
		m_stBoss.pSkinnedMesh->SetNomalAnimationIndex(6);
		break;
	case ENTRANCE:
		m_stBoss.pSkinnedMesh->SetNomalAnimationIndex(14);
		break;
	case DIE:
		m_stBoss.pSkinnedMesh->SetNomalAnimationIndex(7);
		break;
	default:
		break;
	}
}

bool cBoss::PickTheBullet(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, int nZombieIndex)
{
	if (m_pOBB->GetFaceBoxIntersect(&m_stBoss.OBBBox, vPlayerPos, vPlayerDir, &m_stBoss.matWTM))
	{
		return true;
	}

	return false;
}