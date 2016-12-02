#pragma once

class cPyramid : public cGameObject
{
private:
	std::vector<ST_PC_VERTEX>	m_vecVertex;

public:
	cPyramid(void);
	virtual ~cPyramid(void);

	void Setup(D3DCOLOR c, D3DXMATRIXA16* pmat = NULL);
	virtual void Render() override;
};

