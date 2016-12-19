#pragma once

class cSkinnedMesh;
class cOBB;

enum GUN_NAME
{
	HANDGUN,
	BUSTER,
	KNIFE,
	SHOT,
	HEAL
};


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

