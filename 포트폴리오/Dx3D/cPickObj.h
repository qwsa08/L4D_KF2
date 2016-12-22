#pragma once
#include "iMap.h"

class cGroup;
class cMtlTex;

class cPickObj : public iMap
{
protected:
	LPD3DXMESH					m_PickShotGun;
	LPD3DXMESH					m_PickBullpup;
	LPD3DXMESH					m_PickHeal;

	std::vector<cMtlTex*>		m_pShotGunMtltex;
	std::vector<cMtlTex*>		m_pBullpupMtltex;
	std::vector<cMtlTex*>		m_pHealMtltex;

	std::vector<D3DXVECTOR3>	m_line;
	std::vector<D3DXVECTOR3>	m_Start;

	SYNTHESIZE(std::vector<ST_PNT_VERTEX>, m_vecObj, Obj);
	SYNTHESIZE(std::vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);

	LPD3DXEFFECT				m_OutLineShader;

public:
	cPickObj();
	virtual ~cPickObj();

	virtual void Load(char* szMap, D3DXMATRIXA16* pmat = NULL);
	virtual void Render(IN D3DXVECTOR4* LightPosition, IN D3DXVECTOR4* LightDirection) override;
	virtual void Render();
	virtual bool GetHeight(IN float x, OUT float& y, IN float z) override;

	void PickWeaponRender(std::vector<cMtlTex*> Mtltex, 
		LPD3DXEFFECT Shader, LPD3DXMESH Mesh, 
		float Px, float Py, float Pz);
};