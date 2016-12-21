#pragma once

class cMouse
{
private:
	LPDIRECTINPUTDEVICE8	m_pMouse;
	DIMOUSESTATE			m_MouseState;
	bitset<MOUSEBTN_END>	m_MouseDown;
	bitset<MOUSEBTN_END>	m_MouseUp;

	long					m_lWheelVariation;

	POINT					m_FixPos;
	bool					m_bSameFrame;

public:
	bitset<MOUSEBTN_END> GetKeyDown() { return m_MouseDown; }
	bitset<MOUSEBTN_END> GetKeyUp() { return m_MouseUp; }
	void SetKeyDown(MOUSEBUTTON key, bool state) { m_MouseDown.set(key, state); }
	void SetKeyUp(MOUSEBUTTON key, bool state) { m_MouseUp.set(key, state); }

public:
	HRESULT			Setup(LPDIRECTINPUT8 pInput);
	void			Update();
	void			Release();
	void			EndFrame();

public:
	POINT			GetWindowPos();
	bool			IsOnceKeyDown(MOUSEBUTTON key);
	bool			IsStayKeyDown(MOUSEBUTTON key);
	bool			IsOnceKeyUp(MOUSEBUTTON key);
	int				GetWheelVariation();
	long			GetWheelCount();

	POINT			GetFixPos() { return m_FixPos; }
	void			SetFixPos(POINT _fixPos){ m_FixPos = _fixPos; }

	DIMOUSESTATE*	GetMouseState() { return &m_MouseState; }
	POINT			GetMouseVariation();

public:
	cMouse();
	~cMouse();
};

