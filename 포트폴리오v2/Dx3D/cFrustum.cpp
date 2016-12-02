#include "StdAfx.h"
#include "cFrustum.h"


cFrustum::cFrustum(void)
{
	int n = 0;
	m_aProjVertex[n++] = D3DXVECTOR3(-1, 1, 0);
	m_aProjVertex[n++] = D3DXVECTOR3( 1, 1, 0);
	m_aProjVertex[n++] = D3DXVECTOR3( 1,-1, 0);
	m_aProjVertex[n++] = D3DXVECTOR3(-1,-1, 0);
	m_aProjVertex[n++] = D3DXVECTOR3(-1, 1, 1);
	m_aProjVertex[n++] = D3DXVECTOR3( 1, 1, 1);
	m_aProjVertex[n++] = D3DXVECTOR3( 1,-1, 1);
	m_aProjVertex[n++] = D3DXVECTOR3(-1,-1, 1);
}

cFrustum::~cFrustum(void)
{
}

void cFrustum::Update()
{
	D3DXMATRIXA16 matView, matInvView, matProj, matInvProj, mat;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInvProj, 0, &matProj);
	D3DXMatrixInverse(&matInvView, 0, &matView);

	mat = matInvProj * matInvView;

	D3DXVECTOR3 aFrustumVertex[8];
	for (int i = 0; i < 8; ++i)
	{
		D3DXVec3TransformCoord(&aFrustumVertex[i], &m_aProjVertex[i], &mat);
	}

	int n = 0;
	D3DXPlaneFromPoints(&m_aPlane[n++], 
		&aFrustumVertex[0],
		&aFrustumVertex[1],
		&aFrustumVertex[2]);

	D3DXPlaneFromPoints(&m_aPlane[n++], 
		&aFrustumVertex[5],
		&aFrustumVertex[4],
		&aFrustumVertex[7]);

	D3DXPlaneFromPoints(&m_aPlane[n++], 
		&aFrustumVertex[4],
		&aFrustumVertex[0],
		&aFrustumVertex[3]);

	D3DXPlaneFromPoints(&m_aPlane[n++], 
		&aFrustumVertex[1],
		&aFrustumVertex[5],
		&aFrustumVertex[6]);

	D3DXPlaneFromPoints(&m_aPlane[n++], 
		&aFrustumVertex[4],
		&aFrustumVertex[5],
		&aFrustumVertex[0]);

	D3DXPlaneFromPoints(&m_aPlane[n++], 
		&aFrustumVertex[3],
		&aFrustumVertex[2],
		&aFrustumVertex[6]);
}

bool cFrustum::IsIn( ST_SPHERE* pSphere )
{
	for (int i = 0; i < 6; ++i)
	{
		if(D3DXPlaneDotCoord(&m_aPlane[i], &pSphere->vCenter) > pSphere->fRadius)
			return false;
	}
	return true;
}
