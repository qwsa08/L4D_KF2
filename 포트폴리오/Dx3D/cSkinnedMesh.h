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

public:
	cSkinnedMesh(char* szFolder, char* szFilename);
	
	~cSkinnedMesh(void);
	
	//================플레이어===============
	void Update(D3DXMATRIXA16* pmat, int state);
	void Render(D3DXMATRIXA16* pmat);

	//=======================================
	void UpdateAndRender(D3DXMATRIXA16* pmat = NULL, D3DXMATRIXA16* pScal =NULL);
	void SetAnimationIndex(int nIndex);

	void SetRandomTrackPosition(); // 테스트용
	void SetPosition(D3DXVECTOR3 v)
	{
		m_vPosition = v;
		m_stBoundingSphere.vCenter += v;
		m_stBoundingBox.vCenter += v;
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

