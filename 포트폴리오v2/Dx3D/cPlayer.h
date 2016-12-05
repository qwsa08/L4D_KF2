#pragma once
class cSkinnedMesh;

class cPlayer
{
private:
	cSkinnedMesh*		m_player;
	D3DXMATRIXA16		m_Position;
public:
	cPlayer();
	~cPlayer();

	void SetUp();
	void Update(D3DXMATRIXA16* pmat);
	void Render();
};

