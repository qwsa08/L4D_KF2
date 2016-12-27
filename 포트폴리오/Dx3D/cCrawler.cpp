#include "stdafx.h"
#include "cCrawler.h"
#include "cSkinnedMesh.h"
#include "cDijkstra.h"
#include "cOBB.h"
#include "cFrustum.h"

#define CRAWLERHEIGHT	D3DXVECTOR3(0, 0, 0)
#define ATTACKDISTANCE	50.f

cCrawler::cCrawler()
{
}


cCrawler::~cCrawler()
{
	SAFE_RELEASE(m_pBlood);
	SAFE_RELEASE(m_pSprite);
}

void cCrawler::Setup()
{
	cZombie::SetBlood();

	m_pOBB = new cOBB;
	m_pFrustum = new cFrustum;
	//1
	ST_ZOMBIE stZombie;
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Crawler/", "ZED_Crawler.X");
	stZombie.vPosition = D3DXVECTOR3(510, -150, 1200);
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
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Crawler/", "ZED_Crawler.X");
	stZombie.vPosition = D3DXVECTOR3(115, -105, 550);
	stZombie.fAngle = D3DX_PI * 3 / 4.0f;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	stZombie.fSpeed = 3.f;
	m_pOBB->SetupOBJ(stZombie.pSkinnedMesh->GetBoundingBox()->_min*0.5f,
		stZombie.pSkinnedMesh->GetBoundingBox()->_max*0.5f, stZombie.OBBBox);
	m_vecSkinnedMesh.push_back(stZombie);
}

