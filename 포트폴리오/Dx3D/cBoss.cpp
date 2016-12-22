#include "stdafx.h"
#include "cBoss.h"
#include "cSkinnedMesh.h"
#include "cDijkstra.h"


cBoss::cBoss()
	: m_fTime(0.f)
	, m_isDirChange(false)
{
}


cBoss::~cBoss()
{
}

void cBoss::Setup()
{
	m_stBoss.pSkinnedMesh = new cSkinnedMesh("Zombie/BOSS_Patriarch/", "ZED_BOSS_Patriarch.X");
	m_stBoss.vPosition = D3DXVECTOR3(1200, -143, 2200);
	m_stBoss.fAngle = -D3DX_PI;
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, m_stBoss.fAngle);
	D3DXVec3TransformNormal(&m_stBoss.vDirection, &m_stBoss.vPosition, &matR);
	m_stBoss.vDirection.y = 0;
	D3DXVec3Normalize(&m_stBoss.vDirection, &m_stBoss.vDirection);
	m_stBoss.eMotion = IDLE;
	m_stBoss.fSpeed = 3.f;
}

void cBoss::UpdateAndRender(D3DXVECTOR3 * vPlayerPos)
{
	//인식
	if ((*vPlayerPos).y < -50)
	{
		D3DXVECTOR3 v = m_stBoss.vPosition - (*vPlayerPos - D3DXVECTOR3(0, 70, 0));
		float fDistance = D3DXVec3Length(&v);
		D3DXVec3Normalize(&v, &v);

		if (!m_stBoss.isRecognize)
		{
			if (fDistance < 500.f)
			{
				//시야
				float fFov = D3DXVec3Dot(&m_stBoss.vDirection, &v);
				if (fFov <= 1 && fFov > 0.5f)
				{
					m_stBoss.isRecognize = true;
					m_stBoss.eMotion = ENTRANCE;
					m_stBoss.pSkinnedMesh->ResetTrackPosition();
				}
			}
		}
		else
		{
			//D3DXVECTOR3 v0 = m_stBoss.vPosition + fDistance * m_stBoss.vDirection;
			//D3DXVECTOR3 v1 = *vPlayerPos - D3DXVECTOR3(0, 70, 0);
			//D3DXVECTOR3 vPos(0, 0, 0);
			//D3DXVec3Lerp(&vPos, &v0, &v1, D3DXVec3Length(&v0) / fDistance);
			//D3DXVec3Normalize(&m_stBoss.vDirection, &(m_stBoss.vPosition - vPos));

			switch (m_stBoss.eMotion)
			{
			case ENTRANCE:
			{
				m_fTime += g_pTimeManager->GetDeltaTime();
				if (m_fTime > 6.5f)
				{
					m_stBoss.eMotion = IDLE;
					m_stBoss.pSkinnedMesh->ResetTrackPosition();
					m_fTime = 0.f;
				}
			}
				break;
			case IDLE:
			{
				if (fDistance < 200)
				{
					m_stBoss.eMotion = ATTACK_MELEE;
					m_stBoss.pSkinnedMesh->ResetTrackPosition();
				}
				else if (fDistance < 1000)
				{
					m_stBoss.eMotion = MOVE;
					m_stBoss.pSkinnedMesh->ResetTrackPosition();
				}
				else
				{
					m_stBoss.eMotion = ATTACK_CHARGE;
					m_stBoss.pSkinnedMesh->ResetTrackPosition();
					D3DXVec3Normalize(&m_stBoss.vDirection, &(m_stBoss.vPosition - (*vPlayerPos - D3DXVECTOR3(0, 70, 0))));
				}
			}
				break;
			case MOVE:
			{
				D3DXVec3Normalize(&m_stBoss.vDirection, &(m_stBoss.vPosition - (*vPlayerPos - D3DXVECTOR3(0, 70, 0))));
				m_stBoss.vPosition -= m_stBoss.vDirection * 3.f;
			}
				break;
			case ATTACK_CHARGE:
			{
				m_fTime += g_pTimeManager->GetDeltaTime();

				m_stBoss.vPosition -= m_stBoss.vDirection * 10;

				if (m_fTime > 3.f)
				{
					m_stBoss.eMotion = IDLE;
					m_stBoss.pSkinnedMesh->ResetTrackPosition();
					m_fTime = 0.f;
				}
			}
				break;
			case ATTACK_MELEE:
			{
				m_fTime += g_pTimeManager->GetDeltaTime();
				float fActionTime = m_stBoss.pSkinnedMesh->AnimationFrame(2);
				if (m_fTime > fActionTime)
				{
					m_stBoss.eMotion = IDLE;
					m_stBoss.pSkinnedMesh->ResetTrackPosition();
					m_fTime = 0.f;
				}
			}
				break;
			default:
				break;
			}
		}
	}
	else
		m_stBoss.isRecognize = false;

	D3DXMATRIXA16 matS, matR, matT, mat;
	SetAnimationIndex(0, m_stBoss.eMotion);
	D3DXMatrixScaling(&matS, 0.6f, 0.6f, 0.6f);
	D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &m_stBoss.vDirection, &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&matR, &matR);
	D3DXMatrixTranslation(&matT, m_stBoss.vPosition.x, m_stBoss.vPosition.y, m_stBoss.vPosition.z);

	mat = matS * matR * matT;

	m_stBoss.pSkinnedMesh->UpdateAndRender(&mat);
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
	case SPRINT:
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

bool cBoss::PickTheBullet(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir)
{
	return true;
}