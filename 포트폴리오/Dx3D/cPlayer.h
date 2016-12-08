#pragma once

class cSkinnedMesh;
class cOBB;


class cPlayer
{
private:
	cSkinnedMesh*		m_pPlayer;
	D3DXMATRIXA16		m_Position;

	ST_OBB				m_pPlayerBox;
	cOBB*				m_pOBB;
	
public:
	cPlayer();
	~cPlayer();

	void SetUp();
	void Update(D3DXMATRIXA16* pmat);
	void Render();
	ST_OBB* GetPlayerBox() { return &m_pPlayerBox; }
	
};

