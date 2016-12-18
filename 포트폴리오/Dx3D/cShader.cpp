#include "stdafx.h"
#include "cShader.h"

cShader::cShader()
{
}


cShader::~cShader()
{
}

LPD3DXMESH cShader::LoadModel(const char* FileName)
{
	LPD3DXMESH ret = NULL;

	if (FAILED(D3DXLoadMeshFromX(FileName, D3DXMESH_SYSTEMMEM, g_pD3DDevice, NULL,
		NULL, NULL, NULL, &ret)))
	{
		OutputDebugString("모델 로딩 실패 : ");
		OutputDebugString(FileName);
		OutputDebugString("\n");
	}

	return ret;
}

LPD3DXEFFECT cShader::LoadShader(const char* FileName)
{
	LPD3DXEFFECT ret = NULL;
	LPD3DXBUFFER pError = NULL;
	DWORD dwshaderFlags = 0;

#if _DEBUG
	dwshaderFlags != D3DXSHADER_DEBUG;
#endif
	LPD3DXBUFFER pErrBuf = NULL;
	D3DXCreateEffectFromFile(g_pD3DDevice, FileName, NULL, NULL, dwshaderFlags, NULL, &ret, &pError);

	if (!ret && pError)
	{
		int size = pError->GetBufferSize();
		void* ack = pError->GetBufferPointer();

		if (ack)
		{
			char* str = new char[size];
			sprintf(str, (const char*)ack, size);
			OutputDebugString(str);
			delete[] str;
		}
	}


	return ret;
}

LPDIRECT3DTEXTURE9 cShader::LoadTexture(const char* FileName)
{
	LPDIRECT3DTEXTURE9 ret = NULL;

	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, FileName, &ret)))
	{
		OutputDebugString("텍스쳐 로딩 실패 : ");
		OutputDebugString(FileName);
		OutputDebugString("\n");
	}

	return ret;
}