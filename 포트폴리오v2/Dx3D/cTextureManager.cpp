#include "StdAfx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager(void)
{
}


cTextureManager::~cTextureManager(void)
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture( char* szPath )
{
	return GetTexture(std::string(szPath));
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture( std::string sPath )
{
	if (m_mapTexture.find(sPath) == m_mapTexture.end())
	{
		LPDIRECT3DTEXTURE9 pTexture;
		D3DXCreateTextureFromFile(g_pD3DDevice, sPath.c_str(), &pTexture);
		m_mapTexture[sPath] = pTexture;
	}
	return m_mapTexture[sPath];
}

void cTextureManager::Destroy()
{
	for each(auto it in m_mapTexture)
	{
		SAFE_RELEASE(it.second);
	}
}
