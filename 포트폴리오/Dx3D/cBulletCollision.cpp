#include "stdafx.h"
#include "cBulletCollision.h"
#include "cCrtController.h"
#include "cObjMap.h"

cBulletCollision::cBulletCollision()
	: m_pRenderTargetSurface(NULL)
	, m_pRenderTargetTexture(NULL)
	, m_pSprite(NULL)
	, m_pEffect(NULL)
	, m_Texture(NULL)
	, y(0.f)
	, m_pMesh(NULL)
	, m_test(false)
{
	m_nRenderTargetWidth;
	m_nRenderTargetHeight;
}


cBulletCollision::~cBulletCollision()
{
	SAFE_RELEASE(m_pRenderTargetSurface);
	SAFE_RELEASE(m_pRenderTargetTexture);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pEffect);
	//SAFE_RELEASE(m_Texture);
	SAFE_RELEASE(m_pBulletholes);
	SAFE_RELEASE(m_pMesh);
}

void cBulletCollision::SetUp(cObjMap* Map)
{
	m_pMap = Map->GetMap();
	m_vecClipping.resize(6);

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	
	GetClientRect(g_hWnd, &rc);
	g_pD3DDevice->CreateTexture(
		rc.right,
		rc.bottom,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_pRenderTargetTexture,
		NULL);

	g_pD3DDevice->CreateDepthStencilSurface(rc.right,
		rc.bottom,
		D3DFMT_D24X8, D3DMULTISAMPLE_NONE, 0, TRUE, &m_pRenderTargetSurface, NULL);

	

	m_pEffect = g_pShader->LoadShader("shader.fx");
	m_pBulletholes = g_pShader->LoadShader("decal.fx");
	//m_pBulletholes = g_pShader->LoadShader("Bullet.fx");

	m_Texture = g_pTextureManager->GetTexture("box.jpg");
	D3DXCreateBox(g_pD3DDevice,1, 1, 1, &m_pMesh, NULL);
	int a = 0;
}

void cBulletCollision::Render(iMap* Map, cCrtController* Controller)
{
	LPDIRECT3DSURFACE9 pOrgRenderTargetSurface = NULL;
	LPDIRECT3DSURFACE9 pOrgDepthStencilSurface = NULL;
	g_pD3DDevice->GetRenderTarget(0, &pOrgRenderTargetSurface);
	g_pD3DDevice->GetDepthStencilSurface(&pOrgDepthStencilSurface);

	LPDIRECT3DSURFACE9 pShadowSurface = NULL;
	if (SUCCEEDED(m_pRenderTargetTexture->GetSurfaceLevel(0, &pShadowSurface)))
	{
		g_pD3DDevice->SetRenderTarget(0, pShadowSurface);
		pShadowSurface->Release();
		pShadowSurface = NULL;
	}
	g_pD3DDevice->SetDepthStencilSurface(m_pRenderTargetSurface);

	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 255, 255, 255),
		1.0f,
		0);

	D3DXMATRIXA16 matWorld, matProj, matWV, matWVP, matInvV, matInvP, matInvWV;
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &m_matView);



	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &m_matProj);

	matWV = matWorld * m_matView;
	matWVP = matWorld * m_matView * m_matProj;
	m_pEffect->SetMatrix("matWV", &matWV);
	m_pEffect->SetMatrix("matWVP", &matWVP);

	if (m_test)
	{
		D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.f, 200.f);
		g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
		m_pEffect->SetFloat("fFar", 200.f);
	}
	else
	{

		D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.f, 5000.f);
		g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
		m_pEffect->SetFloat("fFar", 5000.f);
	}

	UINT numPasses = 0;
	m_pEffect->Begin(&numPasses, NULL);

	for (UINT i = 0; i < numPasses; ++i)
	{
		m_pEffect->BeginPass(i);
		Map->Render();
		/*Map->Render(
			&D3DXVECTOR4(*Controller->GetPosition(), 1.f),
			&D3DXVECTOR4(Controller->GetDirection(), 1.f));*/
		m_pEffect->EndPass();
	}

	m_pEffect->End();
	g_pD3DDevice->SetRenderTarget(0, pOrgRenderTargetSurface);
	g_pD3DDevice->SetDepthStencilSurface(pOrgDepthStencilSurface);
	
	SAFE_RELEASE(pOrgRenderTargetSurface);
	SAFE_RELEASE(pOrgDepthStencilSurface);
	//=============================================================
	D3DXMATRIXA16 matW, matB, matS, matX, matY, matR;
