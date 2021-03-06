#pragma once

class iMap;

class cCrtController
{
private:
	float						m_fSpeed;
	D3DXVECTOR3					m_vPosition;
	D3DXMATRIXA16				m_matWorld;
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vDirection, Direction);
	POINT						m_ptPrevMouse;
	float						m_fAngleX;
	float						m_fAngleY;

	D3DXMATRIXA16				m_Rotation;
	SYNTHESIZE(float, m_fSensitivity, Sensitivity);
public:
	cCrtController(void);
	~cCrtController(void);

	void Setup();
	void Update(iMap* pMap , D3DXVECTOR3* monLocation = NULL);
	D3DXVECTOR3* GetPosition()
	{
		return &m_vPosition;
	}
	D3DXMATRIXA16* GetWorldTM()
	{
		return &m_matWorld;
	}

	D3DXMATRIXA16 GetRotation()
	{
		return m_Rotation;
	}
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

