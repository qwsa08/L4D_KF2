#include "stdafx.h"
#include "cBulletCollision.h"
#include "cCrtController.h"
#include "cObjMap.h"

cBulletCollision::cBulletCollision()
	: m_pRenderTargetSurface(NULL)
	, m_pRenderTargetTexture(NULL)
	, m_pSprite(NULL)
	, m_nRenderTargetWidth(1024)
	, m_nRenderTargetHeight(1024)
	, m_pEffect(NULL)
	, m_Texture(NULL)
	, y(0.f)
{
}


cBulletCollision::~cBulletCollision()
{
	SAFE_RELEASE(m_pRenderTargetSurface);
	SAFE_RELEASE(m_pRenderTargetTexture);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pEffect);
	SAFE_RELEASE(m_Texture);
	SAFE_RELEASE(m_pBulletholes);
	
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

	

	m_pEffect = g_pShader->LoadShader("Depth.fx");
	m_pBulletholes = g_pShader->LoadShader("Bullet.fx");

	m_Texture = g_pTextureManager->GetTexture("Earth.jpg");
	
	int a = 0;
}

void cBulletCollision::Render(iMap* Map)
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
	g_pD3DDevice->BeginScene();


	D3DXMATRIXA16 matWorld, matView, matProj, matWV, matWVP;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	matWV = matWorld * matView;
	matWVP = matWorld * matView * matProj;
	m_pEffect->SetMatrix("matWV", &matWV);
	m_pEffect->SetMatrix("matWVP", &matWVP);
	m_pEffect->SetFloat("gFar", 50000.f);

	UINT numPasses = 0;
	m_pEffect->Begin(&numPasses, NULL);

	for (UINT i = 0; i < numPasses; ++i)
	{
		m_pEffect->BeginPass(i);
		Map->Render();
		m_pEffect->EndPass();
	}

	m_pEffect->End();



	g_pD3DDevice->EndScene();

	g_pD3DDevice->SetRenderTarget(0, pOrgRenderTargetSurface);
	g_pD3DDevice->SetDepthStencilSurface(pOrgDepthStencilSurface);

	SAFE_RELEASE(pOrgRenderTargetSurface);
	SAFE_RELEASE(pOrgDepthStencilSurface);

	

	/*m_pSprite->Begin(D3DXSPRITE_SORT_TEXTURE);

	m_pSprite->Draw(m_pRenderTargetTexture,
		&rc,
		NULL,
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));

	m_pSprite->End();*/
	
}		

