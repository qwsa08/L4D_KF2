#include "stdafx.h"
#include "cMapXfile.h"
#include "cOBB.h"

cMapXfile::cMapXfile()
	: m_pOutLineShader(NULL)
	, m_pShotgun(NULL)
	, m_pBullpup(NULL)
	, m_pHeal(NULL)
	, m_Color(1.f,0.f,0.f,1.f)
{
	for (int i = 0; i < 4; i++)
	{
		_OBB[i] = new cOBB;
	}
}


cMapXfile::~cMapXfile()
{
	SAFE_RELEASE(m_pOutLineShader);

	SAFE_RELEASE(m_pShotgun);
	SAFE_RELEASE(m_pBullpup);
	SAFE_RELEASE(m_pHeal);

	for (int i = 0; i < m_pShotGunTex.size(); i++)
		SAFE_RELEASE(m_pShotGunTex[i]);

	for (int i = 0; i < m_pBullpupTex.size(); i++)
		SAFE_RELEASE(m_pBullpupTex[i]);

	for (int i = 0; i < m_pHealTex.size(); i++)
		SAFE_RELEASE(m_pHealTex[i]);
	
}


LPD3DXMESH cMapXfile::MeshXFileLoad(
	char* szFilename, 
	std::vector<D3DMATERIAL9>* Mtrls,
	std::vector<LPDIRECT3DTEXTURE9>* Textures)
{
	LPD3DXMESH Mesh;
	_min = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	_max = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	HRESULT hr = 0;

	ID3DXBuffer* adjBuffer = 0;
	ID3DXBuffer* mtrlBuffer = 0;
	DWORD numMtrls = 0;

	hr = D3DXLoadMeshFromX(
		szFilename,
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&adjBuffer,
		&mtrlBuffer,
		0,
		&numMtrls,
		&Mesh);

	if (mtrlBuffer != 0 && numMtrls != 0)
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		for (int i = 0; i < numMtrls; i++)
		{
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;

			Mtrls->push_back(mtrls[i].MatD3D);

			if (mtrls[i].pTextureFilename != 0)
			{
				LPDIRECT3DTEXTURE9 tex = 0;

				D3DXCreateTextureFromFile(
					g_pD3DDevice,
					mtrls[i].pTextureFilename,
					&tex);

				Textures->push_back(tex);
			}

			else
			{
				Textures->push_back(0);
			}
		}
	}

	SAFE_RELEASE(mtrlBuffer);

	
	ST_PC_VERTEX* pV = NULL;
	Mesh->LockVertexBuffer(0, (LPVOID*)&pV);
	D3DXComputeBoundingBox((D3DXVECTOR3*)pV,
		Mesh->GetNumVertices(),
		D3DXGetFVFVertexSize(ST_PC_VERTEX::FVF),
		&_min,
		&_max);

	/*for (int i = 0; i < Mesh->GetNumVertices(); i++)
	{
		vecVertex.push_back(pV[i].p);
	}*/
	
	//memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PC_VERTEX));
//	int a = 0;
	Mesh->UnlockVertexBuffer();

	
	return Mesh;
}

void cMapXfile::PickWeaponLoad()
{
	//================================
	D3DXMATRIXA16 matRx;
	D3DXMatrixScaling(&matS, 0.8f, 0.8f, 0.8f);
	D3DXMatrixRotationX(&matRx, (D3DX_PI / 180) * 79);
	D3DXMatrixRotationY(&matR, -D3DX_PI / 2);
	D3DXMatrixTranslation(&matT, 653.f, 131.f, -585.f);
	matShotgun = matS * matR * matRx * matT;
	//================================
	m_pShotgun = MeshXFileLoad("./PickWeapon/shotgun/shotgun.X", &m_pShotGunMtl, &m_pShotGunTex);
	_OBB[0]->SetupOBJ(_min, _max, BoundingBox[0], &matShotgun);
	BoundingBoxWTM.push_back(matShotgun);
	//=================================
	D3DXMatrixScaling(&matS, 0.85f, 0.85f, 0.85f);
	D3DXMatrixRotationY(&matR, -D3DX_PI / 2);
	D3DXMatrixTranslation(&matT, 653.f, 151.f, -640.f);
	matBullpup = matS * matR * matT;
	//==================================
	m_pBullpup = MeshXFileLoad("./PickWeapon/bullpup/Bullpup.X", &m_pBullpupMtl, &m_pBullpupTex);
	_OBB[1]->SetupOBJ(_min, _max, BoundingBox[1], &matBullpup);
	BoundingBoxWTM.push_back(matBullpup);
	//=================================
	D3DXMatrixRotationY(&matR, -D3DX_PI / 2);
	D3DXMatrixTranslation(&matT, 653.f, 151.f, -600.f);
	matHeal = matR * matT;
	//==================================
	m_pHeal = MeshXFileLoad("./PickWeapon/Healgun/heal.X", &m_pHealMtl, &m_pHealTex);
	_OBB[2]->SetupOBJ(_min, _max, BoundingBox[2], &matHeal);
	BoundingBoxWTM.push_back(matHeal);
	
	m_pOutLineShader = g_pShader->LoadShader("OutLine.fx");

	//=========================================
	D3DXMatrixTranslation(&matT, 653.f, 151.f, -620.f);
	D3DXMATRIXA16 matBox;
	D3DXMatrixIdentity(&matBox);
	matBox =matS * matT;
	_OBB[3]->SetupOBJ(D3DXVECTOR3(-50.f, -20.f, -50.f), D3DXVECTOR3(50.f, 20.f, 50.f), BoundingBox[3], &matBox);

	
	
}

