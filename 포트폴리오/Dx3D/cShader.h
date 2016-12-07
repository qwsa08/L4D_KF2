#pragma once

#define g_pShader cShader::GetInstance()

class cShader
{
private:
	SINGLETONE(cShader);

public:
	LPD3DXMESH LoadModel(const char* FileName);
	LPD3DXEFFECT LoadShader(const char* FileName);
	LPDIRECT3DTEXTURE9 LoadTexture(const char* FileName);
};

