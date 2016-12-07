#pragma once

class cCamera;
class cGrid;
class cCrtController;
class cPyramid;
class iMap;
class cMtlTex;

class cPlayer;
class cZed;
class cObjMap;
class cOBB;

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
	
	cPlayer*					m_pPlayer;
	cZed*						m_pZombie;

	cObjMap*					m_pBoundingBox;

	cOBB*						m_pOBB;

	ST_OBB						m_stWall;
	D3DCOLOR					m_cPaint;
	//========================================
	std::vector<D3DXVECTOR3>	test;
public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetLight();
};

