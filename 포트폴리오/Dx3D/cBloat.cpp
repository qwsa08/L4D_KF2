#include "stdafx.h"
#include "cBloat.h"
#include "cSkinnedMesh.h"
#include "cDijkstra.h"
#include "cOBB.h"
#include "cFrustum.h"

#define BLOATHEIGHT D3DXVECTOR3(0, 0, 0)
#define ATTACKDISTANCE	100.f

cBloat::cBloat()
	: m_pPuke(NULL)
	, m_pSpriteP(NULL)
	, m_Vomit(false)
	, m_fVomitTime(0.f)
	, m_Pick(false)
{
}


cBloat::~cBloat()
{
	SAFE_RELEASE(m_pPuke);
	SAFE_RELEASE(m_pSpriteP);
	SAFE_RELEASE(m_pBlood);
	SAFE_RELEASE(m_pSprite);
}

void cBloat::Setup()
{
	cZombie::SetBlood();

	m_pOBB = new cOBB;
	m_pFrustum = new cFrustum;
	//1
	ST_ZOMBIE stZombie;
	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Bloat/", "ZED_Bloat.X");
	stZombie.vPosition = D3DXVECTOR3(-800, -140, 2200);
	stZombie.fAngle = -D3DX_PI / 4.0f;
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	stZombie.fSpeed = 2.f;
	m_pOBB->SetupOBJ(stZombie.pSkinnedMesh->GetBoundingBox()->_min*0.5f,
		stZombie.pSkinnedMesh->GetBoundingBox()->_max*0.5f, stZombie.OBBBox);
	m_vecSkinnedMesh.push_back(stZombie);

	stZombie.pSkinnedMesh = new cSkinnedMesh("Zombie/Bloat/", "ZED_Bloat.X");
	stZombie.vPosition = D3DXVECTOR3(500, -120, 1000);
	stZombie.fAngle = D3DX_PI / 2.f;
	D3DXMatrixRotationY(&matR, stZombie.fAngle);
	D3DXVec3TransformNormal(&stZombie.vDirection, &stZombie.vPosition, &matR);
	stZombie.vDirection.y = 0;
	D3DXVec3Normalize(&stZombie.vDirection, &stZombie.vDirection);
	stZombie.eMotion = IDLE;
	stZombie.fSpeed = 2.f;
	m_pOBB->SetupOBJ(stZombie.pSkinnedMesh->GetBoundingBox()->_min*0.5f,
		stZombie.pSkinnedMesh->GetBoundingBox()->_max*0.5f, stZombie.OBBBox);
	m_vecSkinnedMesh.push_back(stZombie);

	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"Effect/Bloat_Puke.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 0, 0),
		NULL,
		NULL,
		&m_pPuke);

	GetClientRect(g_hWnd, &m_Rect);
	D3DXCreateSprite(g_pD3DDevice, &m_pSpriteP);
}

