#include "StdAfx.h"
#include "cCrtController.h"
#include "iMap.h"

#define SENSITIVITY	0.015f

cCrtController::cCrtController(void)
	: m_vPosition(50, 50, -450)
//	: m_vPosition(1000, -140, 1400)
	, m_vDirection(0, 0, 1)
	, m_fSpeed(4.f)
	, m_fAngleX(0.0f)
	, m_fAngleY(0.0f)
	, m_fSensitivity(1.f)
{
	GetCursorPos(&m_ptPrevMouse);
}


cCrtController::~cCrtController(void)
{
}

void cCrtController::Setup()
{
	
}

void cCrtController::Update(iMap* pMap, D3DXVECTOR3* monLocation)
{
	{	 // 마우스 컨트롤?
		float nDeltaX = (m_ptPrevMouse.x - MOUSE->GetWindowPos().x)/m_fSensitivity;
		float nDeltaY = (m_ptPrevMouse.y - MOUSE->GetWindowPos().y)/m_fSensitivity;
		m_fAngleX += nDeltaY * SENSITIVITY;
		if (m_fAngleX > D3DX_PI / 2.0f - EPSILON)
			m_fAngleX = D3DX_PI / 2.0f - EPSILON;

		if (m_fAngleX < -D3DX_PI / 2.0f + EPSILON)
			m_fAngleX = -D3DX_PI / 2.0f + EPSILON;

		m_fAngleY += nDeltaX * SENSITIVITY;
	}

	D3DXVECTOR3 vPosition = m_vPosition;
	D3DXMATRIXA16 matX, matY, matR, mat;
	D3DXMatrixRotationX(&matX, m_fAngleX);
	D3DXMatrixRotationY(&matY, m_fAngleY);
	matR = matX * matY;

	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(0, 0, 1), &matR);
	
	bool crushPront = false;
	bool crushBack = false;
	bool crushLeft = false;
	bool crushRight = false;

	if (monLocation)
	{
		/*D3DXVECTOR3 vMonLocation; 
		vMonLocation = *monLocation - vPosition;
		D3DXVec3Normalize(&vMonLocation, &vMonLocation);*/
		float crushAngle = D3DXVec3Dot(&m_vDirection, monLocation);
		D3DXVECTOR3 vMonLocation = (*monLocation - m_vDirection);

		//float LRlenght = D3DXVec3Length(&(*monLocation - m_vDirection));
		if (crushAngle > 0) crushPront = true;
		if (crushAngle < 0) crushBack = true;
		if (vMonLocation.x < 0) crushLeft = true;
		if (vMonLocation.x > 0) crushRight = true;
	}
	else
	{
		crushPront = false;
		crushBack = false;
		crushLeft = false;
		crushRight = false;
	}

	D3DXVECTOR3 v(0, 0, 1);
	D3DXMatrixRotationY(&mat, D3DX_PI / 2.0f);
	D3DXVec3TransformNormal(&v, &m_vDirection, &mat);
	D3DXVECTOR3 l(0, 0, 1);
	D3DXMatrixRotationY(&mat, D3DX_PI / 4.0f);
	D3DXVec3TransformNormal(&l, &m_vDirection, &mat);
	D3DXVECTOR3 r(0, 0, 1);
	D3DXMatrixRotationY(&mat, -D3DX_PI / 4.0f);
	D3DXVec3TransformNormal(&r, &m_vDirection, &mat);

	if (g_pKeyManager->isStayKeyDown('W') && g_pKeyManager->isStayKeyDown('A'))
	{
		if(!crushPront) vPosition = m_vPosition + (r * m_fSpeed);
	}
	else if (g_pKeyManager->isStayKeyDown('S') && g_pKeyManager->isStayKeyDown('A'))
	{
		if (!crushBack) vPosition = m_vPosition - (l * m_fSpeed);
	}
	else if (g_pKeyManager->isStayKeyDown('W') && g_pKeyManager->isStayKeyDown('D'))
	{
		if (!crushPront) vPosition = m_vPosition + (l * m_fSpeed);
	}
	else if (g_pKeyManager->isStayKeyDown('S') && g_pKeyManager->isStayKeyDown('D'))
	{
		if (!crushBack) vPosition = m_vPosition - (r * m_fSpeed);
	}
	else if (GetKeyState('W') & 0x8000)
	{
		if (!crushPront) vPosition = m_vPosition + (m_vDirection * m_fSpeed);
	}
	else if (GetKeyState('S') & 0x8000)
	{
		if (!crushBack) vPosition = m_vPosition - (m_vDirection * m_fSpeed);
	}
	else if (GetKeyState('A') & 0x8000)
	{
		if (!crushLeft) vPosition = m_vPosition - (v * m_fSpeed);
	}
	else if(GetKeyState('D') & 0x8000)
	{
		if (!crushRight) vPosition = m_vPosition + (v * m_fSpeed);
	}
	
	if (pMap)
	{
		if (pMap->GetHeight(vPosition.x, vPosition.y, vPosition.z))
		{
			vPosition.y += 70;
			m_vPosition = vPosition;
		}			
	}
	else
	{
		m_vPosition = vPosition;
	}

	

	m_Rotation = matR;	
	
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT;
}

void cCrtController::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
	{
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
		/*POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);

		int nDeltaX = pt.x - m_ptPrevMouse.x;
		int nDeltaY = pt.y - m_ptPrevMouse.y;

		m_fAngleX += nDeltaY * SENSITIVITY;
		if (m_fAngleX > D3DX_PI / 2.0f - EPSILON)
			m_fAngleX = D3DX_PI / 2.0f - EPSILON;

		if (m_fAngleX < -D3DX_PI / 2.0f + EPSILON)
			m_fAngleX = -D3DX_PI / 2.0f + EPSILON;

		m_fAngleY += nDeltaX * SENSITIVITY;

		m_ptPrevMouse = pt;*/
	}
	break;
	default:
	{
		
	}
		break;
	}
}
