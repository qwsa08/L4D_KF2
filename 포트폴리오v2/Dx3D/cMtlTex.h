#pragma once

class cMtlTex : public cObject
{
private:
	SYNTHESIZE_PASS_BY_REF(D3DMATERIAL9, m_stMtl, Mtl);
	SYNTHESIZE(DWORD, m_dwAttrID, AttrID);
	SYNTHESIZE_ADD_REF(LPDIRECT3DTEXTURE9, m_pTexture, Texture);

// 	void SetTexture(LPDIRECT3DTEXTURE9 pTexture)
// 	{
// 		if(m_pTexture != pTexture)
// 		{
// 			SAFE_RELEASE(m_pTexture);
// 			SAFE_ADD_REF(pTexture);
// 			m_pTexture = pTexture;
// 		}
// 	}

public:
	cMtlTex(void);
	virtual ~cMtlTex(void);
//	D3DMATERIAL9		m_stMtl;
// 	void SetMtl(D3DMATERIAL9 stMtl)
// 	{
// 		m_stMtl = stMtl;
// 	}
// 	D3DMATERIAL9 GetMtl()
// 	{
// 		return m_stMtl;
// 	}
};

