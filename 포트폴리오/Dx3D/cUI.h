#pragma once
class cUI
{
private:
	RECT									rc;
	std::vector<LPDIRECT3DTEXTURE9>			m_vTWeapon;
	std::vector<LPDIRECT3DTEXTURE9>			m_vTHP;

	std::vector<LPDIRECT3DTEXTURE9>			m_vTNum;
	//std::vector<LPD3DXSPRITE>				m_vSprite;
	LPD3DXSPRITE							m_pSprite;

	D3DXIMAGE_INFO							m_stImageInfo;
	LPD3DXFONT								m_pFont;
public:
	cUI();
	~cUI();
	void SetUp();
	void Update();
	void HP_Render();
	void Wepon_Render(GUN_NAME _name);
	void Bullet_Render(int currentBullet, int MaxBullet);
};

