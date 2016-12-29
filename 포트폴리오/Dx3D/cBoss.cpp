#include "stdafx.h"
#include "cBoss.h"
#include "cSkinnedMesh.h"
#include "cDijkstra.h"
#include "cOBB.h"
#include "cFrustum.h"

#define ATTACKDISTANCE	100.f


cBoss::cBoss()
: m_Pick(false)
{
}


cBoss::~cBoss()
{
	SAFE_RELEASE(m_pBlood);
	SAFE_RELEASE(m_pSprite);
}

void cBoss::Setup()
{
	cZombie::SetBlood();

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
	m_pOBB->SetupOBJ(m_stBoss.pSkinnedMesh->GetBoundingBox()->_min*0.5f + D3DXVECTOR3(-50, 0, 0),
		m_stBoss.pSkinnedMesh->GetBoundingBox()->_max*0.5f + D3DXVECTOR3(50, 0, 0), m_stBoss.OBBBox);
	m_stBoss.eMotion = IDLE;
	m_stBoss.nHealth = 300;
	m_stBoss.fSpeed = 3.f;
	m_pOBB->SetupOBJ(m_stBoss.pSkinnedMesh->GetBoundingBox()->_min*0.5f + D3DXVECTOR3(-50, 0, 0),
		m_stBoss.pSkinnedMesh->GetBoundingBox()->_max*0.5f + D3DXVECTOR3(50, 0, 0), m_stBoss.OBBBox);
}

