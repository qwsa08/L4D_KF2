#pragma once
class cSkinnedMesh;
class cFrustum;

class cZed
{
private:

	cSkinnedMesh*				m_pSkinnedMesh;
	std::vector<cSkinnedMesh*>	m_vecSkinnedMesh;

	cFrustum*					m_pFrustum;
public:
	cZed();
	~cZed();
	
	void SetUp();
	void Update();
	void Render(D3DXMATRIXA16* WorldTM);
};

