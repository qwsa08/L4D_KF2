#include "stdafx.h"
#include "cPickObj.h"
#include "cObjLoader.h"
#include "cMtlTex.h"


cPickObj::cPickObj()
	: m_PickShotGun(NULL)
	, m_OutLineShader(NULL)
	, m_PickBullpup(NULL)
	, m_PickHeal(NULL)
{
}


cPickObj::~cPickObj()
{
	SAFE_RELEASE(m_PickShotGun);
	SAFE_RELEASE(m_OutLineShader);

	for each(auto p in m_pShotGunMtltex)
	{
		SAFE_RELEASE(p);
	}

	for each(auto p in m_pBullpupMtltex)
	{
		SAFE_RELEASE(p);
	}

	for each(auto p in m_pHealMtltex)
	{
		SAFE_RELEASE(p);
	}
}

void cPickObj::Load(char* szMap, D3DXMATRIXA16* pmat)
{
	cObjLoader l;
	m_PickShotGun = l.Load(this, szMap, m_pShotGunMtltex, pmat);

	//m_PickBullpup = l.Load(this, "./PickWeapon/bullpup/Bullpup.obj", m_pBullpupMtltex, pmat);

	//m_PickHeal = l.Load(this, "./PickWeapon/healgun/Syringe.obj", m_pHealMtltex, pmat);

	m_OutLineShader = g_pShader->LoadShader("OutLine.fx");
}

void cPickObj::Render()
{

}

void cPickObj::Render(IN D3DXVECTOR4* LightPosition, IN D3DXVECTOR4* LightDirection)
{
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);

	D3DXMATRIXA16 matView, matProj, matWorld, matViewProjection;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_WORLD, &matWorld);

	matViewProjection = matView * matProj;

	m_OutLineShader->SetMatrix("fvEyePosition", &matView);

	m_OutLineShader->SetVector("fvLightPosition", LightPosition);

	PickShotGunRender();
	//PickWeaponRender(m_pShotGunMtltex, m_OutLineShader, m_PickShotGun, 1.f, -80.f, 1.f);
	//PickWeaponRender(m_pBullpupMtltex, m_OutLineShader, m_PickBullpup, 1.f, -80.f, -50.f);
}

void cPickObj::PickShotGunRender()
{
	D3DXMATRIXA16 matView, matProj, matWorld, matViewProjection;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_WORLD, &matWorld);

	matViewProjection = matView * matProj;

	//D3DXMatrixTranslation(&matWorld, 1.f, -80.f, 1.f);

	m_OutLineShader->SetMatrix("matWorld", &matWorld);
	m_OutLineShader->SetMatrix("matViewProjection", &matViewProjection);

	m_OutLineShader->SetMatrix("Textured_Phong_Pass_1_Vertex_Shader_matWorld", &matWorld);
	m_OutLineShader->SetMatrix("Textured_Phong_Pass_1_Vertex_Shader_matViewProjection", &matViewProjection);

	for (int i = 0; i < m_pShotGunMtltex.size(); i++)
	{
		UINT numPasses = 1;
		m_OutLineShader->SetTexture("base_Tex", m_pShotGunMtltex[i]->GetTexture());

		m_OutLineShader->Begin(&numPasses, NULL);
		{
			for (UINT j = 0; j < numPasses; ++j)
			{
				m_OutLineShader->BeginPass(j);
				{
					m_PickShotGun->DrawSubset(i);
				}
				m_OutLineShader->EndPass();
			}
		}
		m_OutLineShader->End();
	}
}

void cPickObj::PickBullpupRender()
{
	D3DXMATRIXA16 matView, matProj, matWorld, matViewProjection;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_WORLD, &matWorld);

	matViewProjection = matView * matProj;

	D3DXMatrixTranslation(&matWorld, 1.f, -80.f, -50.f);

	m_OutLineShader->SetMatrix("matWorld", &matWorld);
	m_OutLineShader->SetMatrix("matViewProjection", &matViewProjection);

	m_OutLineShader->SetMatrix("Textured_Phong_Pass_1_Vertex_Shader_matWorld", &matWorld);
	m_OutLineShader->SetMatrix("Textured_Phong_Pass_1_Vertex_Shader_matViewProjection", &matViewProjection);

	for (int i = 0; i < m_pBullpupMtltex.size(); i++)
	{
		UINT numPasses = 1;
		m_OutLineShader->SetTexture("base_Tex", m_pBullpupMtltex[i]->GetTexture());

		m_OutLineShader->Begin(&numPasses, NULL);
		{
			for (UINT j = 0; j < numPasses; ++j)
			{
				m_OutLineShader->BeginPass(j);
				{
					m_PickBullpup->DrawSubset(i);
				}
				m_OutLineShader->EndPass();
			}
		}
		m_OutLineShader->End();
	}
}

