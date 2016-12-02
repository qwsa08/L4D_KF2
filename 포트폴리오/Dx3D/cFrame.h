#pragma once

#include "cMtlTex.h"

class cFrame : public cObject
{
private:
	std::vector<cFrame*>		m_vecChild;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	int							m_nNumTri;

	/*std::vector<ST_PNT_VERTEX>	m_vecVertex;*/
	//SYNTHESIZE(std::vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);
	SYNTHESIZE_ADD_REF(cMtlTex*, m_pMtlTex, MtlTex);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matLocal, LocalTM);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorld, WorldTM);
	SYNTHESIZE_PASS_BY_REF(std::vector<ST_POS_SAMPLE>, m_vecPosTrack, PosTrack);
	SYNTHESIZE_PASS_BY_REF(std::vector<ST_ROT_SAMPLE>, m_vecRotTrack, RotTrack);

public:
	cFrame(void);
	virtual ~cFrame(void);

	void SetVertex(std::vector<ST_PNT_VERTEX> vecVertex);
	void Update(int nKeyFrame, D3DXMATRIXA16* pParent);
	void Render();
	void AddChild(cFrame* pChild);
	void Destroy();
	void CalcLocalTM(D3DXMATRIXA16* pParent);
	void LocalT(int nKeyFrame, D3DXMATRIXA16& mat);
	void LocalR(int nKeyFrame, D3DXMATRIXA16& mat);
};
