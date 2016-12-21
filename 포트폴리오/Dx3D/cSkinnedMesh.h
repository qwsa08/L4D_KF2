#pragma once

struct ST_BONE;

class cSkinnedMesh
{
	friend class cSkinnedMeshManager;
	
private:
	//하나만 생성
	ST_BONE*					m_pRootFrame;			
	DWORD						m_dwWorkingPaletteSize;
	D3DXMATRIX*					m_pmWorkingPalette;
	LPD3DXEFFECT				m_pEffect;
	ST_SPHERE					m_stBoundingSphere;
	ST_BoundingBox				m_stBoundingBox;

	// 객체마다 생성
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	D3DXVECTOR3					m_vPosition;
	bool						m_isBlending;
	float						m_fBlendTime;
	float						m_fPassedBlendTime;
	float						m_fTimer;
	float						m_dPeriod;

	SYNTHESIZE(GUN_NAME, m_GunName, GunName);
	SYNTHESIZE(bool, m_bAction, Action);
	SYNTHESIZE(int, m_FrameNum, FrameNum);
public:
	cSkinnedMesh(char* szFolder, char* szFilename);
	
	~cSkinnedMesh(void);
	
	//================플레이어===============
	void Update(D3DXMATRIXA16* pmat, int state);
	void Render(D3DXMATRIXA16* pmat);

	//=======================================
	void UpdateAndRender(D3DXMATRIXA16* pmat = NULL);
	void SetAnimationIndex(int nIndex);
	void SetNomalAnimationIndex(int nIndex);

	//================추가 애니메이션?수정해야할껄요!?===================//
	void SetskinningAnimationIndex(int current, int next);
	float AnimationFrame(int num);
	void AnimationUpdate(int current, int next);

	void SetRandomTrackPosition(); // 테스트용
	void SetPosition(D3DXVECTOR3 v)
	{
		m_vPosition = v;
		//m_stBoundingSphere.vCenter += v;
		//m_stBoundingBox.vCenter += v;
	}
	D3DXVECTOR3 GetPosition()
	{
		return m_vPosition;
	}
	ST_SPHERE* GetBoundingSphere()
	{
		return &m_stBoundingSphere;
	}
	ST_BoundingBox* GetBoundingBox()
	{
		return &m_stBoundingBox;
	}
	
private:
	cSkinnedMesh();
	void Load(char* szFolder, char* szFilename);
	LPD3DXEFFECT LoadEffect(char* szFilename);
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void Render(ST_BONE* pBone = NULL);
	void RenderPlayer(ST_BONE* pBone = NULL);
	void SetupBoneMatrixPtrs(ST_BONE* pBone);
	void Destroy();
};

