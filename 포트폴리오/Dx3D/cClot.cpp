#include "stdafx.h"
#include "cClot.h"
#include "cSkinnedMesh.h"
#include "cDijkstra.h"
#include "cOBB.h"
#include "cFrustum.h"

#define	CLOTHEIGHT D3DXVECTOR3(0, 10, 0)
#define ATTACKDISTANCE	80.f

cClot::cClot()
{
}


cClot::~cClot()
{
	SAFE_RELEASE(m_pBlood);
	SAFE_RELEASE(m_pSprite);
}

void cClot::Setup()
{
	cZombie::SetBlood();

	m_pOBB = new cOBB;
	m_pFrustum = new cFrustum;
	//1
	ST_ZOMBIE stZombie;
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	stZombie.vPosition = D3DXVECTOR3(100, -150, -100);
	stZombie.fAngle = D3DX_PI / 2.0f;
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	stZombie.nHealth = 30;
	stZombie.fSpeed = 3.f;
	m_pOBB->SetupOBJ(stZombie.pSkinnedMesh->GetBoundingBox()->_min*0.5f,
		stZombie.pSkinnedMesh->GetBoundingBox()->_max*0.5f, stZombie.OBBBox);
	m_vecSkinnedMesh.push_back(stZombie);
	//2
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	stZombie.vPosition = D3DXVECTOR3(600, -150, 100);
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
	stZombie.vPosition = D3DXVECTOR3(360, -120, 490);
	stZombie.fAngle = D3DX_PI;
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
	stZombie.vPosition = D3DXVECTOR3(480, -120, 675);
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
	stZombie.vPosition = D3DXVECTOR3(-20, -120, 675);
	stZombie.fAngle = -D3DX_PI / 2.0f;
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
	stZombie.vPosition = D3DXVECTOR3(-20, -120, 470);
	stZombie.fAngle = 0.f;
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
	stZombie.vPosition = D3DXVECTOR3(-400, -120, 300);
	stZombie.fAngle = -D3DX_PI * 2 / 3.f;
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
	stZombie.fAngle = 0.f;
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
	stZombie.vPosition = D3DXVECTOR3(0, -150, 1100);
	stZombie.fAngle = 0.f;
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
	stZombie.vPosition = D3DXVECTOR3(-400, -150, 1500);
	stZombie.fAngle = -D3DX_PI / 4.0f;
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
	stZombie.vPosition = D3DXVECTOR3(110, -150, 1400);
	stZombie.fAngle = D3DX_PI / 4.0f;
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
	stZombie.vPosition = D3DXVECTOR3(1400, -150, 1600);
	stZombie.fAngle = D3DX_PI / 4.0f;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	m_pOBB->SetupOBJ(stZombie.pSkinnedMesh->GetBoundingBox()->_min*0.5f,
		stZombie.pSkinnedMesh->GetBoundingBox()->_max*0.5f, stZombie.OBBBox);
	m_vecSkinnedMesh.push_back(stZombie);
}

