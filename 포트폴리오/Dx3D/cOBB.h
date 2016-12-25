#pragma once
class cCrtController;
class cOBB
{
private:
	D3DXVECTOR3 m_vOrgCenterPos;		
	D3DXVECTOR3 m_vOrgAxisDir[3];		
	
	D3DXVECTOR3 m_vCenterPos;		// ���� �߾��� ��ǥ
	D3DXVECTOR3 m_vAxisDir[3];		// ���ڿ� ������ �� ���� ��������
	float		m_fAxisLen[3];		// ������ ������ �� ���� ���� fAxisLen[n]�� vAxisDir[n]�� ���� �����Ѵ�.
	float		m_fAxisHalfLen[3];

	D3DXMATRIXA16 m_matWorldTM;
public:
	cOBB(void);
	~cOBB(void);

	void SetupOBJ(D3DXVECTOR3 _min, D3DXVECTOR3 _max, OUT ST_OBB &box , D3DXMATRIXA16* _World = NULL);
	void Setup(D3DXVECTOR3 _min, D3DXVECTOR3 _max, OUT ST_OBB &box);
	void Update(D3DXMATRIXA16* pmatWorld, ST_OBB &box);
	void DebugRender(ST_OBB* pOBB1,D3DCOLOR c);
	

	bool GetFaceBoxIntersect(ST_OBB* pOBB1, D3DXVECTOR3* PlayerPos, D3DXVECTOR3* PlayerDir, D3DXMATRIXA16* _World);
	bool GetMonsterBoxIntersect(ST_OBB* pOBB1, D3DXVECTOR3* PlayerPos, D3DXVECTOR3* PlayerDir);
	D3DXMATRIXA16 GetWTM() { return m_matWorldTM; }
	static bool IsCollision(ST_OBB* pOBB1, ST_OBB* pOBB2);
};

