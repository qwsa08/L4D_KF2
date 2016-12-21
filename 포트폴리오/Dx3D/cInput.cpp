#include "stdafx.h"
#include "cInput.h"


cInput::cInput()
	: m_pInput(NULL)
	, m_pMouse(NULL)
	, m_pKeyboard(NULL)
{
	//	m_KeyboardState[256] = { '0', };
}


cInput::~cInput()
{
}


HRESULT cInput::Setup(HINSTANCE hInst)
{
	//	ZeroMemory(&m_MouseState, sizeof(DIMOUSESTATE));

	if (FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&m_pInput, NULL)))
	{
		//MSGBOX("인풋장치 생성 실패");
		return E_FAIL;
	}

	/*if (FAILED(SetupMouse()))
	{
	MSGBOX("마우스 초기화 실패");
	return E_FAIL;
	}

	if (FAILED(SetupKeyboard()))
	{
	MSGBOX("키보드 초기화 실패");
	return E_FAIL;
	}*/

	m_pMouse = new cMouse();
	if (FAILED(m_pMouse->Setup(m_pInput)))
	{
		//MSGBOX("마우스 초기화 실패");
		return E_FAIL;
	}

	m_pKeyboard = new cKeyBoard();
	if (FAILED(m_pKeyboard->Setup(m_pInput)))
	{
		//MSGBOX("키보드 초기화 실패");
		return E_FAIL;
	}

	return S_OK;
}


void cInput::Update()
{
	if (m_pMouse)
		m_pMouse->Update();

	if (m_pKeyboard)
		m_pKeyboard->Update();
}


void cInput::Release()
{
	if (m_pMouse)
		SAFE_RELEASE(m_pMouse);

	if (m_pKeyboard)
		SAFE_RELEASE(m_pKeyboard);

	SAFE_RELEASE(m_pInput);

	//cSingleton::Release();
}


void cInput::EndFrame()
{
	m_pMouse->EndFrame();
	m_pKeyboard->EndFrame();
}