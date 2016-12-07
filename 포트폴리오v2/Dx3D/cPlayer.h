#pragma once
class cSkinnedMesh;
class cOBB;

class cPlayer
{
private:
	cSkinnedMesh*		m_player;
	D3DXMATRIXA16		m_Position;

	ST_OBB				m_pPlayerBox;


	cOBB*				m_test;
public:
	cPlayer();
	~cPlayer();

	
	void SetUp();
	void Update(D3DXMATRIXA16* pmat);
	void Render();
	ST_OBB* GetPlayerBox();
};

