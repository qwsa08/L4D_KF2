#include "stdafx.h"
#include "cMouse.h"


cMouse::cMouse()
	: m_lWheelVariation(0)
{
	POINT pWinPos;
	pWinPos.x = 100; //GetWindowWidth() / 2;
	pWinPos.y = 100; //GetWindowHeight() / 2;
	ClientToScreen(g_hWnd, &pWinPos);

	//SetCursorPos(pWinPos.x, pWinPos.y);
	m_FixPos = pWinPos;
}


cMouse::~cMouse()
{
}


HRESULT cMouse::Setup(LPDIRECTINPUT8 pInput)
{
	ZeroMemory(&m_MouseState, sizeof(DIMOUSESTATE));
	m_lWheelVariation = 0;

	if (pInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL) == IDCANCEL)
	{
		//	MSGBOX("마우스 생성 실패");
		return E_FAIL;
	}

	if (m_pMouse->SetCooperativeLevel(g_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE) == IDCANCEL)
	{
		//	MSGBOX("마우스 생성 실패2");
		return E_FAIL;
	}

	if (m_pMouse->SetDataFormat(&c_dfDIMouse) == IDCANCEL)
	{
		//	MSGBOX("마우스 생성 실패3");
		return E_FAIL;
	}

	for (int i = 0; i < MOUSEBTN_END; ++i)
	{
		this->SetKeyDown((MOUSEBUTTON)i, false);
		this->SetKeyUp((MOUSEBUTTON)i, false);
	}

	return S_OK;
}


void cMouse::Update()
{
	HRESULT hr = m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseState);

	if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
		m_pMouse->Acquire();
}


void cMouse::Release()
{
	m_pMouse->Unacquire();
	SAFE_RELEASE(m_pMouse);
}


void cMouse::EndFrame()
{
	m_bSameFrame = false;
}


POINT cMouse::GetWindowPos()
{
	POINT ptPosition;
	GetCursorPos(&ptPosition);
	ScreenToClient(g_hWnd, &ptPosition);

	return ptPosition;
}


bool cMouse::IsOnceKeyDown(MOUSEBUTTON key)
{
	if (m_MouseState.rgbButtons[key] & 0x80)
	{
		if (!this->GetKeyDown()[key])
		{
			this->SetKeyDown(key, true);
			return true;
		}
	}
	else
	{
		this->SetKeyDown(key, false);
	}
	return false;
}


bool cMouse::IsStayKeyDown(MOUSEBUTTON key)
{
	if (m_MouseState.rgbButtons[key] & 0x80)
		return true;
	return false;
}


int cMouse::GetWheelVariation()
{
	return m_MouseState.lZ;
}


bool cMouse::IsOnceKeyUp(MOUSEBUTTON key)
{
	if (m_MouseState.rgbButtons[key] & 0x80)
		SetKeyUp(key, true);
	else
	{
		if (this->GetKeyUp()[key])
		{
			this->SetKeyUp(key, false);
			return true;
		}
	}
	return false;
}


long cMouse::GetWheelCount()
{
	return m_lWheelVariation += m_MouseState.lZ;
}


POINT cMouse::GetMouseVariation()
{
	POINT p;
	p.x = m_MouseState.lX;
	p.y = m_MouseState.lY;

	return p;
}