bool cBoss::UpdateAndRender(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, bool* Shot, GUN_NAME ePlayerGun)
{
	if (!m_isDead)
	{
		cZombie::AttackBlood();

		D3DXVECTOR3 vDest = *vPlayerPos - D3DXVECTOR3(0, 70, 0);

		m_pFrustum->Update();

		if (m_stBoss.eMotion == DIE)
		{
			if (!g_pSoundManager->isPlaySound("BOSS_Death"))
				g_pSoundManager->play("BOSS_Death", 0.03f);

			IdleSoundOff();

			D3DXMATRIXA16 matView;
			D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(m_stBoss.vPosition.x - 100, m_stBoss.vPosition.y + 300, m_stBoss.vPosition.z - 100),
				&D3DXVECTOR3(m_stBoss.vPosition.x, m_stBoss.vPosition.y, m_stBoss.vPosition.z),
				&D3DXVECTOR3(0, 1, 0));
			g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
			m_Pick = false;
			m_stBoss.vPosition.y -= 0.5f;
			m_stBoss.fElapsedTime += g_pTimeManager->GetDeltaTime();
			float fActionTime = m_stBoss.pSkinnedMesh->AnimationFrame(12);
			if (m_stBoss.fElapsedTime > fActionTime)
			{
				m_isDead = true;
			}
		}
		else
		{
			if (m_stBoss.nHealth <= 0)
			{
				m_stBoss.eMotion = DIE;
				m_stBoss.pSkinnedMesh->ResetTrackPosition();
			}
			if (*Shot && PickTheBullet(vPlayerPos, vPlayerDir, 0))
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
				int damage = 0;
				switch (ePlayerGun)
				{
				case HANDGUN:
					damage = H_DAMAGE;
					break;
				case BUSTER:
					damage = B_DAMAGE;
					break;
				case KNIFE:
					damage = K_DAMAGE;
					break;
				case SHOT:
					damage = S_DAMAGE;
					break;
				case HEAL:
					*Shot = false;
					break;
				default:
					break;
				}

				m_stBoss.nHealth -= damage;
				if (ePlayerGun != SHOT) *Shot = false;

			}
			//범위?
			D3DXVECTOR3 v = m_stBoss.vPosition - vDest;
			float fDistance = D3DXVec3Length(&v);
			D3DXVec3Normalize(&v, &v);

			if (m_stBoss.eMotion == IDLE)
			{
				if ((*vPlayerPos).y < 0)
				{
					if (m_stBoss.isRecognize == false)
					{
						if (fDistance < 1200.f)
						{
							IdleSoundOn();
						}
						else
						{
							IdleSoundOff();
						}

						if (fDistance < 1000.f)
						{
							//시야
							float fFov = D3DXVec3Dot(&m_stBoss.vDirection, &v);

							if (fFov <= 1 && fFov > 0.5f)
							{
								m_stBoss.isRecognize = true;
								m_stBoss.eMotion = ENTRANCE;
								m_stBoss.pSkinnedMesh->ResetTrackPosition();

								IdleSoundOff();
							}
						}
					}
					else
					{
						if (fDistance < ATTACKDISTANCE)
						{
							m_stBoss.eMotion = ATTACK_MELEE;
							m_stBoss.pSkinnedMesh->ResetTrackPosition();

							IdleSoundOff();
						}

						else if (fDistance < 300.f)
						{
							m_stBoss.eMotion = MOVE;
							m_stBoss.pSkinnedMesh->ResetTrackPosition();

							IdleSoundOff();
						}

						else
						{
							m_stBoss.eMotion = ATTACK_GUN_BLINDLY;
						}

						if (m_stBoss.nHealth < 100)
						{
							m_stBoss.eMotion = BOSS_HEAL;
							m_stBoss.pSkinnedMesh->ResetTrackPosition();

							IdleSoundOff();
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
				StepSoundOn();

				if ((*vPlayerPos).y > 0)
				{
					m_stBoss.eMotion = IDLE;

					StepSoundOff();
				}
				if (fDistance < ATTACKDISTANCE)
				{
					m_stBoss.eMotion = ATTACK_MELEE;
					m_stBoss.pSkinnedMesh->ResetTrackPosition();

					StepSoundOff();
				}
				else
				{
					//총은 언제 쏘게 하지
					if (fDistance > 300.f)
					{
						m_stBoss.eMotion = ATTACK_GUN_BLINDLY;

						StepSoundOff();
					}
					else
					{
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

							StepSoundOff();
						}
					}
				}
			}
			else if (m_stBoss.eMotion == HIT_F)
			{
				if (!g_pSoundManager->isPlaySound("Zombie_Hit2"))
					g_pSoundManager->play("Zombie_Hit2", 0.1f);

				m_stBoss.fElapsedTime += g_pTimeManager->GetDeltaTime();
				float fActionTime = m_stBoss.pSkinnedMesh->AnimationFrame(3);
				m_Pick = true;
				if (m_stBoss.fElapsedTime > fActionTime)
				{
					m_Pick = false;
					m_stBoss.eMotion = IDLE;
					m_stBoss.pSkinnedMesh->ResetTrackPosition();
					m_stBoss.fElapsedTime = 0.f;
				}
			}
			else if (m_stBoss.eMotion == HIT_B)
			{
				if (!g_pSoundManager->isPlaySound("Zombie_Hit2"))
					g_pSoundManager->play("Zombie_Hit2", 0.1f);

				m_stBoss.fElapsedTime += g_pTimeManager->GetDeltaTime();
				float fActionTime = m_stBoss.pSkinnedMesh->AnimationFrame(4);
				m_Pick = true;
				if (m_stBoss.fElapsedTime > fActionTime)
				{
					m_Pick = false;
					m_stBoss.eMotion = IDLE;
					m_stBoss.pSkinnedMesh->ResetTrackPosition();
					m_stBoss.fElapsedTime = 0.f;
				}
			}
			else if (m_stBoss.eMotion == ATTACK_MELEE)
			{
				if (!g_pSoundManager->isPlaySound("BOSS_Attack"))
					g_pSoundManager->play("BOSS_Attack", 0.1f);

				if (fDistance < ATTACKDISTANCE)
				{
					m_Blood = true;
				}
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
				if (!g_pSoundManager->isPlaySound("BOSS_Charge"))
					g_pSoundManager->play("BOSS_Charge", 0.1f);

				m_stBoss.fElapsedTime += g_pTimeManager->GetDeltaTime();
				float fActionTime = m_stBoss.pSkinnedMesh->AnimationFrame(6);

				if (fDistance < ATTACKDISTANCE)
				{
					m_stBoss.eMotion = ATTACK_MELEE;
				}

				if (m_stBoss.fElapsedTime > fActionTime)
				{
					m_stBoss.eMotion = IDLE;
					m_stBoss.pSkinnedMesh->ResetTrackPosition();
					m_stBoss.fElapsedTime = 0.f;
				}
				//
				D3DXVec3Normalize(&m_stBoss.vDirection, &(m_stBoss.vPosition - m_stBoss.vPrevPosition));
				m_stBoss.vPosition -= m_stBoss.vDirection * (m_stBoss.fSpeed + 15.f);
			}
			else if (m_stBoss.eMotion == ATTACK_GUN_BLINDLY)
			{
				if (!g_pSoundManager->isPlaySound("BOSS_Gunfire"))
					g_pSoundManager->play("BOSS_Gunfire", 0.1f);

				D3DXVec3Normalize(&m_stBoss.vDirection, &(m_stBoss.vPosition - (*vPlayerPos - D3DXVECTOR3(0, 70, 0))));
				m_stBoss.fElapsedTime += g_pTimeManager->GetDeltaTime();
				float fActionTime = m_stBoss.pSkinnedMesh->AnimationFrame(5);
				if (m_stBoss.fElapsedTime > fActionTime)
				{
					//if (fDistance < ATTACKDISTANCE)
					//{
					//	m_Blood = true;
					//}
					m_stBoss.eMotion = ATTACK_GUN_RELOAD;
					m_stBoss.pSkinnedMesh->ResetTrackPosition();
					m_stBoss.fElapsedTime = 0.f;

					g_pSoundManager->stop("BOSS_Gunfire");
				}
			}
			else if (m_stBoss.eMotion == ATTACK_GUN_RELOAD)
			{
				m_stBoss.fElapsedTime += g_pTimeManager->GetDeltaTime();
				float fActionTime = m_stBoss.pSkinnedMesh->AnimationFrame(3);
				if (m_stBoss.fElapsedTime > fActionTime)
				{
					m_stBoss.vPrevPosition = *vPlayerPos - D3DXVECTOR3(0, 70, 0);
					m_stBoss.eMotion = ATTACK_CHARGE;
					m_stBoss.pSkinnedMesh->ResetTrackPosition();
					m_stBoss.fElapsedTime = 0.f;
				}
			}
			else if (m_stBoss.eMotion == BOSS_HEAL)
			{
				if (!g_pSoundManager->isPlaySound("BOSS_Heal"))
					g_pSoundManager->play("BOSS_Heal", 0.1f);

				m_stBoss.fElapsedTime += g_pTimeManager->GetDeltaTime();
				float fActionTime = m_stBoss.pSkinnedMesh->AnimationFrame(7);
				if (m_stBoss.fElapsedTime > 100)
				{
					m_stBoss.nHealth += 150;
					m_stBoss.eMotion = IDLE;
					m_stBoss.pSkinnedMesh->ResetTrackPosition();
					m_stBoss.fElapsedTime = 0.f;
				}
			}
			else if (m_stBoss.eMotion == VICTORY)
			{
				if (!g_pSoundManager->isPlaySound("BOSS_Victory"))
					g_pSoundManager->play("BOSS_Victory", 0.1f);

				m_stBoss.fElapsedTime += g_pTimeManager->GetDeltaTime();
				float fActionTime = m_stBoss.pSkinnedMesh->AnimationFrame(13);
				if (m_stBoss.fElapsedTime > fActionTime)
				{
					if (fDistance < ATTACKDISTANCE)
					{
						m_Blood = true;
					}
					m_stBoss.eMotion = IDLE;
					m_stBoss.pSkinnedMesh->ResetTrackPosition();
					m_stBoss.fElapsedTime = 0.f;
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

	if (m_stBoss.eMotion == DIE)
	{
		if (!g_pSoundManager->isPlaySound("BOSS_Death"))
			g_pSoundManager->play("BOSS_Death", 0.1f);

		return true;
	}
	else return false;
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
	case ATTACK_GUN:
		m_stBoss.pSkinnedMesh->SetNomalAnimationIndex(4);
		break;
	case ATTACK_GUN_BLINDLY:
		m_stBoss.pSkinnedMesh->SetNomalAnimationIndex(5);
		break;
	case ATTACK_GUN_RELOAD:
		m_stBoss.pSkinnedMesh->SetNomalAnimationIndex(3);
		break;
	case BOSS_HEAL:
		m_stBoss.pSkinnedMesh->SetNomalAnimationIndex(7);
		break;
	case ENTRANCE:
		m_stBoss.pSkinnedMesh->SetNomalAnimationIndex(14);
		break;
	case VICTORY:
		m_stBoss.pSkinnedMesh->SetNomalAnimationIndex(13);
		break;
	case DIE:
		m_stBoss.pSkinnedMesh->SetNomalAnimationIndex(12);
		break;
	default:
		break;
	}
}

bool cBoss::PickTheBullet(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, int nZombieIndex)
{
	if (m_pOBB->GetMonsterBoxIntersect(&m_stBoss.OBBBox, vPlayerPos, vPlayerDir, &m_stBoss.matWTM))
	{

		return true;
	}

	m_Pick = false;
	return false;
}
bool cBoss::PickThePlayer(ST_OBB* sPlayer, OUT D3DXVECTOR3& monLocation)
{
	return false;
}
bool cBoss::GetZombiePosition()
{
	m_pPosition = m_pOBB->GetPosition();
	return m_Pick;
}
D3DXVECTOR3 cBoss::GetPosition()
{
	return m_pPosition;
}

void cBoss::IdleSoundOn()
{
	if (!g_pSoundManager->isPlaySound("BOSS_Idle"))
		g_pSoundManager->play("BOSS_Idle", 0.06f);
}

void cBoss::IdleSoundOff()
{
	if (g_pSoundManager->isPlaySound("BOSS_Idle"))
		g_pSoundManager->stop("BOSS_Idle");
}

void cBoss::StepSoundOn()
{
	if (!g_pSoundManager->isPlaySound("Boss_Step"))
		g_pSoundManager->play("Boss_Step", 0.06f);
}

void cBoss::StepSoundOff()
{
	if (g_pSoundManager->isPlaySound("Boss_Step"))
		g_pSoundManager->stop("Boss_Step");
}