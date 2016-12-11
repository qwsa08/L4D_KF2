#pragma once

class cMtlTex;
class cGroup;
class cObjMap;

class cObjLoader
{
private:
	std::map<std::string, cMtlTex*>	m_mapMtlTex;
	std::vector<ST_PNT_VERTEX>		m_vecVertex;
	std::map<int, std::string>		m_mapFloor;
	std::map<int, std::string>		m_mapWall;

	SYNTHESIZE(std::vector<LPDIRECT3DTEXTURE9>, m_vecNomalMap, NomalMap);
	SYNTHESIZE(std::vector<LPDIRECT3DTEXTURE9>, m_vecSpecularMap, SpecularMap);

public:
	cObjLoader(void);
	~cObjLoader(void);

	void Load(IN char* szPath, OUT std::vector<D3DXVECTOR3>& vecBoundingBox, IN D3DXMATRIXA16* pmat = NULL);
	LPD3DXMESH Load(OUT cObjMap* ObjMap,
	IN char* szPath,
	OUT std::vector<cMtlTex*>& vecMtlTex,
	IN D3DXMATRIXA16* pmat = NULL);

	std::vector<ST_PNT_VERTEX> GetVertexFull() { return m_vecVertex; }
private:
	void LoadMtlLib(char* szPath);
	void LoadMtlLib(char* szPath, OUT std::vector<cMtlTex*>& vecMtlTex);
	void SetFloorMtrlNum(OUT std::map<int, std::string>* mapFloor);
	void SetWallMtrlNum(OUT std::map<int, std::string>* mapWall);
};

