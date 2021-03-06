#include "StdAfx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCrtController.h"
#include "cPyramid.h"
#include "cObjMap.h"
#include "cRay.h"
#include "cMtlTex.h"
#include "cObjLoader.h"
#include "cAllocateHierarchy.h"
//#include "cSkinnedMesh.h"
#include "cFrustum.h"
#include "cMapXfile.h"
#include "cPlayer.h"
#include "cOBB.h"
#include "cBulletCollision.h"
#include "cCrossHead.h"
#include "cEnemyManager.h"
#include "cSky.h"
#include "cUI.h"
#include "cSoundSetting.h"
#include "cScene.h"
#include "cCredit.h"

#define RADIUS 3.f

cMainGame::cMainGame(void)
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pController(NULL)
	, m_pPyramid(NULL)
	, m_pMap(NULL)
	, m_pObj(NULL)
	, m_pMesh(NULL)
	, m_pMapMesh(NULL)
	, m_pFrustum(NULL)
	//	, m_pSkinnedMesh(NULL)
	, m_pPlayer(NULL)
	, m_pBoundingBox(NULL)
	, m_mouseCheck(false)
	, m_pBulletCollision(NULL)
	, m_fire(false)
	, m_pCrossHead(NULL)
	, m_pEnemyManager(NULL)
	, m_bBlood(NULL)
	, timer(0.f)
	, m_ReboundCamera(0.f)
	, m_fBloodTimer(0.f)
	, m_fTextTimer(0.f)
	, m_bText(false)
	, m_pFont(NULL)
	, OnOff_MOUSE(false)
	, m_pSky(NULL)
	, m_AimDown(false)
	, m_pScene(NULL)
	, m_pCredit(NULL)
	, m_nScene(0)	
{
}

cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pController);
//	for each(auto p in m_vecSkinnedMesh)
//	{
//		SAFE_DELETE(p);
//	}
	SAFE_DELETE(m_pFrustum);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pBulletCollision);
	SAFE_DELETE(m_pCrossHead);
	SAFE_DELETE(m_pEnemyManager);
	SAFE_DELETE(m_pObj);
	SAFE_RELEASE(m_pPyramid);
	SAFE_RELEASE(m_pMap);
	SAFE_DELETE(m_pUI);
	SAFE_DELETE(m_pScene);
	SAFE_DELETE(m_pCredit);

	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMapMesh);
	SAFE_RELEASE(m_pBoundingBox);
	SAFE_RELEASE(m_pFont);
	for each (auto p in m_vecMtlTex)
	{
		SAFE_RELEASE(p);
	}

	//SAFE_DELETE(m_pSkinnedMesh);

	SAFE_DELETE(m_pSky);

	g_pSkinnedMeshManager->Destroy();
	g_pObjectManager->Destroy();
	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
	g_pSoundManager->release();
}

void cMainGame::Setup()
{
	g_pSoundManager->init();

	cSoundSetting m_SoundSetting;
	m_SoundSetting.Setup();
	
	m_pFrustum = new cFrustum;

	m_pPlayer = new cPlayer;
	m_pPlayer->SetUp();

	m_pController = new cCrtController;
	m_pController->Setup();

	D3DXMATRIXA16 matS, matR, matT, mat;
	D3DXMatrixIdentity(&mat);

	cObjMap* pObjMap = new cObjMap;
	pObjMap->Load("./Map/House14.ptop");
	m_pMap = pObjMap;

	cMapXfile* pPickObj = new cMapXfile;
	pPickObj->PickWeaponLoad();
	m_pObj = pPickObj;

	m_pEnemyManager = new cEnemyManager;
	m_pEnemyManager->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup(30);
		
	m_pBoundingBox = new cObjMap;
	m_pBoundingBox->BoxLoad("./Map/Wall.ptop", test, &mat);
	
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 20;
	fd.Width = 10;
	fd.Weight = FW_NORMAL;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	strcpy_s(fd.FaceName, "HY견고딕");	//글꼴 스타일
	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);

	D3DXVECTOR3 min;
	D3DXVECTOR3 max;
	
	m_pOBB = new cOBB;
	for (int j = 0; j < 8; j++)
	{
		int t = 36 * j;
		min = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
		max = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		for (int i = t; i < 36 + t; i++)
		{
			D3DXVec3Minimize(&min, &min, &test[i]);
			D3DXVec3Maximize(&max, &max, &test[i]);
		}
		m_pOBB->SetupOBJ(min, max, m_stWall[j]);
	}

	m_pBulletCollision = new cBulletCollision;
	//이걸 넣어야하나.. imap을 넣어야하나..
	m_pBulletCollision->SetUp(pObjMap);

	m_pCrossHead = new cCrossHead;

	m_pSky = new cSky;
	m_pSky->SetUp();

	m_pUI = new cUI;
	m_pUI->SetUp();

	D3DXMatrixScaling(&matS, 0.1f, 1.0f, 0.1f);
	D3DXMatrixRotationX(&matR, D3DX_PI / 2.0f);
	D3DXMatrixTranslation(&matT, 0, 0, 0.5f);
	mat = matS * matR * matT;
	m_pPyramid = new cPyramid;
	m_pPyramid->Setup(D3DCOLOR_XRGB(255, 255, 255), &mat);

	ZeroMemory(&m_stMtlNormal, sizeof(D3DMATERIAL9));
	m_stMtlNormal.Ambient = m_stMtlNormal.Diffuse = m_stMtlNormal.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	ZeroMemory(&m_stMtlPicked, sizeof(D3DMATERIAL9));
	m_stMtlPicked.Ambient = m_stMtlPicked.Diffuse = m_stMtlPicked.Specular = D3DXCOLOR(0.8f, 0.0f, 0.0f, 1.0f);

	SetLight();

	GetClientRect(g_hWnd, &m_Clientrc);
	POINT pos = { 0, 0 };
	ClientToScreen(g_hWnd, &pos);
	RECT temp = { pos.x, pos.y, pos.x + (m_Clientrc.right - m_Clientrc.left), pos.y + (m_Clientrc.bottom - m_Clientrc.top) };
	m_Clientrc = temp;

	m_pScene = new cScene;
	m_pScene->Setup();

	m_pCredit = new cCredit;
	m_pCredit->Setup();

	SetCursorPos((m_Clientrc.right - m_Clientrc.left) / 2.f, (m_Clientrc.bottom - m_Clientrc.top) / 2.f);
	ClipCursor(&m_Clientrc);	//마우스 가두기

	ShowCursor(m_mouseCheck);	//마우스 숨기기
}

