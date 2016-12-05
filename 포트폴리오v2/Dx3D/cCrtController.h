#pragma once

class iMap;

class cCrtController
{
private:
	float						m_fSpeed;
	float						m_fAngle;
	D3DXVECTOR3					m_vPosition;
	D3DXMATRIXA16				m_matWorld;
	D3DXVECTOR3					m_Camera;
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vDirection, Direction);
public:
	cCrtController(void);
	~cCrtController(void);

	void Setup();
	void Update(float Angle, iMap* pMap = NULL);
	D3DXVECTOR3* GetPosition()
	{
		return &m_vPosition;
	}
	D3DXMATRIXA16* GetWorldTM()
	{
		return &m_matWorld;
	}

	D3DXVECTOR3* GetCamera()
	{
		return &m_Camera;
	}
};

