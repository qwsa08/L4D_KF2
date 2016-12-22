#pragma once
class cCamera
{
private:
	D3DXVECTOR3				m_vEye;
	D3DXVECTOR3				m_vLookAt;
	D3DXVECTOR3				m_vUp;
	D3DXMATRIXA16			m_matView;
	D3DXMATRIXA16			m_matProj;
	POINT					m_ptMouse;

	float					m_fDistance;

public:
	cCamera(void);
	~cCamera(void);

	void Setup();
	void Update(D3DXVECTOR3* pTarget, D3DXVECTOR3* pDirection);

	D3DXMATRIXA16* GetViewMatrix();
	D3DXMATRIXA16* GetProjMatrix();

	D3DXVECTOR3 GetEye() { return m_vEye; }
	void Clipping(D3DXVECTOR3 Eye, D3DXVECTOR3 pDirection);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

