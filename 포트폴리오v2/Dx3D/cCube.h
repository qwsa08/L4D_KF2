#pragma once

class cCamera;

class cCube
{
private:
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	D3DXMATRIXA16				m_matWorldTM;
	std::vector<cCube*>			m_vecChild;
	float						m_fAngle;
	float						m_fAngleVel;
	D3DXVECTOR3					m_vTranslation;

public:
	cCube(void);
	~cCube(void);

	void Setup(D3DXMATRIXA16* pmat);
	void Update(D3DXMATRIXA16* pParentWorld);
	void Render();
	D3DXMATRIXA16* GetWorldMatrix();
	void AddChild(cCube* pCube);
	void SetAngleVel(float fVel)
	{
		m_fAngleVel = fVel;
	}

	void SetTranslation(D3DXVECTOR3& v)
	{
		m_vTranslation = v;
	}
};

