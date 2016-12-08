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
#include "cZombie.h"
#include "cBloat.h"
#include "cOBB.h"
#include "cBulletCollision.h"
#include "cCrossHead.h"
#define RADIUS 3.f

cMainGame::cMainGame(void)
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pController(NULL)
	, m_pPyramid(NULL)
	, m_pMap(NULL)
	, m_pMesh(NULL)
	, m_pMapMesh(NULL)
	, m_pFrustum(NULL)
//	, m_pSkinnedMesh(NULL)
	, m_pPlayer(NULL)
	, m_pBoundingBox(NULL)
	, m_pBloat(NULL)
	, m_mouseCheck(false)
	, m_pBulletCollision(NULL)
	, m_fire(false)
	, m_pCrossHead(NULL)
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
	SAFE_DELETE(m_pBloat);
	SAFE_DELETE(m_pBulletCollision);
	SAFE_DELETE(m_pCrossHead);

	SAFE_RELEASE(m_pPyramid);
	SAFE_RELEASE(m_pMap);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMapMesh);
	SAFE_RELEASE(m_pBoundingBox);
	for each (auto p in m_vecMtlTex)
	{
		SAFE_RELEASE(p);
	}

	//SAFE_DELETE(m_pSkinnedMesh);


	g_pSkinnedMeshManager->Destroy();
	g_pObjectManager->Destroy();
	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	m_pFrustum = new cFrustum;

	m_pPlayer = new cPlayer;
	m_pPlayer->SetUp();

	m_pBloat = new cBloat;
	m_pBloat->Setup();

	D3DXMATRIXA16 matS, matR, matT, mat;
	D3DXMatrixIdentity(&mat);

	cObjMap* pObjMap = new cObjMap;
	pObjMap->Load("./Map/House14.ptop",&mat);
	m_pMap = pObjMap;

	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pController = new cCrtController;
	m_pController->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup(30);
		
	m_pBoundingBox = new cObjMap;
	m_pBoundingBox->BoxLoad("./Map/Wall.ptop", test, &mat);
	
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
		m_pOBB->Setup(min, max, m_stWall[j]);
	}
	
	

	m_pBulletCollision = new cBulletCollision;
	//이걸 넣어야하나.. imap을 넣어야하나..
	m_pBulletCollision->SetUp(pObjMap);

	m_pCrossHead = new cCrossHead;


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

	RECT rc;
	GetWindowRect(g_hWnd, &rc);
	//GetClientRect(g_hWnd, &rc);
	rc.left += 10;
	rc.right -= 10;
	rc.top += 55;
	rc.bottom -= 10;
	SetCursorPos((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2);	//마우스 시작좌표 고정
	ClipCursor(&rc);	//마우스 가두기
	ShowCursor(m_mouseCheck);	//마우스 숨기기
}

void cMainGame::Update()
{
	g_pTimeManager->Update();
	
	if(m_pController)
		m_pController->Update(m_pMap);

	if (m_pPlayer)
		m_pPlayer->Update(m_pController->GetWorldTM());

	if (m_pCamera)
		m_pCamera->Update(m_pController->GetPosition(), &m_pController->GetDirection());

	if(m_pFrustum)
	{
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
		//	m_pFrustum->Update();
		}
	}

	
	for (int i = 0; i < 8;i++)
	{
		if (m_pOBB->IsCollision(m_pPlayer->GetPlayerBox(), &m_stWall[i]))
		{
			//m_pController->SetCrush(true);
			m_cPaint = D3DCOLOR_XRGB(255, 255, 255);
		}
		else
		{
			m_cPaint = D3DCOLOR_XRGB(0, 0, 0);
		}
	}
	
	if (GetKeyState(VK_SPACE) & 0x8000)
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

	
	if (GetKeyState(VK_LBUTTON) & 0x8000)
	{
		if (m_pBulletCollision->PickBullet(m_pController))
		{
			m_fire = true;
		}
	}

	g_pAutoReleasePool->Drain();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		//D3DCOLOR_XRGB(0, 0, 255),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	// 그림을 그린다.
	m_pGrid->Render();
	
	D3DXMATRIXA16 matI, matT ,matS , matPosition;
	D3DXMatrixIdentity(&matI);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixScaling(&matS, 0.3, 0.5, 0.3);
	
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	//for each(auto p in m_vecSkinnedMesh)
	//{
	//	if(m_pFrustum->IsIn(p->GetBoundingSphere()))
	//	{
	//		p->UpdateAndRender(m_pController->GetWorldTM(), &matI);
	//	}
	if (m_pPlayer)
		m_pPlayer->Render();

	if (m_pBloat)
		m_pBloat->UpdateAndRender();

	if (m_fire)
	{
		D3DXCreateSphere(g_pD3DDevice,
			RADIUS,
			20,
			20,
			&m_pMesh,
			NULL);

		D3DXMATRIXA16 matB;
		D3DXMatrixTranslation(&matB,
			m_pBulletCollision->GetBulletPosition().x,
			m_pBulletCollision->GetBulletPosition().y,
			m_pBulletCollision->GetBulletPosition().z);

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matB);
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		m_pMesh->DrawSubset(0);
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		
		SAFE_RELEASE(m_pMesh);
		m_fire = false;
	}
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pMap->Render();
		
	m_pCrossHead->Render();
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if (m_pController)
	{
		m_pController->WndProc(hWnd, message, wParam, lParam);
	}


	switch (message)
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_LBUTTON:
		{
			
		}
		break;
		}
	}
	break;
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

