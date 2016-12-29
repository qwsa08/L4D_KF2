#pragma once
class cCredit
{
private:
	LPD3DXSPRITE		m_pSprite;
	LPDIRECT3DTEXTURE9	m_pTexture;
	RECT				m_Rect;
	int					m_nScroll;

public:
	cCredit();
	~cCredit();

	void Setup();
	void Update();
	void Render();
};

