#pragma once

#include "iMap.h"

class cMapXfile : public iMap
{
private:
	LPD3DXMESH							m_pShotgun;
	//LPD3DXMESH m_pshotgun;
	//LPD3DXMESH m_pshotgun;
	
	std::vector<D3DMATERIAL9>			m_pShotGunMtl;
	//std::vector<cMtlTex*>				m_pBullpupMtltex;
	//std::vector<cMtlTex*>				m_pHealMtltex;

	std::vector<LPDIRECT3DTEXTURE9>		m_pShotGunTex;
	//std::vector<cMtlTex*>				m_pBullpupMtltex;
	//std::vector<cMtlTex*>				m_pHealMtltex;

	LPD3DXEFFECT						m_pOutLineShader;
public:
	cMapXfile();
	virtual ~cMapXfile();

	LPD3DXMESH MeshXFileLoad(
		char* szFilename, 
		std::vector<D3DMATERIAL9>* Mtrls,
		std::vector<LPDIRECT3DTEXTURE9>* Textures);
	//void Render();

	void PickWeaponLoad(char* szFileName);

	virtual void Render(IN D3DXVECTOR4* LightPosition, IN D3DXVECTOR4* LightDirection) override;
	virtual void Render();
	virtual bool GetHeight(IN float x, OUT float& y, IN float z) override;

	void PickWeaponRender(
		std::vector<D3DMATERIAL9> vecMtl,
		std::vector<LPDIRECT3DTEXTURE9> vecTex,
		LPD3DXEFFECT Shader, LPD3DXMESH Mesh,
		float Px, float Py, float Pz);
};

