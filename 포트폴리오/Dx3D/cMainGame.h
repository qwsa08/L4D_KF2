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

class cPlayer;
class cObjMap;
class cOBB;
class cBulletCollision;
class cCrossHead;

class cEnemyManager;
class cSky;
class cUI;
class cScene;

class cEffect;

class cSoundSetting;
class cCredit;

class cMainGame
{
private:
	RECT						m_Clientrc;
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	cPyramid*					m_pPyramid;
	cCamera*					m_pCamera;
	cGrid*						m_pGrid;
	cCrtController*				m_pController;
	iMap*						m_pMap;
	//=========================================
	cSky*						m_pSky;
	//=========================================
	//cSoundSetting				m_SoundSetting;
	//=========================================
	cMapXfile*					m_pObj;
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
	cBulletCollision*			m_pBulletCollision;

	//카메라 관련 한개더
	float					    m_ReboundCamera;
	
	//====나중에 나눠줘야한다.
	cOBB*						m_pOBB;
	ST_OBB						m_stWall[8];
	D3DCOLOR					m_cPaint;
	bool						m_mouseCheck;
	bool						m_AimDown;
	bool						m_fire;
	cCrossHead*					m_pCrossHead;

	cEnemyManager*				m_pEnemyManager;

	//std::vector<D3DXVECTOR3> temp;
	//==================
	cUI*						m_pUI;
	cEffect*					m_pEffect;
	bool						m_bBlood;
	//==================
	//============테스트중=======================//
	float						timer;
	bool						OnOff_MOUSE;
	//============ 플레이어 피 + 감도 =========
	float						m_fBloodTimer;
	float						m_fTextTimer;
	bool						m_bText;
	LPD3DXFONT					m_pFont;
	//============몬스터 좌표?===============
	D3DXVECTOR3					m_pMonlocation;
	//========================================
	//========================================
	std::vector<ST_PT_VERTEX>	m_vTexture;
	D3DXMATRIXA16				matView;

	cScene*						m_pScene;
	cCredit*					m_pCredit;
	int							m_nScene;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetLight();
};

