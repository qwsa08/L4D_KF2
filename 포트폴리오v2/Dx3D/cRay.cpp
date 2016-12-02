#include "StdAfx.h"
#include "cRay.h"


cRay::cRay(void)
	: m_vRayPos(0, 0, 0)
	, m_vRayDir(0, 0, 1)
{
}


cRay::~cRay(void)
{
}

cRay cRay::RayAtViewSpace( int x, int y )
{
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);

	D3DXMATRIXA16 matProj;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	cRay r;
	r.m_vRayPos = D3DXVECTOR3(0, 0, 0);
	r.m_vRayDir.x = ( 2.0f * x / vp.Width  - 1.0f) / matProj._11; 
	r.m_vRayDir.y = (-2.0f * y / vp.Height + 1.0f) / matProj._22;
	r.m_vRayDir.z = 1.0f;
	return r;
}

cRay cRay::RayAtWorldSpace( int x, int y )
{
	cRay r = cRay::RayAtViewSpace(x, y);

	D3DXMATRIXA16 matView, matInvView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInvView, 0, &matView);
	D3DXVec3TransformNormal(&r.m_vRayDir, &r.m_vRayDir, &matInvView);
	D3DXVec3TransformCoord(&r.m_vRayPos, &r.m_vRayPos, &matInvView);
	return r;
}

bool cRay::IsPicked( ST_SPHERE& s )
{
	D3DXVECTOR3 vLocalRayPos = m_vRayPos - s.vCenter;
	// Q.V * Q.V - V.V * (Q.Q - r*r);
	float qv = D3DXVec3Dot(&vLocalRayPos, &m_vRayDir);
	float qq = D3DXVec3Dot(&vLocalRayPos, &vLocalRayPos);
	float vv = D3DXVec3Dot(&m_vRayDir, &m_vRayDir);
	float rr = s.fRadius * s.fRadius;
	return qv * qv - vv * (qq - rr) > 0.0f;
}
