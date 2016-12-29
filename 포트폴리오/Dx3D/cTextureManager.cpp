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
		D3DXIMAGE_INFO	   m_stImageInfo;
		D3DXCreateTextureFromFile(g_pD3DDevice, sPath.c_str(), &pTexture);
		m_mapTexture[sPath] = pTexture;
		
		/*D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			sPath.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0xFF000000,
			&m_stImageInfo,
			NULL,
			&pTexture);
		m_mapTexture[sPath] = pTexture;*/
	}
	return m_mapTexture[sPath];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetSpriteTexture(char * szPath, D3DXIMAGE_INFO * pImageInfo)
{
	return GetSpriteTexture(std::string(szPath), pImageInfo);
}

LPDIRECT3DTEXTURE9 cTextureManager::GetSpriteTexture(std::string sPath, D3DXIMAGE_INFO * pImageInfo)
{
	if (m_mapSpriteTexture.find(sPath) == m_mapSpriteTexture.end())
	{
		LPDIRECT3DTEXTURE9 pTexture = NULL;
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			sPath.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_mapImageInfo[sPath],
			NULL,
			&pTexture);

		m_mapSpriteTexture[sPath] = pTexture;
	}

	if (pImageInfo)
	{
		*pImageInfo = m_mapImageInfo[sPath];
	}

	return m_mapSpriteTexture[sPath];
}

void cTextureManager::Destroy()
{
	for each(auto it in m_mapTexture)
	{
		SAFE_RELEASE(it.second);
	}

	for each(auto it in m_mapSpriteTexture)
	{
		SAFE_RELEASE(it.second);
	}
}
