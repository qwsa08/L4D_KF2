#pragma once
class cAstarNode
{
public:
	cAstarNode();
	~cAstarNode();

	float			F;
	float			G;
	float			H;
	cAstarNode*		m_pParent;
	bool			m_isClose;
	bool			m_isOpen;
	D3DXVECTOR3		m_vPosition;
	int				m_nHeapIndex;
};

