#pragma once

class cSkinnedMesh;
class iMap;

class cZombie
{
protected:
	std::vector<cSkinnedMesh*>	m_vecSkinnedMesh;
	iMap*						m_pMap;
	D3DXVECTOR3					m_vPosition;

public:
	cZombie();
	virtual ~cZombie();

	virtual void Setup();
	virtual void UpdateAndRender(D3DXMATRIXA16* pmat = NULL, D3DXMATRIXA16* pScal = NULL) = 0;
};

