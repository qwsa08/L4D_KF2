#include "stdafx.h"
#include "cKeyBoard.h"


cKeyBoard::cKeyBoard()
	: m_bSameFrame(false)
{
}


cKeyBoard::~cKeyBoard()
{
}


HRESULT cKeyBoard::Setup(LPDIRECTINPUT8 pInput)
{
	if (pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL) == IDCANCEL)
	{
		//MSGBOX("키보드 생성 실패");
		return E_FAIL;
	}

	if (m_pKeyboard->SetCooperativeLevel(g_hWnd, DISCL_BACKGROUND | DISCL_EXCLUSIVE) == IDCANCEL)
	{
		//MSGBOX("키보드 생성 실패2");
		return E_FAIL;
	}

	if (m_pKeyboard->SetDataFormat(&c_dfDIKeyboard) == IDCANCEL)
	{
		//MSGBOX("키보드 생성 실패3");
		return E_FAIL;
	}

	for (int i = 0; i < KEYMAX; ++i)
	{
		this->SetKeyDown(i, false);
		this->SetKeyUp(i, false);
	}

	return S_OK;
}


void cKeyBoard::Update()
{
	HRESULT hr = m_pKeyboard->GetDeviceState(sizeof(UINT8) * 256, m_KeyboardState);

	if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
		m_pKeyboard->Acquire();
}


void cKeyBoard::Release()
{
	m_pKeyboard->Unacquire();
	SAFE_RELEASE(m_pKeyboard);
}


void cKeyBoard::EndFrame()
{
	m_bSameFrame = false;
}


bool cKeyBoard::IsOnceKeyDown(int key)
{
	if (KEYDOWN(m_KeyboardState, key))
	{
		if (!this->GetKeyDown()[key])
		{
			this->SetKeyDown(key, true);
			m_bSameFrame = true;
			return true;
		}
		else if (m_bSameFrame)
			return true;
	}
	else
	{
		this->SetKeyDown(key, false);
	}
	return false;
}


bool cKeyBoard::IsStayKeyDown(int key)
{
	if (KEYDOWN(m_KeyboardState, key))
		return true;
	return false;
}


bool cKeyBoard::IsOnceKeyUp(int key)
{
	if (KEYDOWN(m_KeyboardState, key))
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
bool cKeyBoard::IsToggleKey(int key)
{
	if (GetKeyState(key))
	{
		return true;
	}
	return false;

}