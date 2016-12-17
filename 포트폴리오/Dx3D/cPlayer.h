#pragma once

class cSkinnedMesh;
class cOBB;


class cPlayer
{
private:
	RECT						rc;
	cSkinnedMesh*				m_pPlayer;
	D3DXMATRIXA16				m_Position;

	ST_OBB						m_pPlayerBox;
	cOBB*						m_pOBB;
	LPDIRECT3DTEXTURE9			m_Tblood;
	LPD3DXSPRITE				m_pSprite;
	D3DXIMAGE_INFO				m_stImageInfo;
public:
	cPlayer();
	~cPlayer();

	void SetUp();
	void Update(D3DXMATRIXA16* pmat);
	void Render();
	void Blood();
	void SetAni(int num);
	ST_OBB* GetPlayerBox() { return &m_pPlayerBox; }
	
};

