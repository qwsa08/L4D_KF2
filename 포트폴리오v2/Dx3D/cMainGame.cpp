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
#include "cSkinnedMesh.h"
#include "cFrustum.h"
#include "cMapXfile.h"

#define RADIUS 0.3f

cMainGame::cMainGame(void)
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pController(NULL)
	, m_pPyramid(NULL)
	, m_pMap(NULL)
	, m_pMesh(NULL)
	, m_pMapMesh(NULL)
	, m_pFrustum(NULL)
	, m_pSkinnedMesh(NULL)
{
}

cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pController);
	for each(auto p in m_vecSkinnedMesh)
	{
		SAFE_DELETE(p);
	}
	SAFE_DELETE(m_pFrustum);

	SAFE_RELEASE(m_pPyramid);
	SAFE_RELEASE(m_pMap);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMapMesh);

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

	//D3DXPLANE
	//D3DXPlaneFromPoints(평면, 점1, 점2, 점3);
	//거리 = D3DXPlaneDotCoord(평면, 점) 앞:양수, 뒤:음수


	m_pSkinnedMesh = new cSkinnedMesh("Zombie/Clot/", "ZED_Clot.X");
	//m_pSkinnedMesh->SetAnimationIndex(rand() % 5);
	m_pSkinnedMesh->SetRandomTrackPosition();
	m_pSkinnedMesh->SetPosition(D3DXVECTOR3(0, 0,2));
	m_vecSkinnedMesh.push_back(m_pSkinnedMesh);

	D3DXCreateSphere(g_pD3DDevice, RADIUS, 20, 20, &m_pMesh, NULL);

	D3DXMATRIXA16 matS, matR, matT, mat;
	/*D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	mat = matS * matR;*/
	D3DXMatrixIdentity(&mat);

	cObjMap* pObjMap = new cObjMap;
	pObjMap->Load("./Map/House14.ptop",&mat);
	m_pMap = pObjMap;

	/*cMapXfile* m_pMapXFile = new cMapXfile;
	m_pMapXFile->Setup("house08/house_08.X");
	m_pMap = m_pMapXFile;*/

//	cObjLoader objloader;
//	m_pMapMesh = objloader.Load("obj/Map.obj", m_vecMtlTex, &mat);

	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pController = new cCrtController;
	m_pController->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup(30);

	
	
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
}

void cMainGame::Update()
{
	g_pTimeManager->Update();
	
	if(m_pController)
		m_pController->Update(m_pMap);

	/*if(m_pPyramid)
	{
		m_pPyramid->SetDirection(m_pController->GetDirection());
		m_pPyramid->SetPosition(*(m_pController->GetPosition()));
		m_pPyramid->Update();
	}*/

	if(m_pCamera)
		m_pCamera->Update(m_pController->GetPosition());
	
	if(m_pFrustum)
	{
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
		//	m_pFrustum->Update();
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
	D3DXMatrixScaling(&matS, 0.5, 0.5, 0.5);
	

	
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	for each(auto p in m_vecSkinnedMesh)
	{
		if(m_pFrustum->IsIn(p->GetBoundingSphere()))
		{
			p->UpdateAndRender(m_pController->GetWorldTM(),&matS);
		}
	}

	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pMap->Render();
	
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if (m_pCamera)
	{
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
	}

	switch(message)
	{
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_SPACE:
				{
					static int n = 0;
					m_pSkinnedMesh->SetAnimationIndex(++n % 10);
					
				}
				break;
			}
		}
		break;

	case WM_LBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			cRay r = cRay::RayAtWorldSpace(x, y);
			for (size_t i = 0; i < m_vecSphere.size(); ++i)
			{
				m_vecSphere[i].isPicked = r.IsPicked(m_vecSphere[i]);
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

