#pragma once
class cCrtController;
class cCrossHead
{
private:
	LPD3DXSPRITE				m_pSprite;
	D3DXIMAGE_INFO				m_stImageInfo;
	LPDIRECT3DTEXTURE9			m_pTexture;
	D3DXVECTOR2					m_WithHeight;

	RECT rc;
	RECT rcClient;
public:
	cCrossHead();
	~cCrossHead();
	
	
	void Render();

};

