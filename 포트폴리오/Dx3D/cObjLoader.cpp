#include "StdAfx.h"
#include "cObjLoader.h"
#include "cMtlTex.h"
#include "cGroup.h"
#include "cObjMap.h"

cObjLoader::cObjLoader(void)
{
}

cObjLoader::~cObjLoader(void)
{
}

void cObjLoader::Load( IN char* szPath, OUT std::vector<cGroup*>& vecGroup, IN D3DXMATRIXA16* pmat /*= NULL*/)
{
	std::vector<D3DXVECTOR3>	vecV;
	std::vector<D3DXVECTOR3>	vecVN;
	std::vector<D3DXVECTOR2>	vecVT;
	std::vector<ST_PNT_VERTEX>	vecVertex;
	std::string					sMtlName;

	
	cGroup* pGroup = NULL;

	FILE* fp = NULL;

	fopen_s(&fp, szPath, "r");

	while(!feof(fp))
	{
		char szBuf[1024] = {'\0', };
		fgets(szBuf, 1024, fp);
		if (strlen(szBuf) == 0) continue;
		
		if (szBuf[0] == '#') 
		{
			continue;
		}
		else if(szBuf[0] == 'm')
		{
			char szMtlPath[1024];
			sscanf_s(szBuf, "%*s %s", szMtlPath, 1024);
			LoadMtlLib(szMtlPath);
		}
		else if(szBuf[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);
		}
		else if(szBuf[0] == 'g')
		{
			if (!vecVertex.empty())
			{
				pGroup = new cGroup;
				pGroup->SetVertex(vecVertex);
				pGroup->SetMtlTex(m_mapMtlTex[sMtlName]);
				vecGroup.push_back(pGroup);
				vecVertex.clear();
				
			}
		}
		else if(szBuf[0] == 'v')
		{
			if(szBuf[1] == 't')
			{
				float u, v;
				sscanf_s(szBuf, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if(szBuf[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
			else
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if(szBuf[0] == 'f')
		{
			int aIndex[3][3];
			sscanf_s(szBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[aIndex[i][0] - 1];
				v.t = vecVT[aIndex[i][1] - 1];
				v.n = vecVN[aIndex[i][2] - 1];
				if(pmat)
				{
					D3DXVec3TransformCoord(&v.p, &v.p, pmat);
					D3DXVec3TransformNormal(&v.n, &v.n, pmat);
				}
				vecVertex.push_back(v);
				m_vecVertex.push_back(v);
			}
		}
	}
	
	
	fclose(fp);

	for each(auto it in m_mapMtlTex)
	{
		SAFE_RELEASE(it.second);
	}
}

LPD3DXMESH cObjLoader::Load(cObjMap* m_pTestObj,
	IN char* szPath,
	OUT std::vector<cMtlTex*>& vecMtlTex,
	IN D3DXMATRIXA16* pmat /*= NULL*/ )
{
	std::vector<D3DXVECTOR3>	vecV;
	std::vector<D3DXVECTOR3>	vecVN;
	std::vector<D3DXVECTOR2>	vecVT;
	std::vector<ST_PNT_VERTEX>	vecVertex;
	std::vector<DWORD>			vecAttr;

	std::string					sMtlName;

	std::vector<ST_PNT_VERTEX>	vecFloorVertex;
	char szMtlName[1024];

	cGroup* pGroup = NULL;

	FILE* fp = NULL;

	fopen_s(&fp, szPath, "r");

	while(!feof(fp))
	{
		char szBuf[1024] = {'\0', };
		fgets(szBuf, 1024, fp);
		if (strlen(szBuf) == 0) continue;

		if (szBuf[0] == '#') 
		{
			continue;
		}
		else if(szBuf[0] == 'm')
		{
			char szMtlPath[1024];
			sscanf_s(szBuf, "%*s %s", szMtlPath, 1024);
			LoadMtlLib(szMtlPath, vecMtlTex);
		}
		else if(szBuf[0] == 'u')
		{
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);
		}
		else if(szBuf[0] == 'g')
		{	
		}
		else if(szBuf[0] == 'v')
		{
			if(szBuf[1] == 't')
			{
				float u, v;
				sscanf_s(szBuf, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if(szBuf[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
			else
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if(szBuf[0] == 'f')
		{
			int aIndex[3][3];
			sscanf_s(szBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[aIndex[i][0] - 1];
				v.t = vecVT[aIndex[i][1] - 1];
				v.n = vecVN[aIndex[i][2] - 1];
				if(pmat)
				{
					D3DXVec3TransformCoord(&v.p, &v.p, pmat);
					D3DXVec3TransformNormal(&v.n, &v.n, pmat);
				}
				vecVertex.push_back(v);
				if (!strcmp(szMtlName, "texture_3") ||
					!strcmp(szMtlName, "texture_13") ||
					!strcmp(szMtlName, "texture_18") ||
					!strcmp(szMtlName, "texture_21") ||
					!strcmp(szMtlName, "texture_29") ||
					!strcmp(szMtlName, "texture_47") || 
					!strcmp(szMtlName, "texture_63") || 
					!strcmp(szMtlName, "texture_68") ||
					!strcmp(szMtlName, "texture_145"))
					vecFloorVertex.push_back(v);

			}

			vecAttr.push_back(m_mapMtlTex[sMtlName]->GetAttrID());
		}
	}

	fclose(fp);
	m_pTestObj->SetVertex(vecFloorVertex);
	LPD3DXMESH pMesh = NULL;
	D3DXCreateMeshFVF(vecVertex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&pMesh);

	ST_PNT_VERTEX* pV = NULL;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	for (size_t i = 0; i < vecVertex.size(); ++i)
	{
		pI[i] = i;
	}
	pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(0, &pA);
	memcpy(pA, &vecAttr[0], vecAttr.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdj(pMesh->GetNumFaces() * 3);
	pMesh->OptimizeInplace(
		D3DXMESHOPT_COMPACT | 
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0],
		NULL,
		NULL,
		NULL);

	return pMesh;
}

void cObjLoader::LoadMtlLib(char* szPath)
{
	m_mapMtlTex.clear();
	FILE* fp = NULL;
	
	std::string sMtlName;

	fopen_s(&fp, szPath, "r");

	while(!feof(fp))
	{
		char szBuf[1024] = {'\0', };
		fgets(szBuf, 1024, fp);
		if (strlen(szBuf) == 0) continue;

		if (szBuf[0] == '#') 
		{
			continue;
		}
		else if(szBuf[0] == 'n')
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);
			m_mapMtlTex[sMtlName] = new cMtlTex;
		}
		else if(szBuf[0] == 'K')
		{
			D3DMATERIAL9& stMtl = m_mapMtlTex[sMtlName]->GetMtl();
			float r, g, b;
			if(szBuf[1] == 'a')
			{
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				stMtl.Ambient = D3DXCOLOR(r, g, b, 1.0f);
			}
			else if(szBuf[1] == 'd')
			{
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				stMtl.Diffuse = D3DXCOLOR(r, g, b, 1.0f);
			}
			else if(szBuf[1] == 's')
			{
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				stMtl.Specular = D3DXCOLOR(r, g, b, 1.0f);
			}
		}
		else if(szBuf[0] == 'm')
		{
			char szPath[1024];
			sscanf_s(szBuf, "%*s %s", szPath, 1024);
			m_mapMtlTex[sMtlName]->SetTexture(g_pTextureManager->GetTexture(szPath));
		}
	}

	fclose(fp);
}

void cObjLoader::LoadMtlLib( char* szPath, OUT std::vector<cMtlTex*>& vecMtlTex )
{
	m_mapMtlTex.clear();

	FILE* fp = NULL;

	std::string sMtlName;

	fopen_s(&fp, szPath, "r");

	while(!feof(fp))
	{
		char szBuf[1024] = {'\0', };
		fgets(szBuf, 1024, fp);
		if (strlen(szBuf) == 0) continue;

		if (szBuf[0] == '#') 
		{
			continue;
		}
		else if(szBuf[0] == 'n')
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);

			m_mapMtlTex[sMtlName] = new cMtlTex;
			m_mapMtlTex[sMtlName]->SetAttrID(vecMtlTex.size());
			vecMtlTex.push_back(m_mapMtlTex[sMtlName]);
		}
		else if(szBuf[0] == 'K')
		{
			D3DMATERIAL9& stMtl = m_mapMtlTex[sMtlName]->GetMtl();
			float r, g, b;
			if(szBuf[1] == 'a')
			{
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				stMtl.Ambient = D3DXCOLOR(r, g, b, 1.0f);
			}
			else if(szBuf[1] == 'd')
			{
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				stMtl.Diffuse = D3DXCOLOR(r, g, b, 1.0f);
			}
			else if(szBuf[1] == 's')
			{
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				stMtl.Specular = D3DXCOLOR(r, g, b, 1.0f);
			}
		}
		else if(szBuf[0] == 'm')
		{
			char szPath[1024];
			sscanf_s(szBuf, "%*s %s", szPath, 1024);
			m_mapMtlTex[sMtlName]->SetTexture(g_pTextureManager->GetTexture(szPath));
		}
	}

	fclose(fp);
}