void cBloat::UpdateAndRender(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, bool* Shot, GUN_NAME ePlayerGun)
{
	cZombie::AttackBlood();

	if (m_Vomit)
	{
		m_fVomitTime += g_pTimeManager->GetDeltaTime();

		if (m_fVomitTime > 0.5f)
		{
			m_pSpriteP->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
			D3DXMATRIXA16 matS, matW;
			D3DXMatrixIdentity(&matW);
			//D3DXMatrixIdentity(&matS);
			D3DXMatrixScaling(&matS, 2.f, 1.5f, 1.f);
			matW *= matS;
			m_pSpriteP->SetTransform(&matW);
			g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
			g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
			m_pSpriteP->Draw(m_pPuke,
				&m_Rect,
				&D3DXVECTOR3(0, 0, 0),
				&D3DXVECTOR3(45, -60, 0),
				D3DCOLOR_XRGB(255, 255, 255));
			m_pSpriteP->End();
		}
		if (m_fVomitTime > 5.f)
		{
			m_Vomit = false;
			m_fVomitTime = 0.f;
		}
	}
	
	D3DXVECTOR3 vDest = *vPlayerPos - D3DXVECTOR3(0, 70, 0) - BLOATHEIGHT;

	m_pFrustum->Update();

	for (int i = 0; i < m_vecSkinnedMesh.size(); ++i)
	{
		if (m_vecSkinnedMesh[i].eMotion == DIE)
		{
			m_Pick = false;
			m_vecSkinnedMesh[i].vPosition.y -= 1.f;
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
				if(ePlayerGun != SHOT) *Shot = false;
				
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
						if (fDistance < 800.f)
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
					if (m_Vomit)
						m_vecSkinnedMesh[i].eMotion = ATTACK_MELEE;
					else
						m_vecSkinnedMesh[i].eMotion = ATTACK_VOMIT;

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
						D3DXVec3Normalize(&m_vecSkinnedMesh[i].vDirection, &(m_vecSkinnedMesh[i].vPosition - (vecRoute[0] - BLOATHEIGHT)));
						m_vecSkinnedMesh[i].vPosition -= m_vecSkinnedMesh[i].vDirection * m_vecSkinnedMesh[i].fSpeed;

						float l = D3DXVec3Dot(&(m_vecSkinnedMesh[i].vPosition - (vecRoute[0] - BLOATHEIGHT)), &(m_vecSkinnedMesh[i].vPrevPosition - (vecRoute[0] - BLOATHEIGHT)));
						if (l <= 0)
						{
							m_vecSkinnedMesh[i].vPrevPosition = vecRoute[0];
						}
					}
					else
					{
						D3DXVec3Normalize(&m_vecSkinnedMesh[i].vDirection, &(m_vecSkinnedMesh[i].vPosition - (vecRoute[1] - BLOATHEIGHT)));
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
				m_Pick = true;
				m_vecSkinnedMesh[i].fElapsedTime += g_pTimeManager->GetDeltaTime();
				float fActionTime = m_vecSkinnedMesh[i].pSkinnedMesh->AnimationFrame(4);
				if (m_vecSkinnedMesh[i].fElapsedTime > 1.f) m_Pick = false;
				if (m_vecSkinnedMesh[i].fElapsedTime > fActionTime)
				{
					m_Pick = false;
					m_vecSkinnedMesh[i].eMotion = IDLE;
					m_vecSkinnedMesh[i].pSkinnedMesh->ResetTrackPosition();
					m_vecSkinnedMesh[i].fElapsedTime = 0.f;
				}
			}
			else if (m_vecSkinnedMesh[i].eMotion == HIT_B)
			{
				m_Pick = true;
				m_vecSkinnedMesh[i].fElapsedTime += g_pTimeManager->GetDeltaTime();
				float fActionTime = m_vecSkinnedMesh[i].pSkinnedMesh->AnimationFrame(5);
				if (m_vecSkinnedMesh[i].fElapsedTime > 1.f) m_Pick = false;
				if (m_vecSkinnedMesh[i].fElapsedTime > fActionTime)
				{
					m_Pick = false;
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
			else if (m_vecSkinnedMesh[i].eMotion == ATTACK_VOMIT)
			{
				m_Vomit = true;
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
				float fActionTime = m_vecSkinnedMesh[i].pSkinnedMesh->AnimationFrame(8);
				if (m_vecSkinnedMesh[i].fElapsedTime > fActionTime)
				{
					//				m_vecSkinnedMesh[i].fElapsedTime = 0.f;
				}
			}
		}

		D3DXMATRIXA16 matS, matR, matT, mat, matBT, matB, matBS;
		SetAnimationIndex(i, m_vecSkinnedMesh[i].eMotion);
		D3DXMatrixScaling(&matS, 0.5f, 0.5f, 0.5f);
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

void cBloat::SetAnimationIndex(int nIndex, ZOMBIE_MOTION eMotion)
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
	case ATTACK_VOMIT:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(2);
		break;
	case DIE:
		m_vecSkinnedMesh[nIndex].pSkinnedMesh->SetNomalAnimationIndex(8);
		break;
	default:
		break;
	}
}

bool cBloat::PickTheBullet(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vPlayerDir, int nZombieIndex)
{
	if (m_pOBB->GetMonsterBoxIntersect(&m_vecSkinnedMesh[nZombieIndex].OBBBox, vPlayerPos, vPlayerDir, &m_vecSkinnedMesh[nZombieIndex].matWTM))
	{
		return true;
	}
	m_Pick = false;
	return false;
}
bool cBloat::PickThePlayer(ST_OBB* sPlayer, OUT D3DXVECTOR3& monLocation)
{
	return false;
}

bool cBloat::GetZombiePosition()
{
	m_pPosition = m_pOBB->GetPosition();
	return m_Pick;
}
D3DXVECTOR3 cBloat::GetPosition()
{
	return m_pPosition;
}