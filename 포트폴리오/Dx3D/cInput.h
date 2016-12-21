#pragma once
#include "cMouse.h"
#include "cKeyBoard.h"


//class iKeyState;
class cInput
{
private:
	SINGLETONE(cInput);

private:
	LPDIRECTINPUT8			m_pInput;

	cMouse*					m_pMouse;
	cKeyBoard*				m_pKeyboard;

public:
	cMouse*		GetMouse() { return m_pMouse; }
	cKeyBoard*	GetKeyBoard() { return m_pKeyboard; }

public:
	HRESULT		Setup(HINSTANCE hInst);
	void		Update();
	void		Release();
	void		EndFrame();


};

#define MOUSE cInput::GetInstance()->GetMouse()
#define KEYBOARD cInput::GetInstance()->GetKeyBoard()
