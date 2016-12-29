#pragma once
class cEffect
{
	std::vector<ST_PT_VERTEX>	m_vecVertex;
	LPD3DXEFFECT				m_pEffect;
	LPDIRECT3DTEXTURE9			m_pTexture;
	std::vector<D3DXVECTOR2>	m_tempTextureUV;

	int							m_iFramenum;

	float						f_timer;
	int							f_UVx;
	int							f_UVy;
	bool						OnOff;
	bool						f_finish;
public:
	cEffect();
	~cEffect();

	void Setup(char* effectName, int frameNum);
	void Update(bool _OnOff);
	void Render(D3DXVECTOR3* Position, D3DXMATRIX* Rotation, D3DXVECTOR3* Eye = NULL);
};

