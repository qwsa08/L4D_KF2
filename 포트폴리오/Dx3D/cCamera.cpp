#include "StdAfx.h"
#include "cCamera.h"


cCamera::cCamera(void)
	: m_vEye(0, 0, 0)
	, m_vLookAt(0, 0, -10)
	, m_vUp(0, 1, 0)
	, m_fDistance(0.f)
{
}

cCamera::~cCamera(void)
{
}

void cCamera::Setup()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);
	
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.f, 2000.f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void cCamera::Update(D3DXVECTOR3* pTarget, D3DXVECTOR3* pDirection)
{
	m_vEye = D3DXVECTOR3(0, 0, 0);
	m_vLookAt = D3DXVECTOR3(0, 0, -10);

	if (pTarget)
	{
		m_vEye = m_vEye + *pTarget;
		m_vLookAt = m_vEye + *pDirection;
	}

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		m_vEye += D3DXVECTOR3(0, 100, 0);
	}
	


 	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);

}

D3DXMATRIXA16* cCamera::GetViewMatrix()
{
	return &m_matView;
}

D3DXMATRIXA16* cCamera::GetProjMatrix()
{
	return &m_matProj;
}
void cCamera::Clipping(D3DXVECTOR3 Eye,D3DXVECTOR3 pDirection)
{
}

void cCamera::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
}
