#include "stdafx.h"
#include "cEffect.h"


cEffect::cEffect()
	: m_pEffect(NULL)
	, f_timer(0.f)
	, OnOff(false)
	, f_UVx(0)
	, f_UVy(0)
	, m_iFramenum(0)
{
}


cEffect::~cEffect()
{
	SAFE_RELEASE(m_pEffect);
	//SAFE_RELEASE(m_pTexture);
}

void cEffect::Setup(char* effectName, int frameNum)
{
	ST_PT_VERTEX v;

	v.p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);	v.t = D3DXVECTOR2(0.0f, 0.25f);   m_tempTextureUV.push_back(v.t); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);  v.t = D3DXVECTOR2(0.0f, 0.0f);    m_tempTextureUV.push_back(v.t); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, -1.0f);   v.t = D3DXVECTOR2(0.25f, 0.0f);   m_tempTextureUV.push_back(v.t); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f); v.t = D3DXVECTOR2(0.0f, 0.25f);   m_tempTextureUV.push_back(v.t); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, -1.0f);   v.t = D3DXVECTOR2(0.25f, 0.0f);   m_tempTextureUV.push_back(v.t); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -1.0f, -1.0f);  v.t = D3DXVECTOR2(0.25f, 0.25f);  m_tempTextureUV.push_back(v.t); m_vecVertex.push_back(v);

	m_pEffect = g_pShader->LoadShader("light.fx");
	m_pTexture = g_pTextureManager->GetTexture(effectName);

	m_iFramenum = frameNum;
	
}
void cEffect::Update(bool _OnOff)
{
	OnOff = _OnOff;
	if (OnOff)
	{
		f_timer += g_pTimeManager->GetDeltaTime();

		if (f_timer > 0.05f)
		{

			if (f_UVx >= 3 && f_UVy >= 3)
			{
				OnOff = false;
				f_UVx = 0;
				f_UVy = 0;

				for (int i = 0; i < m_vecVertex.size(); i++)
				{
					m_vecVertex[i].t = m_tempTextureUV[i];
				}
			}
			if (f_UVy < m_iFramenum)
			{
				++f_UVy;
				for (int i = 0; i < m_vecVertex.size(); i++)
				{
					m_vecVertex[i].t += {0.f, 0.25f};
				}
			}
			else if (f_UVx < m_iFramenum)
			{
				++f_UVx;
				f_UVy = 0;
				for (int i = 0; i < m_vecVertex.size(); i++)
				{
					m_vecVertex[i].t.x += 0.25f;
					m_vecVertex[i].t.y = m_tempTextureUV[i].y;
				}
			}


			f_timer = 0.f;
		}

	}
}
void cEffect::Render(D3DXVECTOR3* Position, D3DXMATRIX* Rotation, D3DXVECTOR3* Eye)
{
	if (OnOff)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);


		D3DXMATRIXA16 matWorld, matView, matProjection, matVP, matS, matT, matR;
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);
		//D3DXMatrixRotationY(&matR, angle);
		D3DXVECTOR3 temp = *Position;
		D3DXMatrixTranslation(&matT,
			temp.x,
			temp.y,
			temp.z);

		matVP = matView * matProjection;
		D3DXMatrixScaling(&matS, 60, 60, 0);


		//D3DXMatrixInverse(&matWorld, 0, &matView);
		//D3DXMatrixInverse(&matWorld, 0, &matView);

		matWorld = matS *(*Rotation) *matT;

		//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		// 쉐이더 전역변수들을 설정
		D3DXVECTOR4 m_Eye(0,0,0, 1.f);
		if (Eye) D3DXVECTOR4 m_Eye(*Eye, 1.f);
		m_pEffect->SetVector("fvLightPosition", &D3DXVECTOR4(-100, -100, -100, 1.f));
		m_pEffect->SetVector("fvEyePosition", &m_Eye);


		m_pEffect->SetMatrix("matWorld", &matWorld);
		m_pEffect->SetMatrix("matView", &matView);

		m_pEffect->SetMatrix("matViewProjection", &matVP);

		m_pEffect->SetVector("fvAmbient", &D3DXVECTOR4(0.368f, 0.368f, 0.368f, 1.f));
		m_pEffect->SetVector("fvDiffuse", &D3DXVECTOR4(0.88f, 0.88f, 0.88f, 1.f));
		m_pEffect->SetVector("fvSpecular", &D3DXVECTOR4(0.49f, 0.49f, 0.49f, 1.f));

		m_pEffect->SetFloat("fSpecularPower", 10);

		m_pEffect->SetTexture("base_Tex", m_pTexture);

		g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
		UINT numPasses = 0;
		m_pEffect->Begin(&numPasses, NULL);


		for (UINT i = 0; i < numPasses; ++i)
		{
			m_pEffect->BeginPass(i);

			g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
				m_vecVertex.size() / 3,
				&m_vecVertex[0],
				sizeof(ST_PT_VERTEX));

			m_pEffect->EndPass();
		}

		m_pEffect->End();
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	}
}