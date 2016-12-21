#pragma once

class cSkinnedMesh;
class cOBB;



class cPlayer
{
private:
	RECT						rc;
	cSkinnedMesh*				m_pPlayer;
	cSkinnedMesh*				m_pGun[5];
	D3DXMATRIXA16				m_Position;
	GUN_NAME					m_eGunName;


	ST_OBB						m_pPlayerBox;
	cOBB*						m_pOBB;
	LPDIRECT3DTEXTURE9			m_Tblood;
	LPD3DXSPRITE				m_pSprite;
	D3DXIMAGE_INFO				m_stImageInfo;
	float						m_timer;
	D3DXMATRIXA16				m_matT;
	bool						m_bZoomIn;
	bool						m_bZoomOut;
public:
	cPlayer();
	~cPlayer();

	void SetUp();
	void Update(D3DXMATRIXA16* pmat);
	void Render();
	void Blood();
	void SetAni(int num);
	ST_OBB* GetPlayerBox() { return &m_pPlayerBox; }
	GUN_NAME GetPlayerGun() { return m_eGunName; }
	
};