//	D3DXMATRIXA16 matWorld, matProj, matWV, matWVP, matInvV, matInvP, matInvWV;
	D3DXMatrixTranslation(&matB,
		m_vBulletPoint.x,
		m_vBulletPoint.y,
		m_vBulletPoint.z);//m_vBulletPoint.z);
	D3DXMatrixScaling(&matS, 10, 10, 10);
	D3DXMatrixIdentity(&matWorld);
	//D3DXMatrixIdentity(&matS);
	
	//g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &m_matProj);
//	matWorld = matS  *matB;
	matWorld = matS  *matB;
	matWV = matWorld * m_matView;
	matWVP = matWorld * m_matView * m_matProj;

	D3DXMatrixInverse(&matInvV, 0, &m_matView);
	D3DXMatrixInverse(&matInvP, 0, &m_matProj);
	D3DXMatrixInverse(&matInvWV, 0, &matWV);

	//=========================이것의 문제인듯하다!...!?!...!?!!?..?!
	D3DXVECTOR4 vRightTop(1, -1, 1, 1);
	D3DXVec4Transform(&vRightTop, &vRightTop, &matInvP);
	vRightTop /= vRightTop.w;

	//	D3DXVECTOR4 vCamera = Controller->GetDirection();
	//	D3DXVec4Normalize(&vCamera, &vCamera);
	//	D3DXVECTOR3 vRightTop(0,0,0);
	//	D3DXVec4Transform(&vCamera, &vCamera, &matInvP);
	//	vCamera /= vCamera.w;
	m_pBulletholes->SetMatrix("matWV", &matWV);
	m_pBulletholes->SetMatrix("matWVP", &matWVP);
	m_pBulletholes->SetMatrix("matInvWorldView", &matInvWV);
	//m_pBulletholes->SetVector("CameraRightTop", &D3DXVECTOR4(vRightTop,1.0f));
	m_pBulletholes->SetVector("CameraRightTop", &vRightTop);
	m_pBulletholes->SetTexture("DecalTex", m_Texture);
	m_pBulletholes->SetTexture("DepthMapTex", m_pRenderTargetTexture);
	

	 numPasses = 0;
	m_pBulletholes->Begin(&numPasses, NULL);

	

	for (UINT i = 0; i < numPasses; ++i)
	{
		m_pBulletholes->BeginPass(i);
		m_pMesh->DrawSubset(0);
		m_pBulletholes->EndPass();
	}

	m_pBulletholes->End();

	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pMesh->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);


	if (g_pKeyManager->isStayKeyDown('B'))
	{
		m_pSprite->Begin(D3DXSPRITE_SORT_TEXTURE);

		m_pSprite->Draw(m_pRenderTargetTexture,
			&rc,
			NULL,
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_XRGB(255, 255, 255));

		m_pSprite->End();
	}

}		

