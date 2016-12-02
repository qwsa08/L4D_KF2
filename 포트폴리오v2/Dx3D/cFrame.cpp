#include "StdAfx.h"
#include "cFrame.h"

cFrame::cFrame(void)
	: m_pMtlTex(NULL)
	, m_pVB(NULL)
	, m_nNumTri(0)
{
	D3DXMatrixIdentity(&m_matLocal);
	D3DXMatrixIdentity(&m_matWorld);
}

cFrame::~cFrame(void)
{
	SAFE_RELEASE(m_pVB);
	for each(auto p in m_vecChild)
	{
		SAFE_RELEASE(p);
	}
	SAFE_RELEASE(m_pMtlTex);
}

void cFrame::Update( int nKeyFrame, D3DXMATRIXA16* pParent )
{
	D3DXMATRIXA16 matT, matR;
	
	LocalT(nKeyFrame, matT);
	LocalR(nKeyFrame, matR);
	
	m_matLocal = matR * matT;

	m_matWorld = m_matLocal;

	if (pParent)
	{
		m_matWorld = m_matLocal * *pParent;
	}

	for each(auto p in m_vecChild)
	{
		p->Update(nKeyFrame, &m_matWorld);
	}
}

void cFrame::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	if(m_pMtlTex)
	{
		g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PNT_VERTEX));
		g_pD3DDevice->SetTexture(0, m_pMtlTex->GetTexture());
		g_pD3DDevice->SetMaterial(&m_pMtlTex->GetMtl());
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_nNumTri);
	}

	for each(auto p in m_vecChild)
	{
		p->Render();
	}
}

void cFrame::AddChild( cFrame* pChild )
{
	if(pChild)
	{
		SAFE_ADD_REF(pChild);
		m_vecChild.push_back(pChild);
	}
}

void cFrame::Destroy()
{
	
}

void cFrame::CalcLocalTM( D3DXMATRIXA16* pParent )
{
	m_matLocal = m_matWorld;

	if (pParent)
	{
		//LOCAL = World * IPW
		D3DXMATRIXA16 matInvParent;
		D3DXMatrixInverse(&matInvParent, 0, pParent);
		m_matLocal = m_matWorld * matInvParent;
	}

	for each(auto p in m_vecChild)
	{
		p->CalcLocalTM(&m_matWorld);
	}
}

void cFrame::LocalT( int nKeyFrame, D3DXMATRIXA16& mat )
{
	D3DXMatrixIdentity(&mat);

	if (m_vecPosTrack.empty())
	{
		mat._41 = m_matLocal._41;
		mat._42 = m_matLocal._42;
		mat._43 = m_matLocal._43;
	}
	else if (nKeyFrame <= m_vecPosTrack.front().n)
	{
		mat._41 = m_vecPosTrack.front().p.x;
		mat._42 = m_vecPosTrack.front().p.y;
		mat._43 = m_vecPosTrack.front().p.z;
	}
	else if (nKeyFrame >= m_vecPosTrack.back().n)
	{
		mat._41 = m_vecPosTrack.back().p.x;
		mat._42 = m_vecPosTrack.back().p.y;
		mat._43 = m_vecPosTrack.back().p.z;
	}
	else
	{
		int nNext = -1;
		int nPrev = -1;
		for (size_t i = 0; i < m_vecPosTrack.size(); ++i)
		{
			if(nKeyFrame < m_vecPosTrack[i].n)
			{
				nNext = i;
				nPrev = i - 1;
				break;
			}
		}

		assert(nPrev >= 0 && "세상에 이런일이..");

		float t = (nKeyFrame - m_vecPosTrack[nPrev].n) / 
			(float)(m_vecPosTrack[nNext].n - m_vecPosTrack[nPrev].n);
		D3DXVECTOR3 p(0, 0, 0);
		D3DXVec3Lerp(&p, &m_vecPosTrack[nPrev].p, &m_vecPosTrack[nNext].p, t);
		mat._41 = p.x;
		mat._42 = p.y;
		mat._43 = p.z;
	}
}

void cFrame::LocalR( int nKeyFrame, D3DXMATRIXA16& mat )
{
	D3DXMatrixIdentity(&mat);

	if (m_vecRotTrack.empty())
	{
		mat = m_matLocal;
		mat._41 = 0.0f;
		mat._42 = 0.0f;
		mat._43 = 0.0f;
	}
	else if (nKeyFrame <= m_vecRotTrack.front().n)
	{
		D3DXMatrixRotationQuaternion(&mat, &m_vecRotTrack.front().q);
	}
	else if (nKeyFrame >= m_vecRotTrack.back().n)
	{
		D3DXMatrixRotationQuaternion(&mat, &m_vecRotTrack.back().q);
	}
	else
	{
		int nNext = -1;
		int nPrev = -1;
		for (size_t i = 0; i < m_vecRotTrack.size(); ++i)
		{
			if(nKeyFrame < m_vecRotTrack[i].n)
			{
				nNext = i;
				nPrev = i - 1;
				break;
			}
		}

		assert(nPrev >= 0 && "세상에 이런일이..");

		float t = (nKeyFrame - m_vecRotTrack[nPrev].n) / 
			(float)(m_vecRotTrack[nNext].n - m_vecRotTrack[nPrev].n);
		D3DXQUATERNION q;
		D3DXQuaternionSlerp(&q, &m_vecRotTrack[nPrev].q, &m_vecRotTrack[nNext].q, t);
		D3DXMatrixRotationQuaternion(&mat, &q);
	}
}

void cFrame::SetVertex( std::vector<ST_PNT_VERTEX> vecVertex )
{
	g_pD3DDevice->CreateVertexBuffer(
		vecVertex.size() * sizeof(ST_PNT_VERTEX),
		D3DUSAGE_WRITEONLY,
		ST_PNT_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		NULL);

	ST_PNT_VERTEX* pV = NULL;
	m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pVB->Unlock();

	m_nNumTri = vecVertex.size() / 3;
}

