#include "StdAfx.h"
#include "cCamera.h"


cCamera::cCamera(void)
	: m_vEye(0, 10, 0)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_isLButtonDown(false)
	, m_fAngleX(0.0f)
	, m_fAngleY(0.0f)
	, m_fDistance(10.0f)
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
	
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1, 50000);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void cCamera::Update(D3DXVECTOR3* pTarget, D3DXVECTOR3* pDirection)
{
	m_vEye = D3DXVECTOR3(0, 0, -m_fDistance);
	m_vLookAt = D3DXVECTOR3(10, 10, 10);

	D3DXMATRIXA16 matRX, matRY, mat;
	D3DXMatrixRotationX(&matRX, m_fAngleX);
	D3DXMatrixRotationY(&matRY, m_fAngleY);
	
	mat = matRX * matRY;
	
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &mat);

	if (pTarget)
	{
		m_vEye = *pTarget + D3DXVECTOR3(0, 30, 0);
		m_vLookAt = m_vEye + *pDirection;
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

void cCamera::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch(message)
	{
	case WM_LBUTTONUP:
		{
			m_isLButtonDown = false;
		}
		break;
	case WM_MOUSEMOVE:
		{
			m_ptMouse.x = LOWORD(lParam);
			m_ptMouse.y = HIWORD(lParam);
		}
		break;
	case WM_MOUSEWHEEL:
		{
			int n = GET_WHEEL_DELTA_WPARAM(wParam);
			m_fDistance -= n / 5.f;
		}
		break;
	}
}
