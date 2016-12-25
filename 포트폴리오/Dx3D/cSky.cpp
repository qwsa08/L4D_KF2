#include "stdafx.h"
#include "cSky.h"
#include "cMapXfile.h"

cSky::cSky()
	: m_pSky(NULL)
{
}


cSky::~cSky()
{
	SAFE_RELEASE(m_pSky);
	for (int i = 0; i < m_vSkyTxt.size(); i++)
	{
		SAFE_RELEASE(m_vSkyTxt[i]);
	}
}

void cSky::SetUp()
{
	cMapXfile* pMapX = new cMapXfile;
	m_pSky = pMapX->MeshXFileLoad("Map/sky.X", &m_vSkyMtl, &m_vSkyTxt);

}

void cSky::Render()
{
	D3DXMATRIXA16 mat, matS, matT;
	D3DXMatrixScaling(&matS, 4, 1.5, 4);
	D3DXMatrixTranslation(&matT, 0, -100, 0);
	D3DXMatrixIdentity(&mat);

	mat = matS * matT;

	g_pD3DDevice->SetTransform(D3DTS_WORLD,& mat);
	for (int i = 0; i < m_vSkyMtl.size(); i++)
	{
		g_pD3DDevice->SetMaterial(&m_vSkyMtl[i]);
		g_pD3DDevice->SetTexture(0,m_vSkyTxt[i]);
		m_pSky->DrawSubset(i);
	}
}
