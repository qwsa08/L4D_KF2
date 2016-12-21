#pragma once

#define KEYMAX		256
#define KEYDOWN(State, Key) (State[Key] & 0x80)

class cKeyBoard
{
private:
	LPDIRECTINPUTDEVICE8	m_pKeyboard;
	UINT8		 			m_KeyboardState[KEYMAX];
	bitset<KEYMAX>			m_bKeyDown;
	bitset<KEYMAX>			m_bKeyUp;

	bool					m_bSameFrame;

public:
	bitset<KEYMAX> GetKeyDown() { return m_bKeyDown; }
	bitset<KEYMAX> GetKeyUp() { return m_bKeyUp; }
	void SetKeyDown(int key, bool state) { m_bKeyDown.set(key, state); }
	void SetKeyUp(int key, bool state) { m_bKeyUp.set(key, state); }

public:
	bool IsOnceKeyDown(int key);
	bool IsStayKeyDown(int key);
	bool IsOnceKeyUp(int key);
	bool IsToggleKey(int key);

public:
	HRESULT		Setup(LPDIRECTINPUT8 pInput);
	void		Update();
	void		Release();
	void		EndFrame();

public:
	cKeyBoard();
	~cKeyBoard();
};

