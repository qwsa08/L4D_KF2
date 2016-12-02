#pragma once

class cMtlTex;
class cGroup;
class cObjMap;

class cObjLoader
{
private:
	std::map<std::string, cMtlTex*> m_mapMtlTex;
	std::vector<ST_PNT_VERTEX> m_vecVertex;

public:
	cObjLoader(void);
	~cObjLoader(void);

	void Load(IN char* szPath, OUT std::vector<cGroup*>& vecGroup, IN D3DXMATRIXA16* pmat = NULL);
	LPD3DXMESH Load(cObjMap* m_pTestObj,
	IN char* szPath,
	OUT std::vector<cMtlTex*>& vecMtlTex,
	IN D3DXMATRIXA16* pmat = NULL);

	std::vector<ST_PNT_VERTEX> GetVertexFull() { return m_vecVertex; }
private:
	void LoadMtlLib(char* szPath);
	void LoadMtlLib(char* szPath, OUT std::vector<cMtlTex*>& vecMtlTex);
};