void cBulletCollision::Fire(iMap* Map)
{
	LPD3DXMESH		m_pMesh;
	
	D3DXCreateBox(g_pD3DDevice,
		1, 1, 1, &m_pMesh, NULL);
	
	if (g_pKeyManager->isStayKeyDown(VK_DOWN))
	{
		y -= 1.f;
	}
	if (g_pKeyManager->isStayKeyDown(VK_UP))
	{
		y += 1.f;
	}
	
	D3DXMATRIXA16 matW, matB ,matS;
	D3DXMatrixTranslation(&matB,
		m_vBulletPoint.x,
		m_vBulletPoint.y,
		m_vBulletPoint.z);//m_vBulletPoint.z);
	D3DXMatrixScaling(&matS, 10, 10, 10);
	/*
	ST_PT_VERTEX v;
	std::vector<D3DXVECTOR3> Vertex;
	Vertex.push_back(D3DXVECTOR3(-0.5f, -0.5f, -0.5f));
	Vertex.push_back(D3DXVECTOR3(-0.5f,  0.5f, -0.5f));
	Vertex.push_back(D3DXVECTOR3( 0.5f,  0.5f, -0.5f));
	Vertex.push_back(D3DXVECTOR3( 0.5f, -0.5f, -0.5f));
	Vertex.push_back(D3DXVECTOR3(-0.5f, -0.5f,  0.5f));
	Vertex.push_back(D3DXVECTOR3(-0.5f,  0.5f,  0.5f));
	Vertex.push_back(D3DXVECTOR3( 0.5f,  0.5f,  0.5f));
	Vertex.push_back(D3DXVECTOR3( 0.5f, -0.5f,  0.5f));

	
	v.p =   v.t = D3DXVECTOR2(0, 1); m_vBox.push_back(v);
	v.p =   v.t = D3DXVECTOR2(0, 0); m_vBox.push_back(v);
	v.p =   v.t = D3DXVECTOR2(1, 0); m_vBox.push_back(v);
	v.p =   v.t = D3DXVECTOR2(0, 1); m_vBox.push_back(v);
	v.p =   v.t = D3DXVECTOR2(1, 0); m_vBox.push_back(v);
	v.p =   v.t = D3DXVECTOR2(1, 1); m_vBox.push_back(v);
	*/	   
	

	//1.�Ž����� �����ϰ� �ڽ�������� �װ��� ������ ���� (������ ����!)
	//2.uv�� �ȸ´´� ���� �ؽ��ĸ� �׸��°��� �Ž���ü�� �θ��°� �ƴϴ�.
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matB);

	

	D3DXMATRIXA16 matWorld, matView, matProj, matWV, matWVP, matInvV, matInvP, matInvW;
	D3DXMatrixIdentity(&matWorld);
	matWorld = matS *matB;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	matWV = matWorld * matView;
	matWVP = matWorld * matView * matProj;

	D3DXMatrixInverse(&matInvV, 0, &matView);
	D3DXMatrixInverse(&matInvV, 0, &matInvW);
	//================���⼭ ����;;;=====================//
	D3DXVECTOR3 temp(1, 1, 1);
	D3DXVECTOR3	vCamera(0, 0, 0);
	D3DXMatrixInverse(&matInvP, 0, &matProj);
	D3DXVec3TransformCoord(&vCamera, &temp, &matProj);
	
	m_pBulletholes->SetMatrix("mWV", &matWV);
	m_pBulletholes->SetMatrix("mWVP", &matWVP);
	m_pBulletholes->SetMatrix("InvV", &matInvV);
	m_pBulletholes->SetVector("CameraRightTop", &D3DXVECTOR4(vCamera,1.f));

	m_pBulletholes->SetTexture("texSamp_Tex", m_Texture);
	m_pBulletholes->SetTexture("base_Tex", m_pRenderTargetTexture);
	

	UINT numPasses = 0;
	m_pBulletholes->Begin(&numPasses, NULL);
	
	for (UINT i = 0; i < numPasses; ++i)
	{
		m_pBulletholes->BeginPass(i);
		{
			//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			m_pMesh->DrawSubset(0);
			g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
		m_pBulletholes->EndPass();
	}
	
	m_pBulletholes->End();
	
	/*g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pMesh->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);*/
	SAFE_RELEASE(m_pMesh);
	



}

void cBulletCollision::Bulletholes(cCrtController* Controller)
{
	/*m_pBulletholes = g_pShader->LoadShader("Bullet.fx");

	D3DXMATRIXA16 matWorld, matView, matProj, matWV, matWVP, matInvV;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	matWV = matWorld * matView;
	matWVP = matWorld * matView * matProj;
	D3DXMatrixInverse(&matInvV, 0, &matWV);


	m_pBulletholes->SetMatrix("matWV", &matWV);
	m_pBulletholes->SetMatrix("matWVP", &matWVP);
	m_pBulletholes->SetFloat("gFar", 1000.f);
	m_pBulletholes->SetMatrix("InvWV", &matWVP);
	m_pBulletholes->SetVector("CameraRightTop", &D3DXVECTOR4(*Controller->GetPosition(), 1.f));
*/
	
	
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
		for (int i = 0; i < 3; i++)
		{
			m_vOverTex.push_back(m_pMap[vecWallNear[0].num + i]);
		}
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