void cPickObj::PickHealRender()
{
	D3DXMATRIXA16 matView, matProj, matWorld, matViewProjection;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_WORLD, &matWorld);

	matViewProjection = matView * matProj;

	D3DXMatrixTranslation(&matWorld, 1.f, -80.f, -100.f);

	m_OutLineShader->SetMatrix("matWorld", &matWorld);
	m_OutLineShader->SetMatrix("matViewProjection", &matViewProjection);

	m_OutLineShader->SetMatrix("Textured_Phong_Pass_1_Vertex_Shader_matWorld", &matWorld);
	m_OutLineShader->SetMatrix("Textured_Phong_Pass_1_Vertex_Shader_matViewProjection", &matViewProjection);

	for (int i = 0; i < m_pShotGunMtltex.size(); i++)
	{
		UINT numPasses = 1;
		m_OutLineShader->SetTexture("base_Tex", m_pShotGunMtltex[i]->GetTexture());

		m_OutLineShader->Begin(&numPasses, NULL);
		{
			for (UINT j = 0; j < numPasses; ++j)
			{
				m_OutLineShader->BeginPass(j);
				{
					m_PickShotGun->DrawSubset(i);
				}
				m_OutLineShader->EndPass();
			}
		}
		m_OutLineShader->End();
	}
}

void cPickObj::PickWeaponRender(std::vector<cMtlTex*> Mtltex, LPD3DXEFFECT Shader, LPD3DXMESH Mesh, float Px, float Py, float Pz)
{
	D3DXMATRIXA16 matView, matProj, matWorld, matViewProjection;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_WORLD, &matWorld);

	matViewProjection = matView * matProj;

	D3DXMatrixTranslation(&matWorld, Px, Py, Pz);

	Shader->SetMatrix("matWorld", &matWorld);
	Shader->SetMatrix("matViewProjection", &matViewProjection);

	Shader->SetMatrix("Textured_Phong_Pass_1_Vertex_Shader_matWorld", &matWorld);
	Shader->SetMatrix("Textured_Phong_Pass_1_Vertex_Shader_matViewProjection", &matViewProjection);

	for (int i = 0; i < Mtltex.size(); i++)
	{
		UINT numPasses = 1;
		Shader->SetTexture("base_Tex", Mtltex[i]->GetTexture());

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

bool cPickObj::GetHeight(IN float x, OUT float& y, IN float z)
{

	std::vector<float> vY;

	D3DXVECTOR3 vRayPos(x, y + 70, z);
	D3DXVECTOR3 vRayDir(0, -1, 0);
	float u, v, d;

	D3DXVECTOR3 vPos(x, y, z);
	float Range;


	/*for (int i = 0; i < m_vecVerWall.size(); i += 3)
	{

	float LineMag;
	float U;
	D3DXVECTOR3 vIntersection;
	D3DXVECTOR3 _halfSpot;
	_halfSpot = (m_vecVerWall[i + 1].p + m_vecVerWall[i + 2].p) / 2;

	LineMag = D3DXVec3Length(&(_halfSpot - m_vecVerWall[i].p));

	U = (
	((vPos.x - m_vecVerWall[i].p.x) * (_halfSpot.x - m_vecVerWall[i].p.x)) +
	((vPos.y - m_vecVerWall[i].p.y) * (_halfSpot.y - m_vecVerWall[i].p.y)) +
	((vPos.z - m_vecVerWall[i].p.z) * (_halfSpot.z - m_vecVerWall[i].p.z))
	) / (LineMag * LineMag);

	if (U < 0.f || U >1.f) continue;

	vIntersection.x = m_vecVerWall[i].p.x + U *(_halfSpot.x - m_vecVerWall[i].p.x);
	vIntersection.y = m_vecVerWall[i].p.y + U *(_halfSpot.y - m_vecVerWall[i].p.y);
	vIntersection.z = m_vecVerWall[i].p.z + U *(_halfSpot.z - m_vecVerWall[i].p.z);

	Range = D3DXVec3Length(&(vIntersection - vPos));

	if (Range < 50.f)
	{
	return false;
	}
	}
	*/
	for (int i = 0; i < m_line.size(); i++)
	{
		D3DXVECTOR3 _line;
		_line = vPos - m_Start[i];
		D3DXVECTOR3 _lineNomal;
		D3DXVec3Normalize(&_lineNomal, &m_line[i]);

		D3DXVECTOR3 m_Spot, m_test;
		float numtest;
		numtest = D3DXVec3Dot(&_lineNomal, &_line);// *m_line[i];
		m_Spot = m_Start[i] + D3DXVec3Dot(&_lineNomal, &_line) * m_line[i];

		m_Spot = vPos - m_Spot;
		Range = D3DXVec3Length(&m_Spot);

		if (fabs(Range) < 35)
		{
			return false;
		}
	}

	for (size_t i = 0; i < m_vecVertex.size(); i += 3)
	{
		D3DXVECTOR3 v0 = m_vecVertex[i].p;
		D3DXVECTOR3 v1 = m_vecVertex[i + 1].p;
		D3DXVECTOR3 v2 = m_vecVertex[i + 2].p;
		if (D3DXIntersectTri(&v0, &v1, &v2, &vRayPos, &vRayDir, &u, &v, &d))
		{
			//return true;
			if (d > 210) continue;
			vY.push_back(y + 70 - d);
		}
	}
	if (vY.size() > 0)
	{
		float hMax = vY[0];
		for (int i = 0; i < vY.size(); ++i)
		{
			if (hMax < vY[i])
			{
				hMax = vY[i];
			}
		}
		y = hMax;
		return true;
	}
	y = 0;
	return false;

}