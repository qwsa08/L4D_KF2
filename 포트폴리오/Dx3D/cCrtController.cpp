#include "StdAfx.h"
#include "cCrtController.h"
#include "iMap.h"

cCrtController::cCrtController(void)
	: m_vPosition(0, 0, 0)
	, m_vDirection(0, 0, 1)
	, m_fSpeed(4.f)
	, m_fAngle(0.0f)
{
}


cCrtController::~cCrtController(void)
{
}

void cCrtController::Setup()
{

}

void cCrtController::Update(iMap* pMap /*= NULL*/)
{
	if(GetKeyState('A') & 0x8000)
	{
		m_fAngle -= 0.1f;
	}

	if(GetKeyState('D') & 0x8000)
	{
		m_fAngle += 0.1f;
	}

	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, m_fAngle);
	
	D3DXVECTOR3 vPosition = m_vPosition;

	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(0, 0, 1), &matR);
	if(GetKeyState('W') & 0x8000)
	{
		vPosition = m_vPosition - (m_vDirection * m_fSpeed);
	}

	if(GetKeyState('S') & 0x8000)
	{
		vPosition = m_vPosition + (m_vDirection * m_fSpeed);
	}

	if (pMap)
	{
		if(pMap->GetHeight(vPosition.x, vPosition.y, vPosition.z))
			m_vPosition = vPosition;
	}
	else
	{
		m_vPosition = vPosition;
	}

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT;
}
