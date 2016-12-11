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

void cObjLoader::Load(IN char* szPath, OUT std::vector<D3DXVECTOR3>& vecBoundingBox, IN D3DXMATRIXA16* pmat /*= NULL*/)
{
	std::vector<D3DXVECTOR3>	vecV;
	std::vector<D3DXVECTOR3>	vecVN;
	std::vector<D3DXVECTOR2>	vecVT;
	std::vector<ST_PNT_VERTEX>	vecVertex;
	//std::string					sMtlName;
	//cGroup* pGroup = NULL;

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
		}
		else if(szBuf[0] == 'u')
		{
		}
		else if(szBuf[0] == 'g')
		{
		}
		else if(szBuf[0] == 'v')
		{
			if(szBuf[1] == 't')
			{
			}
			else if(szBuf[1] == 'n')
			{
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
				if(pmat)
				{
					D3DXVec3TransformCoord(&v.p, &v.p, pmat);
					D3DXVec3TransformNormal(&v.n, &v.n, pmat);
				}
				vecBoundingBox.push_back(v.p);
				//m_vecVertex.push_back(v);
			}
		}
	}
	
	
	fclose(fp);
	

	for each(auto it in m_mapMtlTex)
	{
		SAFE_RELEASE(it.second);
	}
}

LPD3DXMESH cObjLoader::Load(OUT cObjMap* ObjMap,
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

	//========================= ¶¥ 
	std::vector<ST_PNT_VERTEX> vecVertexs;
	//========================= 
	//========================= ÀüÃ¼
	std::vector<ST_PNT_VERTEX> vecMap;
	
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
			char szMtlName[1024];
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
			std::vector<ST_PNT_VERTEX> vecTemp;

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
				vecTemp.push_back(v);
				vecMap.push_back(v);
			}

			
			std::map<int, std::string>::iterator iMapFloor;
			iMapFloor = m_mapFloor.begin();
			for (iMapFloor; iMapFloor != m_mapFloor.end(); iMapFloor++)
			{
				if (!strcmp(sMtlName.c_str(), iMapFloor->second.c_str()))
				{
				    vecVertexs.push_back(vecTemp[0]);
					vecVertexs.push_back(vecTemp[1]);
					vecVertexs.push_back(vecTemp[2]);
				}
			}

			vecAttr.push_back(m_mapMtlTex[sMtlName]->GetAttrID());
		}
	}

	fclose(fp);
	ObjMap->SetVertex(vecVertexs);
	ObjMap->SetMap(vecMap);
	
	//vecVertexs = vecVertex;

	//m_pTestObj->SetVertex(vecVertex);
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
	int nMtlNum = -1;
	SetFloorMtrlNum(&m_mapFloor);
	SetWallMtrlNum(&m_mapWall);

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
			nMtlNum++;

			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);

			m_mapMtlTex[sMtlName] = new cMtlTex;
			m_mapMtlTex[sMtlName]->SetAttrID(vecMtlTex.size());
			vecMtlTex.push_back(m_mapMtlTex[sMtlName]);

			for (int i = 0; i < m_mapFloor.size(); ++i)
			{
				if (m_mapFloor.find(nMtlNum) != m_mapFloor.end())
				{
					m_mapFloor[nMtlNum] = sMtlName;
				}
			}

			for (int i = 0; i < m_mapWall.size(); ++i)
			{
				if (m_mapWall.find(nMtlNum) != m_mapWall.end())
				{
					m_mapWall[nMtlNum] = sMtlName;
				}
			}
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

			if (szBuf[5] == 'a' || szBuf[0] == 'd')
				m_mapMtlTex[sMtlName]->SetTexture(g_pTextureManager->GetTexture(szPath));

			else if (szBuf[5] == 'n')
				m_vecNomalMap.push_back(g_pTextureManager->GetTexture(szPath));

			else if (szBuf[5] == 's')
				m_vecSpecularMap.push_back(g_pTextureManager->GetTexture(szPath));
		}
	}

	fclose(fp);
}

void cObjLoader::SetFloorMtrlNum(OUT std::map<int, std::string>* mapFloor)
{
	std::vector<int> vecNum;
	vecNum.push_back(3);
	vecNum.push_back(13);
	vecNum.push_back(18);
	vecNum.push_back(21);
	vecNum.push_back(27);
	vecNum.push_back(29);
	vecNum.push_back(47);
	vecNum.push_back(49);
	vecNum.push_back(63);
	vecNum.push_back(65);
	vecNum.push_back(67);
	vecNum.push_back(68);
	vecNum.push_back(76);
	vecNum.push_back(145);


	std::string s("");

	for (int i = 0; i < vecNum.size(); ++i)
	{
		(*mapFloor)[vecNum[i]] = s;
	}
}
void cObjLoader::SetWallMtrlNum(OUT std::map<int, std::string>* mapWall)
{
	std::vector<int> vecNum;
	
	//vecNum.push_back(10);
	//vecNum.push_back(28);
	//vecNum.push_back(31);
	//vecNum.push_back(33);
	//vecNum.push_back(37);
	//vecNum.push_back(42);
	//vecNum.push_back(50);
	//vecNum.push_back(52);
	//vecNum.push_back(53);
	//vecNum.push_back(19);
	//vecNum.push_back(88);
	//vecNum.push_back(115);
	//vecNum.push_back(116);
	//vecNum.push_back(118);
	//vecNum.push_back(126);
	//vecNum.push_back(120);
	//vecNum.push_back(59);
	std::string s("");

	for (int i = 0; i < vecNum.size(); ++i)
	{
		(*mapWall)[vecNum[i]] = s;
	}
}













