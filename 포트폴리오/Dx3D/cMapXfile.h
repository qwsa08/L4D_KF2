#pragma once

#include "iMap.h"

class cMapXfile : public iMap
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

	LPD3DXEFFECT						m_pOutLineShader;
public:
	cMapXfile();
	virtual ~cMapXfile();

	LPD3DXMESH MeshXFileLoad(
		char* szFilename, 
		std::vector<D3DMATERIAL9>* Mtrls,
		std::vector<LPDIRECT3DTEXTURE9>* Textures);
	//void Render();

	void PickWeaponLoad();

	virtual void Render(IN D3DXVECTOR4* LightPosition, IN D3DXVECTOR4* LightDirection) override;
	virtual void Render();
	virtual bool GetHeight(IN float x, OUT float& y, IN float z) override;

	void PickWeaponRender(
		std::vector<D3DMATERIAL9> vecMtl,
		std::vector<LPDIRECT3DTEXTURE9> vecTex,
		LPD3DXEFFECT Shader, LPD3DXMESH Mesh,
		D3DXMATRIX World);
};