void cClot::UpdateAndRender(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, bool* Shot, GUN_NAME ePlayerGun)
{
	cZombie::AttackBlood();

	D3DXVECTOR3 vDest = *vPlayerPos - D3DXVECTOR3(0, 70, 0) - CLOTHEIGHT;

	m_pFrustum->Update();

	for (int i = 0; i < m_vecSkinnedMesh.size(); ++i)
	{
		if (m_vecSkinnedMesh[i].eMotion == DIE)
		{
			m_vecSkinnedMesh[i].vPosition.y -= 1.f;
			m_vecSkinnedMesh[i].fElapsedTime += g_pTimeManager->GetDeltaTime();
			float fActionTime = m_vecSkinnedMesh[i].pSkinnedMesh->AnimationFrame(7);
			if (m_vecSkinnedMesh[i].fElapsedTime > fActionTime)
			{
				m_vecSkinnedMesh.erase(m_vecSkinnedMesh.begin() + i);
				continue;
			}
		}
		else
		{
			if (m_vecSkinnedMesh[i].nHealth <= 0)
			{
				m_vecSkinnedMesh[i].eMotion = DIE;
				m_vecSkinnedMesh[i].pSkinnedMesh->ResetTrackPosition();
				m_vecSkinnedMesh[i].fElapsedTime = 0.f;
			}
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

			//범위?
			D3DXVECTOR3 v = m_vecSkinnedMesh[i].vPosition - vDest;
			float fDistance = D3DXVec3Length(&v);
			D3DXVec3Normalize(&v, &v);

			if (m_vecSkinnedMesh[i].eMotion == IDLE)
			{
				if ((*vPlayerPos).y < 0)
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
			}
			else if (m_vecSkinnedMesh[i].eMotion == MOVE)
			{
				if ((*vPlayerPos).y > 0)
				{
					m_vecSkinnedMesh[i].eMotion = IDLE;
				}
				if (fDistance < ATTACKDISTANCE)
				{
					m_vecSkinnedMesh[i].eMotion = ATTACK_MELEE;
					m_vecSkinnedMesh[i].pSkinnedMesh->ResetTrackPosition();
				}
				else
				{
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
							D3DXVECTOR3 vNode0 = vecRoute[0] - CLOTHEIGHT - D3DXVECTOR3(rand() % 21 - 10, 0, rand() % 21 - 10);
							D3DXVec3Normalize(&m_vecSkinnedMesh[i].vDirection, &(m_vecSkinnedMesh[i].vPosition - vNode0));
							m_vecSkinnedMesh[i].vPosition -= m_vecSkinnedMesh[i].vDirection * m_vecSkinnedMesh[i].fSpeed;

							float l = D3DXVec3Dot(&(m_vecSkinnedMesh[i].vPosition - vNode0), &(m_vecSkinnedMesh[i].vPrevPosition - vNode0));
							if (l <= 0)
							{
								m_vecSkinnedMesh[i].vPrevPosition = vecRoute[0];
							}
						}
						else
						{
							D3DXVECTOR3 vNode1 = vecRoute[1] - CLOTHEIGHT - D3DXVECTOR3(rand() % 21 - 10, 0, rand() % 21 - 10);
							D3DXVec3Normalize(&m_vecSkinnedMesh[i].vDirection, &(m_vecSkinnedMesh[i].vPosition - vNode1));
							m_vecSkinnedMesh[i].vPosition -= m_vecSkinnedMesh[i].vDirection * m_vecSkinnedMesh[i].fSpeed;
						}
					}
					else
					{
						m_vecSkinnedMesh[i].isRecognize = false;
						m_vecSkinnedMesh[i].eMotion = IDLE;
					}
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
				float fActionTime = m_vecSkinnedMesh[i].pSkinnedMesh->AnimationFrame(2);
				if (m_vecSkinnedMesh[i].fElapsedTime > fActionTime)
				{
					m_vecSkinnedMesh[i].eMotion = IDLE;
					m_vecSkinnedMesh[i].pSkinnedMesh->ResetTrackPosition();
					m_vecSkinnedMesh[i].fElapsedTime = 0.f;
				}
			}
			else if (m_vecSkinnedMesh[i].eMotion == DIE)
			{
				m_vecSkinnedMesh[i].fElapsedTime += g_pTimeManager->GetDeltaTime();
				float fActionTime = m_vecSkinnedMesh[i].pSkinnedMesh->AnimationFrame(7);
				if (m_vecSkinnedMesh[i].fElapsedTime > fActionTime)
				{
					m_vecSkinnedMesh[i].fElapsedTime = 0.f;
				}
			}
		}

		D3DXMATRIXA16 matS, matR, matT, mat , matBT, matB ,matBS;
		SetAnimationIndex(i, m_vecSkinnedMesh[i].eMotion);
		D3DXMatrixScaling(&matS, 0.5f, 0.5f, 0.5f);
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
	case HIT_F:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(3);
		break;
	case HIT_B:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(4);
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

bool cClot::PickThePlayer(ST_OBB* sPlayer, OUT D3DXVECTOR3& monDirection)
{
	for (int i = 0; i < m_vecSkinnedMesh.size(); i++)
	{
		if (m_pOBB->IsCollision(sPlayer, &m_vecSkinnedMesh[i].OBBBox))
		{
			monDirection = m_vecSkinnedMesh[i].vDirection;
			return true;
		}
	}
	return false;
}