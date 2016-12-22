#include "stdafx.h"
#include "cMapXfile.h"


cMapXfile::cMapXfile()
	: m_pOutLineShader(NULL)
	, m_pShotgun(NULL)
	, m_pBullpup(NULL)
	, m_pHeal(NULL)
{
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

	return Mesh;
}

void cMapXfile::PickWeaponLoad()
{
	m_pShotgun = MeshXFileLoad("./PickWeapon/shotgun/shotgun.X", &m_pShotGunMtl, &m_pShotGunTex);
	m_pBullpup = MeshXFileLoad("./PickWeapon/bullpup/Bullpup.X", &m_pBullpupMtl, &m_pBullpupTex);
	m_pHeal = MeshXFileLoad("./PickWeapon/Healgun/heal.X", &m_pHealMtl, &m_pHealTex);

	m_pOutLineShader = g_pShader->LoadShader("OutLine.fx");

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

	D3DXMATRIXA16 matS, matR, matT;
	D3DXMATRIXA16 matShotgun, matBullpup, matHeal;

	D3DXMatrixScaling(&matS, 0.85f, 0.85f, 0.85f);
	D3DXMatrixRotationY(&matR, -D3DX_PI / 2);
	D3DXMatrixTranslation(&matT, 653.f, 151.f, -640.f);
	matBullpup = matS * matR * matT;
	PickWeaponRender(m_pBullpupMtl, m_pBullpupTex, m_pOutLineShader, m_pBullpup, matBullpup);

	D3DXMatrixRotationY(&matR, -D3DX_PI / 2);
	D3DXMatrixTranslation(&matT, 653.f, 151.f, -600.f);
	matHeal = matR * matT;
	PickWeaponRender(m_pHealMtl, m_pHealTex, m_pOutLineShader, m_pHeal, matHeal);

	D3DXMATRIXA16 matRx;
	D3DXMatrixScaling(&matS, 0.8f, 0.8f, 0.8f);
	D3DXMatrixRotationX(&matRx, (D3DX_PI / 180) * 79);
	D3DXMatrixRotationY(&matR, -D3DX_PI / 2);
	D3DXMatrixTranslation(&matT, 653.f, 131.f, -585.f);
	matShotgun = matS * matR * matRx * matT;
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

bool cMapXfile::GetHeight(IN float x, OUT float& y, IN float z)
{
	//int XY_MAX = 100000;
	//if (x<0 || x > XY_MAX || z < 0 || z > XY_MAX)
	//{
	//	y = 0.f;
	//	return false;
	//}
	//int _x = (int)x;
	//int _z = (int)z;

	////»ï°¢ÇüÀÌ´Ï±ñ ÀÎµ¦½º¹öÆÛ¾È¿¡ ÀÖ´Â »ï°¢Çü!!?!
	//int _0 = _z * XY_MAX + _x;
	//int _1 = (_z + 1) * XY_MAX + _x;
	//int _2 = _z * XY_MAX + _x + 1;
	//int _3 = (_z + 1) * XY_MAX + _x + 1;

	//float fx = x - _x;
	//float fz = z - _z;
	//if (fx + fz < 1)
	//{
	//	D3DXVECTOR3 Vx = m_vPNT[_2].p - m_vPNT[_0].p;
	//	D3DXVECTOR3 Vz = m_vPNT[_1].p - m_vPNT[_0].p;

	//	y = m_vPNT[_0].p.y + (Vx * fx + Vz * fz).y;
	//	int a = 0;
	//}
	//else
	//{
	//	fx = 1.f - fx;
	//	fz = 1.f - fz;

	//	D3DXVECTOR3 Vx = m_vPNT[_1].p - m_vPNT[_3].p;
	//	D3DXVECTOR3 Vz = m_vPNT[_2].p - m_vPNT[_3].p;

	//	y = m_vPNT[_3].p.y + (Vx * fx + Vz * fz).y;
	//}

	return true;
}

void cMapXfile::Render()
{

}