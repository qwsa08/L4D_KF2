#pragma once

class cCamera;
class cGrid;
class cCrtController;
class cPyramid;
class iMap;
class cMtlTex;
//class cSkinnedMesh;
class cFrustum;
class cMapXfile;

class cPlayer;
class cObjMap;
class cZombie;
class cOBB;
class cBulletCollision;
class cCrossHead;

class cDijkstra;

class cMainGame
{
private:
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	cPyramid*					m_pPyramid;
	cCamera*					m_pCamera;
	cGrid*						m_pGrid;
	cCrtController*				m_pController;
	iMap*						m_pMap;
	std::vector<ST_SPHERE>		m_vecSphere;
	LPD3DXMESH					m_pMesh;
	D3DMATERIAL9				m_stMtlNormal;
	D3DMATERIAL9				m_stMtlPicked;
	std::vector<cMtlTex*>		m_vecMtlTex;
	LPD3DXMESH					m_pMapMesh;
	//std::vector<cSkinnedMesh*>	m_vecSkinnedMesh;
	cFrustum*					m_pFrustum;
	//cMapXfile*					m_pMapXFile;
	//cSkinnedMesh*				m_pSkinnedMesh;
	cPlayer*					m_pPlayer;
	cObjMap*					m_pBoundingBox;
	std::vector<D3DXVECTOR3>	test;
	cZombie*					m_pBloat;
	cBulletCollision*			m_pBulletCollision;
	//====나중에 나눠줘야한다.
	cOBB*						m_pOBB;
	ST_OBB						m_stWall[8];
	D3DCOLOR					m_cPaint;
	bool						m_mouseCheck;
	bool						m_fire;
	cCrossHead*					m_pCrossHead;

	cDijkstra*					m_pDijkstra;

	std::vector<D3DXVECTOR3> temp;

	//============테스트중=======================//
	std::vector<ST_PT_VERTEX>	m_vTexture;
public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetLight();
};