void cBulletCollision::Fire(iMap* Map)
{
	LPDIRECT3DSURFACE9 pOrgRenderTargetSurface = NULL;
	LPDIRECT3DSURFACE9 pOrgDepthStencilSurface = NULL;
	g_pD3DDevice->GetRenderTarget(0, &pOrgRenderTargetSurface);
	g_pD3DDevice->GetDepthStencilSurface(&pOrgDepthStencilSurface);

	LPDIRECT3DSURFACE9 pShadowSurface = NULL;
	if (SUCCEEDED(m_pRenderTargetTexture->GetSurfaceLevel(0, &pShadowSurface)))
	{
		g_pD3DDevice->SetRenderTarget(0, pShadowSurface);
		pShadowSurface->Release();
		pShadowSurface = NULL;
	}
	g_pD3DDevice->SetDepthStencilSurface(m_pRenderTargetSurface);

	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 255, 255, 255),
		1.0f,
		0);

	D3DXMATRIXA16 matWorld, matProj, matWV, matWVP, matInvV, matInvP, matInvWV;
	D3DXMatrixIdentity(&matWorld);
	//g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &m_matView);


	// g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &m_matProj);

	//if (m_test)
	{
		D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.f, 200.f);
		//g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
		m_pEffect->SetFloat("fFar", 200.f);
	}


	matWV = matWorld * m_matView;
	matWVP = matWorld * m_matView * m_matProj;
	m_pEffect->SetMatrix("matWV", &matWV);
	m_pEffect->SetMatrix("matWVP", &matWVP);

	/*else
	{
		D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.f, 2000.f);
		g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
		m_pEffect->SetFloat("fFar", 2000.f);
	}*/

	UINT numPasses = 0;
	m_pEffect->Begin(&numPasses, NULL);

	for (UINT i = 0; i < numPasses; ++i)
	{
		m_pEffect->BeginPass(i);
		Map->Render();
		m_pEffect->EndPass();
	}

	m_pEffect->End();


	g_pD3DDevice->SetRenderTarget(0, pOrgRenderTargetSurface);
	g_pD3DDevice->SetDepthStencilSurface(pOrgDepthStencilSurface);

	SAFE_RELEASE(pOrgRenderTargetSurface);
	SAFE_RELEASE(pOrgDepthStencilSurface);
	//=============================================================
	
}

void cBulletCollision::Bulletholes(cCrtController* Controller)
{
	
	
}

bool cBulletCollision::PickBullet(cCrtController* Controller)
{
	std::vector<ST_WallNear> vecWallNear;
	D3DXVECTOR3 Position = *(Controller->GetPosition());
	D3DXVECTOR3 vRayPos(Position.x, Position.y, Position.z);
	D3DXVECTOR3 vRayDir = Controller->GetDirection();
	m_vOverTex.clear();
	float u, v, d;
	
	for (int i = 0; i < m_pMap.size(); i+=3)
	{
		D3DXVECTOR3 v0 = m_pMap[i].p;
		D3DXVECTOR3 v1 = m_pMap[i + 1].p;
		D3DXVECTOR3 v2 = m_pMap[i + 2].p;

		if (D3DXIntersectTri(&v0, &v1, &v2, &vRayPos, &vRayDir, &u, &v, &d))
		{
			D3DXVECTOR3 BulletPoint(0, 0, 0);
			BulletPoint = v0 + u * (v1 - v0) + v * (v2 - v0);
			if (d > 5000.f) return false;
			vecWallNear.push_back(ST_WallNear(BulletPoint, d,i));
			
		}
	}
	if (vecWallNear.size() > 0)
	{
		for (int i = 0; i < vecWallNear.size(); i++)
		{
			if (vecWallNear[0].fRange > vecWallNear[i].fRange)
			{
				ST_WallNear Temp;
				Temp = vecWallNear[0];
				vecWallNear[0] = vecWallNear[i];
				vecWallNear[i] = Temp;
			}
		}
		m_vBulletPoint = vecWallNear[0].WallPosition;
		/*for (int i = 0; i < 3; i++)
		{
			m_vOverTex.push_back(m_pMap[vecWallNear[0].num + i]);
		}*/
		return true;
	}
	return false;
}


D3DXMATRIXA16 cBulletCollision::Clipping()
{
	D3DXMATRIXA16 Cliiping;
	D3DXMatrixPerspectiveFovLH(&Cliiping, D3DX_PI / 4.0f, 2.f, 1, 20);
	
	return Cliiping;
}