void cMainGame::Update()
{
	g_pSoundManager->update();

	if (m_nScene == 0)
	{
		int isStart = 0;
		m_pScene->Update(&isStart);
		if (isStart == 1)
		{
			m_nScene = 1;
		}
		else if (isStart == 2)
		{
			m_nScene = 3;
		}
	}
	else if (m_nScene == 1)
	{
		if (!OnOff_MOUSE) SetCursorPos(m_Clientrc.left + (m_Clientrc.right - m_Clientrc.left) / 2.f, m_Clientrc.top + (m_Clientrc.bottom - m_Clientrc.top) / 2.f);

	/*bool Shot = false;
	if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		if (Shot)	Shot = false;
		else Shot = true;
	}*/
	if (g_pKeyManager->isOnceKeyDown(VK_F2))
	{
		OnOff_MOUSE = !OnOff_MOUSE;
	}
	g_pTimeManager->Update();

	if (m_pController)
	{
			D3DXVECTOR3 monLocation(0, 0, 0);
		if (m_pEnemyManager->PickThePlayer(m_pPlayer->GetPlayerBox(), monLocation))
		{
			m_pController->Update(m_pMap, &monLocation);
		}
		else
		{
			m_pController->Update(m_pMap);
		}
	}
	if (m_pPlayer)
		m_pPlayer->Update(m_pController->GetWorldTM());


	if (!m_AimDown)
	{
		// false일때 그 높이를 저장받고 풀리면 다시 위치로
		m_ReboundCamera = m_pController->m_fAngleX;
	}
	if (m_pCamera)
		m_pCamera->Update(m_pController->GetPosition(), &m_pController->GetDirection());

	if (m_pFrustum)
	{
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
			//	m_pFrustum->Update();
		}
	}


	if (m_pOBB->IsCollision(m_pPlayer->GetPlayerBox(), &m_pObj->GetBoundingBox()[3]))
	{
		for (int i = 0; i < 3; i++)
			{
			if (m_pOBB->GetFaceBoxIntersect(&m_pObj->GetBoundingBox()[i], m_pController->GetPosition(), &m_pController->GetDirection(), &m_pObj->GetBBWTM()[i]))
			{
				if (i == 0)
					m_pObj->SetShotgunOutLine(0.3f);

				else if (i == 1)
					m_pObj->SetBullpupOutLine(0.3f);

				else if (i == 2)
					m_pObj->SetHealOutLine(0.3f);

				if (g_pKeyManager->isOnceKeyDown('E'))
				{
					if (i == 0)
					{
						m_pPlayer->SetPlayerGun(SHOT);

						if (!g_pSoundManager->isPlaySound("Shotgun_Pickup"))
							g_pSoundManager->play("Shotgun_Pickup", 0.2f);
					}
					else if (i == 1)
					{
						m_pPlayer->SetPlayerGun(BUSTER);

						if (!g_pSoundManager->isPlaySound("Bullpup_Pickup"))
							g_pSoundManager->play("Bullpup_Pickup", 0.2f);
					}
					else if (i == 2)
					{
						m_pPlayer->SetPlayerGun(HEAL);

						if (!g_pSoundManager->isPlaySound("Heal_Pickup"))
							g_pSoundManager->play("Heal_Pickup", 0.2f);
					}
				}
			}

			else
			{
				if (i == 0)
					m_pObj->SetShotgunOutLine(-0.2f);

				else if (i == 1)
					m_pObj->SetBullpupOutLine(-0.2f);

				else if (i == 2)
					m_pObj->SetHealOutLine(-0.2f);
		}
	}
		}
	if (g_pKeyManager->isOnceKeyDown(VK_F1))
	{
		if (!m_mouseCheck)
		{
			m_mouseCheck = true;
		}
		else
		{
			m_mouseCheck = false;
		}

		ShowCursor(m_mouseCheck);
	}


	if (m_pPlayer->GetPlayerGun() == BUSTER)
	{
		if (m_pPlayer->GetBullet() > 0)
		{
			if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
			{
				//이거 활성화 하면 총알튀듯이 된다.
				if (!m_pPlayer->GetZoomIn())m_pController->m_fAngleX -= 0.005f;
				//timer가 너무많으니 더 추가해주자 !!
				timer += g_pTimeManager->GetDeltaTime();
				if (timer >= 0.1f)
				{
					if (g_pSoundManager->isPlaySound("Bullpup_Fire"))
						g_pSoundManager->stop("Bullpup_Fire");

					if (!g_pSoundManager->isPlaySound("Bullpup_Fire"))
						g_pSoundManager->play("Bullpup_Fire", 0.1f);

					m_pPlayer->SetAni(1);
					timer = 0.f;
					m_fire = true;
					m_AimDown = true;
					//여기일때만 몬스터 판정 트루
					m_pPlayer->fireBullet();
				}
			}
		}
	}
	else
	{
		if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
		{
			if (m_pPlayer->GetPlayerGun() == SHOT)
			{
				if (g_pSoundManager->isPlaySound("Shotgun_Fire"))
					g_pSoundManager->stop("Shotgun_Fire");

				if (!g_pSoundManager->isPlaySound("Shotgun_Fire"))
					g_pSoundManager->play("Shotgun_Fire", 0.1f);
			}

			else if (m_pPlayer->GetPlayerGun() == HANDGUN)
			{
				if (g_pSoundManager->isPlaySound("9mm_Fire"))
					g_pSoundManager->stop("9mm_Fire");

				if (!g_pSoundManager->isPlaySound("9mm_Fire"))
					g_pSoundManager->play("9mm_Fire", 0.1f);
			}

			else if (m_pPlayer->GetPlayerGun() == KNIFE)
			{
				if (g_pSoundManager->isPlaySound("Knife_Fire"))
					g_pSoundManager->stop("Knife_Fire");

				if (!g_pSoundManager->isPlaySound("Knife_Fire"))
					g_pSoundManager->play("Knife_Fire", 0.1f);
			}

			else if (m_pPlayer->GetPlayerGun() == HEAL)
			{
				if (g_pSoundManager->isPlaySound("Heal_Self"))
					g_pSoundManager->stop("Heal_Self");

				if (!g_pSoundManager->isPlaySound("Heal_Self"))
					g_pSoundManager->play("Heal_Self", 0.3f);
			}

			matView = *m_pCamera->GetViewMatrix();
			//이거 활성화 하면 총알튀듯이 된다.
			m_pController->m_fAngleX -= 0.010f;

			m_pPlayer->SetAni(1);
			if (m_pPlayer->GetPlayerGun() == HANDGUN || m_pPlayer->GetPlayerGun() == SHOT)
			{
					if (m_pPlayer->GetBullet() > 0)	m_pPlayer->fireBullet();
				else m_pPlayer->Reload();
			}
			m_AimDown = true;
			m_fire = true;
		}
	}
	if (g_pKeyManager->isOnceKeyUp(VK_LBUTTON))
	{
		//이걸 총발사 시간과 연관을 지으면 그럴싸하겠다....
		m_fire = false;
		//m_pPlayer->SetAni(0);
		m_AimDown = false;
		m_pController->m_fAngleX = m_ReboundCamera;
	}


	if (!g_pSoundManager->isPlaySound("테스트"))
		g_pSoundManager->play("테스트", 0.5f);
	if (g_pKeyManager->isOnceKeyUp('F'))
	{
		m_pBulletCollision->Settest(true);
	}
	if (g_pKeyManager->isOnceKeyUp('G'))
	{
		m_pBulletCollision->Settest(false);
	}
	//====감도==================================
	float temp = m_pController->GetSensitivity();
	if (g_pKeyManager->isOnceKeyDown(VK_OEM_4))
	{
		m_bText = true;
			if (temp < 1.9)
		temp += 0.05;
		m_pController->SetSensitivity(temp);
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_OEM_6))
	{
		m_bText = true;
			if (temp > 0.1)	temp -= 0.05;
		m_pController->SetSensitivity(temp);
	}

	m_pBulletCollision->PickCenter(m_pController);
	}
	else if (m_nScene == 2)
	{
		m_pCredit->Update();
	}
	if (!g_pSoundManager->isPlaySound("사운드테스트"))
		g_pSoundManager->play("사운드테스트", 0.5f);

	//BGM===============
	if (!g_pSoundManager->isPlaySound("BGM"))
		g_pSoundManager->play("BGM", 0.009f);

	g_pAutoReleasePool->Drain();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0),
		//D3DCOLOR_XRGB(0, 0, 255),
		1.0f, 0);

	g_pD3DDevice->BeginScene();
	
	// 그림을 그린다.
	if (m_nScene == 0)
	{
		if (m_pScene)
			m_pScene->Render();
	}
	else if (m_nScene == 1)
	{
	m_pGrid->Render();
		D3DXMATRIXA16 matI, matT, matS, matPosition;
	D3DXMatrixIdentity(&matI);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixScaling(&matS, 0.3, 0.5, 0.3);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

		bool bossDie = false;
	if (m_pEnemyManager)
	{
			bossDie = m_pEnemyManager->UpdateAndRender(m_pController->GetPosition(), &m_pController->GetDirection(), &m_fire, m_pPlayer->GetPlayerGun());
		m_pEnemyManager->RenderEffect(&m_pController->GetRotation());
	}

		if (bossDie == false)
		{
			if (m_pPlayer)
				m_pPlayer->Render();
		}
		else
		{
			if (m_pEnemyManager->GetIsBossDead() == true)
			{
				m_nScene = 2;
			}
		}

	if (m_pMap)
	{

		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		std::vector<ST_PNT_VERTEX> testMap;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		m_pMap->Render(
			&D3DXVECTOR4(*m_pController->GetPosition(), 1.f),
			&D3DXVECTOR4(m_pController->GetDirection(), 1.f),
			&D3DXVECTOR4(m_pBulletCollision->GetCenterPosition(), 1.f),
			100.f, &D3DXVECTOR4(*m_pController->GetPosition(), 1.f));
	}

	if (m_bText)
	{
		m_fTextTimer += g_pTimeManager->GetDeltaTime();
		if (m_fTextTimer < 0.5f)
			{
			RECT rc;
			GetClientRect(g_hWnd, &rc);
			char s[80];
				float Sensitivity = 20.f - m_pController->GetSensitivity() * 10;
			sprintf_s(s, sizeof(s), "\n\n\n감도 : %0.1f", Sensitivity);
			std::string temp(s);
			//temp = s;
			m_pFont->DrawTextA(NULL, temp.c_str(), temp.length(), &rc,
				DT_CENTER | DT_VCENTER,
				D3DCOLOR_XRGB(255, 255, 255));

		}
		else
		{
			m_bText = false;
			m_fTextTimer = 0.f;
		}
	}

	if (m_pPlayer->GetPlayerGun() != BUSTER)
	{
		m_pCrossHead->Render();
	}

	if (m_pObj)
	{
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		m_pObj->Render(
			&D3DXVECTOR4(*m_pController->GetPosition(), 1.f),
			&D3DXVECTOR4(m_pController->GetDirection(), 1.f));
		m_pObj->Render();
	}


	//m_pBulletCollision->Render(m_pMap, m_pController);
		m_pSky->Render();

	m_pUI->HP_Render();
	m_pUI->Wepon_Render(m_pPlayer->GetPlayerGun());
	if (m_pPlayer->GetPlayerGun() != KNIFE)
		m_pUI->Bullet_Render(m_pPlayer->GetBullet(), m_pPlayer->GetMaxBullet());
	}
	else if (m_nScene == 2)
	{
		m_pCredit->Render();
	}
	

	char szTemp[64];
	sprintf(szTemp, "%f %f %f", 
		m_pController->GetPosition()->x, m_pController->GetPosition()->y, m_pController->GetPosition()->z);
	
	SetWindowText(g_hWnd, szTemp);

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if (m_pController)
	{
		m_pController->WndProc(hWnd, message, wParam, lParam);
	}
	if (m_nScene == 3)
	{
		PostQuitMessage(0);
	}
}

void cMainGame::SetLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = stLight.Diffuse = stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Direction = D3DXVECTOR3( 1,-1, 1);
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}
