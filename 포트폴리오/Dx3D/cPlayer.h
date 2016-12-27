#pragma once

class cSkinnedMesh;
class cOBB;



class cPlayer
{
private:
	RECT						rc;
	cSkinnedMesh*				m_pPlayer;
	cSkinnedMesh*				m_pGun[5];
	int							m_iGunBullet[5];
	int							m_iCurrentBullet[5];
	int							m_iGunBulletFull[5];
	D3DXMATRIXA16				m_Position;
	

	
	//GUN_NAME					m_eGunName;


	ST_OBB						m_pPlayerBox;
	cOBB*						m_pOBB;
	LPDIRECT3DTEXTURE9			m_Tblood;
	LPD3DXSPRITE				m_pSprite;
	D3DXIMAGE_INFO				m_stImageInfo;
	float						m_timer;
	D3DXMATRIXA16				m_matT;
	bool						m_bZoomIn;
	bool						m_bZoomOut;
	SYNTHESIZE(GUN_NAME, m_eGunName, PlayerGun);
public:
	cPlayer();
	~cPlayer();

	void SetUp();
	void Update(D3DXMATRIXA16* pmat);
	void Render();
	void Blood();
	void SetAni(int num);

	bool GetZoomIn() { return m_bZoomIn; }
	ST_OBB* GetPlayerBox() { return &m_pPlayerBox; }
	void fireBullet();
	int GetBullet();
	int GetMaxBullet();
	void Reload();
	//GUN_NAME GetPlayerGun() { return m_eGunName; }
	
};

