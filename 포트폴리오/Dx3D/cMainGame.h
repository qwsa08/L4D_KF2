#pragma once

class cCamera;
class cGrid;
class cCrtController;
class cPyramid;
class iMap;
class cMtlTex;
class cSkinnedMesh;
class cFrustum;
class cMapXfile;

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
	std::vector<cSkinnedMesh*>	m_vecSkinnedMesh;
	cFrustum*					m_pFrustum;
	//cMapXfile*					m_pMapXFile;
	cSkinnedMesh*				m_pSkinnedMesh;
	D3DXVECTOR3					m_vCameraTarget;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetLight();
};