void cMapXfile::Render(IN D3DXVECTOR4* LightPosition, IN D3DXVECTOR4* LightDirection)
{
	D3DXMATRIXA16 matW;
	D3DXMatrixIdentity(&matW);

	g_pD3DDevice->GetTransform(D3DTS_WORLD, &matW);

	D3DXMATRIXA16 matView, matProj, matWorld, matViewProjection;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_WORLD, &matWorld);

	m_pOutLineShader->SetMatrix("fvEyePosition", &matView);
	m_pOutLineShader->SetVector("fvLightPosition", LightPosition);
	m_pOutLineShader->SetVector("Color", &m_Color);
	//D3DXMATRIXA16 matS, matR, matT;
	//D3DXMATRIXA16 matShotgun, matBullpup, matHeal;

	//D3DXMatrixScaling(&matS, 0.85f, 0.85f, 0.85f);
	//D3DXMatrixRotationY(&matR, -D3DX_PI / 2);
	//D3DXMatrixTranslation(&matT, 653.f, 151.f, -640.f);
	//matBullpup = matS * matR * matT;
	PickWeaponRender(m_pBullpupMtl, m_pBullpupTex, m_pOutLineShader, m_pBullpup, matBullpup);

	//D3DXMatrixRotationY(&matR, -D3DX_PI / 2);
	//D3DXMatrixTranslation(&matT, 653.f, 151.f, -600.f);
	//matHeal = matR * matT;
	PickWeaponRender(m_pHealMtl, m_pHealTex, m_pOutLineShader, m_pHeal, matHeal);

	//D3DXMATRIXA16 matRx;
	//D3DXMatrixScaling(&matS, 0.8f, 0.8f, 0.8f);
	//D3DXMatrixRotationX(&matRx, (D3DX_PI / 180) * 79);
	//D3DXMatrixRotationY(&matR, -D3DX_PI / 2);
	//D3DXMatrixTranslation(&matT, 653.f, 131.f, -585.f);
	//matShotgun = matS * matR * matRx * matT;
	PickWeaponRender(m_pShotGunMtl, m_pShotGunTex, m_pOutLineShader, m_pShotgun, matShotgun);
}

void cMapXfile::PickWeaponRender(
	std::vector<D3DMATERIAL9> vecMtl,
	std::vector<LPDIRECT3DTEXTURE9> vecTex,
	LPD3DXEFFECT Shader, LPD3DXMESH Mesh,
	D3DXMATRIX World)
{
	D3DXMATRIXA16 matView, matProj, matWorld, matViewProjection;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_WORLD, &matWorld);

	matViewProjection = matView * matProj;

	matWorld = World;

	Shader->SetMatrix("matWorld", &matWorld);
	Shader->SetMatrix("matViewProjection", &matViewProjection);

	Shader->SetMatrix("Textured_Phong_Pass_1_Vertex_Shader_matWorld", &matWorld);
	Shader->SetMatrix("Textured_Phong_Pass_1_Vertex_Shader_matViewProjection", &matViewProjection);

	for (int i = 0; i < vecMtl.size(); i++)
	{
		UINT numPasses = 1;
		Shader->SetTexture("base_Tex", vecTex[i]);

		Shader->Begin(&numPasses, NULL);
		{
			for (UINT j = 0; j < numPasses; ++j)
			{
				Shader->BeginPass(j);
				{
					Mesh->DrawSubset(i);
				}
				Shader->EndPass();
			}
		}
		Shader->End();
	}
}

void cMapXfile::Render()
{
	
	_OBB[3]->DebugRender(&BoundingBox[3], D3DCOLOR_XRGB(255, 255, 0));
	//for (int i = 0; i < m_vOBB.size(); i++)
	{
		//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_vOBB[i]->GetWTM());
		//m_vOBB[3]->DebugRender(&BoundingBox[3], D3DCOLOR_XRGB(255, 255, 0));
	}
}