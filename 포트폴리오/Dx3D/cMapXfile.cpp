#include "stdafx.h"
#include "cMapXfile.h"


cMapXfile::cMapXfile()
	: Mesh(NULL)
	, Mtrls(0)
	, Textures(0)
{
}


cMapXfile::~cMapXfile()
{
	SAFE_RELEASE(Mesh);
	for each(auto p in Textures)
	{
		SAFE_RELEASE(p);
	}
}

void cMapXfile::Setup(char* szFilename)
{
	HRESULT hr = 0;

	ID3DXBuffer* adjBuffer = 0;
	ID3DXBuffer* mtrlBuffer = 0;
	DWORD numMtrls = 0;

	hr = D3DXLoadMeshFromX(
		szFilename,
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&adjBuffer,
		&mtrlBuffer,
		0,
		&numMtrls,
		&Mesh);

	if (mtrlBuffer != 0 && numMtrls != 0)
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		for (int i = 0; i < numMtrls; i++)
		{
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;

			Mtrls.push_back(mtrls[i].MatD3D);

			if (mtrls[i].pTextureFilename != 0)
			{
				IDirect3DTexture9* tex = 0;
				D3DXCreateTextureFromFile(
					g_pD3DDevice,
					mtrls[i].pTextureFilename,
					&tex);

				Textures.push_back(tex);
			}


			else
			{
				Textures.push_back(0);
			}
		}
	}

	SAFE_RELEASE(mtrlBuffer);
}

void cMapXfile::Render()
{
	D3DXMATRIXA16 matW;
	D3DXMatrixIdentity(&matW);
	//D3DXMATRIXA16 matW , matR , matT;
	//D3DXMatrixRotationZ(&matR, D3DX_PI);
	//D3DXMatrixTranslation(&matT, 0, 10, 0);
	//matW = matR * matT;

	g_pD3DDevice->GetTransform(D3DTS_WORLD, &matW);
	for (int i = 0; i < Mtrls.size(); i++)
	{
		//g_pD3DDevice->SetTexture(0, Textures[i]->GetTexture());
		//g_pD3DDevice->SetMaterial(&Mtrls[i]->GetMtl());
		
		Mesh->DrawSubset(i);
	}
}