void cCrawler::UpdateAndRender(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, bool* Shot, GUN_NAME ePlayerGun)
{
	cZombie::AttackBlood();

	D3DXVECTOR3 vDest = *vPlayerPos - D3DXVECTOR3(0, 70, 0) - CRAWLERHEIGHT;

	m_pFrustum->Update();

	for (int i = 0; i < m_vecSkinnedMesh.size(); ++i)
	{
		if (m_vecSkinnedMesh[i].eMotion == DIE)
		{
			m_vecSkinnedMesh[i].vPosition.y -= 0.5f;
			m_vecSkinnedMesh[i].fElapsedTime += g_pTimeManager->GetDeltaTime();
			float fActionTime = m_vecSkinnedMesh[i].pSkinnedMesh->AnimationFrame(8);
			if (m_vecSkinnedMesh[i].fElapsedTime > fActionTime)
			{
				m_vecSkinnedMesh.erase(m_vecSkinnedMesh.begin() + i);
				continue;
			}
		}
		else
		{
			if (m_vecSkinnedMesh[i].nHealth < 0)
			{
				m_vecSkinnedMesh[i].eMotion = DIE;
				m_vecSkinnedMesh[i].pSkinnedMesh->ResetTrackPosition();
				m_vecSkinnedMesh[i].fElapsedTime = 0.f;
			}
			//범위?
			if ((*vPlayerPos).y < 0)
			{
				if (*Shot && PickTheBullet(vPlayerPos, vPlayerDir, i))
				{
					//앞에서 맞나 뒤에서 맞나
					float fAngle = D3DXVec3Dot(vPlayerDir, &m_vecSkinnedMesh[i].vDirection);
					if (fAngle < 0)
					{
						m_vecSkinnedMesh[i].eMotion = HIT_B;
						m_vecSkinnedMesh[i].pSkinnedMesh->ResetTrackPosition();
						m_vecSkinnedMesh[i].fElapsedTime = 0.f;
					}
					else
					{
						m_vecSkinnedMesh[i].eMotion = HIT_F;
						m_vecSkinnedMesh[i].pSkinnedMesh->ResetTrackPosition();
						m_vecSkinnedMesh[i].fElapsedTime = 0.f;
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

					m_vecSkinnedMesh[i].nHealth -= damage;
					if (ePlayerGun != SHOT) *Shot = false;
				}

				D3DXVECTOR3 v = m_vecSkinnedMesh[i].vPosition - vDest;
				float fDistance = D3DXVec3Length(&v);
				D3DXVec3Normalize(&v, &v);

				if (m_vecSkinnedMesh[i].eMotion == IDLE)
				{
					if (m_vecSkinnedMesh[i].isRecognize == false)
					{
						if (fDistance < 500.f)
						{
							//시야
							float fFov = D3DXVec3Dot(&m_vecSkinnedMesh[i].vDirection, &v);
							if (fFov <= 1 && fFov > 0.5f)
							{
								float fFov = D3DXVec3Dot(&m_vecSkinnedMesh[i].vDirection, &v);
								if (1 - fabs(fFov) < EPSILON)
								{
									m_vecSkinnedMesh[i].isRecognize = true;
									m_vecSkinnedMesh[i].eMotion = MOVE;
									m_vecSkinnedMesh[i].pSkinnedMesh->ResetTrackPosition();
								}
								else
								{
									D3DXVECTOR3 v0 = m_vecSkinnedMesh[i].vPosition + fDistance * m_vecSkinnedMesh[i].vDirection;
									D3DXVECTOR3 v1 = vDest;
									D3DXVECTOR3 vPos(0, 0, 0);
									D3DXVec3Lerp(&vPos, &v0, &v1, D3DXVec3Length(&v0) / fDistance);
									D3DXVec3Normalize(&m_vecSkinnedMesh[i].vDirection, &(m_vecSkinnedMesh[i].vPosition - vPos));
								}
							}

							if (fDistance < ATTACKDISTANCE)
							{
								m_vecSkinnedMesh[i].eMotion = ATTACK_MELEE;
								m_vecSkinnedMesh[i].pSkinnedMesh->ResetTrackPosition();
							}
						}
					}
					else
					{
						m_vecSkinnedMesh[i].eMotion = MOVE;
						m_vecSkinnedMesh[i].pSkinnedMesh->ResetTrackPosition();
					}
				}
				else if (m_vecSkinnedMesh[i].eMotion == MOVE)
				{
					if (fDistance < ATTACKDISTANCE)
					{
						int nActionNum = rand() % 2;
						if (nActionNum == 0)
							m_vecSkinnedMesh[i].eMotion = ATTACK_MELEE;
						else
						{
							m_vecSkinnedMesh[i].eMotion = ATTACK_LEAP;
							m_vecSkinnedMesh[i].vPrevPosition = *vPlayerPos - D3DXVECTOR3(0, 70, 0);
						}
						m_vecSkinnedMesh[i].pSkinnedMesh->ResetTrackPosition();
					}
					std::vector<D3DXVECTOR3> vecRoute = m_pDijkstra->GetRoute(&m_vecSkinnedMesh[i].vPosition, &vDest);

					if (vecRoute.size() < 3)
					{
						D3DXVec3Normalize(&m_vecSkinnedMesh[i].vDirection, &(m_vecSkinnedMesh[i].vPosition - vDest));
						m_vecSkinnedMesh[i].vPosition -= m_vecSkinnedMesh[i].vDirection * m_vecSkinnedMesh[i].fSpeed;
					}
					else if (vecRoute.size() < 6)
					{
						if (m_vecSkinnedMesh[i].vPrevPosition != vecRoute[0])
						{
							D3DXVec3Normalize(&m_vecSkinnedMesh[i].vDirection, &(m_vecSkinnedMesh[i].vPosition - (vecRoute[0] - CRAWLERHEIGHT)));
							m_vecSkinnedMesh[i].vPosition -= m_vecSkinnedMesh[i].vDirection * m_vecSkinnedMesh[i].fSpeed;

							float l = D3DXVec3Dot(&(m_vecSkinnedMesh[i].vPosition - (vecRoute[0] - CRAWLERHEIGHT)), &(m_vecSkinnedMesh[i].vPrevPosition - (vecRoute[0] - CRAWLERHEIGHT)));
							if (l <= 0)
							{
								m_vecSkinnedMesh[i].vPrevPosition = vecRoute[0];
							}
						}
						else
						{
							D3DXVec3Normalize(&m_vecSkinnedMesh[i].vDirection, &(m_vecSkinnedMesh[i].vPosition - (vecRoute[1] - CRAWLERHEIGHT)));
							m_vecSkinnedMesh[i].vPosition -= m_vecSkinnedMesh[i].vDirection * m_vecSkinnedMesh[i].fSpeed;
						}
					}
					else
					{
						m_vecSkinnedMesh[i].isRecognize = false;
						m_vecSkinnedMesh[i].eMotion = IDLE;
					}
				}
				else if (m_vecSkinnedMesh[i].eMotion == HIT_F)
				{
					m_vecSkinnedMesh[i].fElapsedTime += g_pTimeManager->GetDeltaTime();
					float fActionTime = m_vecSkinnedMesh[i].pSkinnedMesh->AnimationFrame(3);
					if (m_vecSkinnedMesh[i].fElapsedTime > fActionTime)
					{
						m_vecSkinnedMesh[i].eMotion = IDLE;
						m_vecSkinnedMesh[i].pSkinnedMesh->ResetTrackPosition();
						m_vecSkinnedMesh[i].fElapsedTime = 0.f;
					}
				}
				else if (m_vecSkinnedMesh[i].eMotion == HIT_B)
				{
					m_vecSkinnedMesh[i].fElapsedTime += g_pTimeManager->GetDeltaTime();
					float fActionTime = m_vecSkinnedMesh[i].pSkinnedMesh->AnimationFrame(4);
					if (m_vecSkinnedMesh[i].fElapsedTime > fActionTime)
					{
						m_vecSkinnedMesh[i].eMotion = IDLE;
						m_vecSkinnedMesh[i].pSkinnedMesh->ResetTrackPosition();
						m_vecSkinnedMesh[i].fElapsedTime = 0.f;
					}
				}
				else if (m_vecSkinnedMesh[i].eMotion == ATTACK_MELEE)
				{
					if (fDistance < ATTACKDISTANCE)
					{
						m_Blood = true;
					}					
					m_vecSkinnedMesh[i].fElapsedTime += g_pTimeManager->GetDeltaTime();
					float fActionTime = m_vecSkinnedMesh[i].pSkinnedMesh->AnimationFrame(3);
					if (m_vecSkinnedMesh[i].fElapsedTime > fActionTime)
					{
						m_vecSkinnedMesh[i].eMotion = IDLE;
						m_vecSkinnedMesh[i].pSkinnedMesh->ResetTrackPosition();
						m_vecSkinnedMesh[i].fElapsedTime = 0.f;
					}
				}
				else if (m_vecSkinnedMesh[i].eMotion == ATTACK_LEAP)
				{
					if (fDistance < ATTACKDISTANCE)
					{
						m_Blood = true;
					}
					m_vecSkinnedMesh[i].fElapsedTime += g_pTimeManager->GetDeltaTime();
					float fActionTime = m_vecSkinnedMesh[i].pSkinnedMesh->AnimationFrame(2);
					if (m_vecSkinnedMesh[i].fElapsedTime > fActionTime)
					{
						m_vecSkinnedMesh[i].eMotion = IDLE;
						m_vecSkinnedMesh[i].pSkinnedMesh->ResetTrackPosition();
						m_vecSkinnedMesh[i].fElapsedTime = 0.f;
					}
					//
					//			D3DXVec3Normalize(&m_vecSkinnedMesh[i].vDirection, &(m_vecSkinnedMesh[i].vPosition - m_vecSkinnedMesh[i].vPrevPosition));
					//			m_vecSkinnedMesh[i].vPosition -= m_vecSkinnedMesh[i].vDirection * m_vecSkinnedMesh[i].fSpeed;
				}
			}
			else if (m_vecSkinnedMesh[i].eMotion == DIE)
			{
				m_vecSkinnedMesh[i].fElapsedTime += g_pTimeManager->GetDeltaTime();
				float fActionTime = m_vecSkinnedMesh[i].pSkinnedMesh->AnimationFrame(7);
				if (m_vecSkinnedMesh[i].fElapsedTime > fActionTime)
				{
//				m_vecSkinnedMesh[i].fElapsedTime = 0.f;
				}
			}
			else
			{
				m_vecSkinnedMesh[i].eMotion = IDLE;
			}
		}

		D3DXMATRIXA16 matS, matR, matT, mat, matBT, matB, matBS;
		SetAnimationIndex(i, m_vecSkinnedMesh[i].eMotion);
		D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
		D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &m_vecSkinnedMesh[i].vDirection, &D3DXVECTOR3(0, 1, 0));
		D3DXMatrixTranspose(&matR, &matR);
		D3DXMatrixTranslation(&matT, m_vecSkinnedMesh[i].vPosition.x, m_vecSkinnedMesh[i].vPosition.y, m_vecSkinnedMesh[i].vPosition.z);

		mat = matS * matR * matT;

		if (m_pFrustum->IsIn(m_vecSkinnedMesh[i].pSkinnedMesh->GetBoundingSphere()))
			m_vecSkinnedMesh[i].pSkinnedMesh->UpdateAndRender(&mat);
		//
		D3DXMatrixScaling(&matBS, 0.6f, 0.8f, 0.6f);
		D3DXMatrixTranslation(&matBT, m_vecSkinnedMesh[i].vPosition.x, m_vecSkinnedMesh[i].vPosition.y + 30.f, m_vecSkinnedMesh[i].vPosition.z);
		matB = matBS * matR *matBT;
		m_vecSkinnedMesh[i].matWTM = matB;
		m_pOBB->Update(&matB, m_vecSkinnedMesh[i].OBBBox);
		m_pOBB->DebugRender(&m_vecSkinnedMesh[i].OBBBox, D3DCOLOR_XRGB(255, 0, 255));
	}
}

void cCrawler::SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion)
{
	switch (eMotion)
	{
	case IDLE:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(0);
		break;
	case MOVE:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(1);
		break;
	case HIT_F:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(4);
		break;
	case HIT_B:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(5);
		break;
	case ATTACK_MELEE:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(3);
		break;
	case ATTACK_LEAP:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(2);
		break;
	case DIE:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(8);
		break;
	default:
		break;
	}
}

bool cCrawler::PickTheBullet(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, int nZombieIndex)
{
	if (m_pOBB->GetFaceBoxIntersect(&m_vecSkinnedMesh[nZombieIndex].OBBBox, vPlayerPos, vPlayerDir, &m_vecSkinnedMesh[nZombieIndex].matWTM))
	{
		return true;
	}

	return false;
}

bool cCrawler::PickThePlayer(ST_OBB* sPlayer, OUT D3DXVECTOR3& monLocation)
{
	return false;
}