#include "StdAfx.h"
#include "cCrtController.h"
#include "iMap.h"

cCrtController::cCrtController(void)
	: m_vPosition(0, 0, 0)
	, m_vDirection(0, 0, 1)
	, m_fSpeed(4.f)
	, m_fAngle(0.0f)
	, m_fAngleX(0.0f)
	, m_fAngleY(0.0f)
{
	GetCursorPos(&m_ptPrevMouse);
}


cCrtController::~cCrtController(void)
{
}

void cCrtController::Setup()
{
	
}

void cCrtController::Update(iMap* pMap /*= NULL*/)
{
	D3DXVECTOR3 vPosition = m_vPosition;
	D3DXMATRIXA16 matX, matY, matR, mat;
	D3DXMatrixRotationX(&matX, m_fAngleX);
	D3DXMatrixRotationY(&matY, m_fAngleY);
	matR = matX * matY;

	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(0, 0, 1), &matR);
	//m_vDirection = D3DXVECTOR3(0, 0, 1);
	if (GetKeyState('W') & 0x8000)
	{
		vPosition = m_vPosition + (m_vDirection * m_fSpeed);
	}

	if (GetKeyState('S') & 0x8000)
	{
		vPosition = m_vPosition - (m_vDirection * m_fSpeed);
	}
	//m_vDirection = D3DXVECTOR3(1, 0, 0);
	D3DXVECTOR3 v(0, 0, 1);
	D3DXMatrixRotationY(&mat, D3DX_PI / 2.0f);
	D3DXVec3TransformNormal(&v, &m_vDirection, &mat);
	if(GetKeyState('A') & 0x8000)
	{
		vPosition = m_vPosition - (v * m_fSpeed);
	}

	if(GetKeyState('D') & 0x8000)
	{
		vPosition = m_vPosition + (v * m_fSpeed);
	}
	
	if (pMap)
	{
		if (pMap->GetHeight(vPosition.x, vPosition.y, vPosition.z))
			m_vPosition = vPosition;
	}
	else
	{
		m_vPosition = vPosition;
	}

	//m_vPosition += D3DXVECTOR3(0, 100, 0);

	D3DXMATRIXA16 matT ,matR2;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	D3DXMatrixRotationY(&matR2, D3DX_PI);

	m_matWorld = matY* matR2* matT;
}

void cCrtController::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
	{
		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);

		int nDeltaX = pt.x - m_ptPrevMouse.x;
		int nDeltaY = pt.y - m_ptPrevMouse.y;

		m_fAngleX += nDeltaY * 0.01f;
		if (m_fAngleX > D3DX_PI / 2.0f - EPSILON)
			m_fAngleX = D3DX_PI / 2.0f - EPSILON;

		if (m_fAngleX < -D3DX_PI / 2.0f + EPSILON)
			m_fAngleX = -D3DX_PI / 2.0f + EPSILON;

		m_fAngleY += nDeltaX * 0.01f;

		m_ptPrevMouse = pt;
	}
	break;
	}
}
