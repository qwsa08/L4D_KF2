#pragma once


class cOBB;

class cMapXfile 
{
private:
	LPD3DXMESH							m_pShotgun;
	LPD3DXMESH							m_pBullpup;
	LPD3DXMESH							m_pHeal;
	
	std::vector<D3DMATERIAL9>			m_pShotGunMtl;
	std::vector<D3DMATERIAL9>			m_pBullpupMtl;
	std::vector<D3DMATERIAL9>			m_pHealMtl;

	std::vector<LPDIRECT3DTEXTURE9>		m_pShotGunTex;
	std::vector<LPDIRECT3DTEXTURE9>		m_pBullpupTex;
	std::vector<LPDIRECT3DTEXTURE9>		m_pHealTex;
	ST_OBB								BoundingBox[3];
	cOBB*								_OBB[3];
	std::vector<cOBB*>					m_vOBB;
	D3DXVECTOR3							_min, _max;
	LPD3DXEFFECT						m_pOutLineShader;

	D3DXMATRIXA16 matS, matR, matT;
	D3DXMATRIXA16 matShotgun, matBullpup, matHeal;
public:
	cMapXfile();
	virtual ~cMapXfile();

	LPD3DXMESH MeshXFileLoad(
		char* szFilename, 
		std::vector<D3DMATERIAL9>* Mtrls,
		std::vector<LPDIRECT3DTEXTURE9>* Textures);
	//void Render();

	void PickWeaponLoad();

	
	ST_OBB*			   GetBoundingBox() { return BoundingBox; }
	void Render(IN D3DXVECTOR4* LightPosition, IN D3DXVECTOR4* LightDirection);
	void Render();

	void PickWeaponRender(
		std::vector<D3DMATERIAL9> vecMtl,
		std::vector<LPDIRECT3DTEXTURE9> vecTex,
		LPD3DXEFFECT Shader, LPD3DXMESH Mesh,
		D3DXMATRIX World);
};

