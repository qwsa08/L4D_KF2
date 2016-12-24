#pragma once
class cMapXfile;
class cSky
{
private:
	LPD3DXMESH							m_pSky;
	std::vector<D3DMATERIAL9>			m_vSkyMtl;
	std::vector<LPDIRECT3DTEXTURE9>		m_vSkyTxt;
public:
	cSky();
	~cSky();

	void SetUp();
	void Render();
};

