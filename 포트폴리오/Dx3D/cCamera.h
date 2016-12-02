#pragma once
class cCamera
{
private:
	D3DXVECTOR3				m_vEye;
	D3DXVECTOR3				m_vLookAt;
	D3DXVECTOR3				m_vUp;
	D3DXMATRIXA16			m_matView;
	D3DXMATRIXA16			m_matProj;
	POINT					m_ptPrevMouse;
	bool					m_isLButtonDown;
	float					m_fAngleX;
	float					m_fAngleY;
	float					m_fDistance;

public:
	cCamera(void);
	~cCamera(void);

	void Setup();
	void Update(D3DXVECTOR3* pTarget);

	D3DXMATRIXA16* GetViewMatrix();
	D3DXMATRIXA16* GetProjMatrix();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

