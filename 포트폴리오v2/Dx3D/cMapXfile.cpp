#include "stdafx.h"
#include "cMapXfile.h"


cMapXfile::cMapXfile()
	: Mesh(0)
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
	D3DXMATRIXA16 matW , matR , matT;
	D3DXMatrixIdentity(&matW);
	//D3DXMatrixRotationZ(&matR, D3DX_PI);
	//D3DXMatrixTranslation(&matT, 0, 10, 0);
	//matW = matR * matT;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matW);
	for (int i = 0; i < Mtrls.size(); i++)
	{
		g_pD3DDevice->SetMaterial(&Mtrls[i]);
		g_pD3DDevice->SetTexture(0, Textures[i]);
		Mesh->DrawSubset(i);
	}
}
bool cMapXfile::GetHeight(IN float x, OUT float& y, IN float z)
{
	//int XY_MAX = 100000;
	//if (x<0 || x > XY_MAX || z < 0 || z > XY_MAX)
	//{
	//	y = 0.f;
	//	return false;
	//}
	//int _x = (int)x;
	//int _z = (int)z;

	////»ï°¢ÇüÀÌ´Ï±ñ ÀÎµ¦½º¹öÆÛ¾È¿¡ ÀÖ´Â »ï°¢Çü!!?!
	//int _0 = _z * XY_MAX + _x;
	//int _1 = (_z + 1) * XY_MAX + _x;
	//int _2 = _z * XY_MAX + _x + 1;
	//int _3 = (_z + 1) * XY_MAX + _x + 1;

	//float fx = x - _x;
	//float fz = z - _z;
	//if (fx + fz < 1)
	//{
	//	D3DXVECTOR3 Vx = m_vPNT[_2].p - m_vPNT[_0].p;
	//	D3DXVECTOR3 Vz = m_vPNT[_1].p - m_vPNT[_0].p;

	//	y = m_vPNT[_0].p.y + (Vx * fx + Vz * fz).y;
	//	int a = 0;
	//}
	//else
	//{
	//	fx = 1.f - fx;
	//	fz = 1.f - fz;

	//	D3DXVECTOR3 Vx = m_vPNT[_1].p - m_vPNT[_3].p;
	//	D3DXVECTOR3 Vz = m_vPNT[_2].p - m_vPNT[_3].p;

	//	y = m_vPNT[_3].p.y + (Vx * fx + Vz * fz).y;
	//}

	return true;
}