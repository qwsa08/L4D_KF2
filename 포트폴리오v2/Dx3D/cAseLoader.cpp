#include "StdAfx.h"
#include "cAseLoader.h"
#include "Asciitok.h"
#include "cMtlTex.h"
#include "cFrame.h"

cAseLoader::cAseLoader(void)
	: m_fp(NULL)
	, m_pRoot(NULL)
{
}

cAseLoader::~cAseLoader(void)
{

}

cFrame* cAseLoader::Load( char* szPath )
{
	fopen_s(&m_fp, szPath, "r");
	
	while(char* szToken = GetToken())
	{
		if (IsEqual(szToken, ID_SCENE))
		{
			SkipBlock();
			//OutputDebugString(GetToken());OutputDebugString("\n");
		}
		else if (IsEqual(szToken, ID_MATERIAL_LIST))
		{
			ProcessMATERIAL_LIST();
		}
		else if (IsEqual(szToken, ID_GEOMETRY))
		{
			cFrame* pFrame = ProcessGEOMOBJECT();
			if(m_pRoot == NULL) m_pRoot = pFrame;
		}
	}

	fclose(m_fp);

	for each(auto p in m_vecMtlTex)
	{
		SAFE_RELEASE(p);
	}

	if(m_pRoot) 
		m_pRoot->CalcLocalTM(NULL);

	return m_pRoot;
}

char* cAseLoader::GetToken()
{
	bool isQuote = false;
	int nReadCount = 0;

	while(!feof(m_fp))
	{
		char c = fgetc(m_fp);
		
		if(c == '\"')
		{
			if (isQuote) break;
			isQuote = true;
			continue;
		}

		if (!isQuote && c < 33)	// 화이트 스페이스
		{
			if (nReadCount == 0) continue;
			break;
		}

		m_szToken[nReadCount++] = c;
	}
	
	if (nReadCount == 0) return NULL;
	
	m_szToken[nReadCount] = '\0';

	return m_szToken;
}

int cAseLoader::GetInteger()
{
	return atoi(GetToken());
}

float cAseLoader::GetFloat()
{
	return (float)atof(GetToken());
}

bool cAseLoader::IsEqual( char* str1, char* str2 )
{
	return strcmp(str1, str2) == 0;
}

void cAseLoader::SkipBlock()
{
	int nLevel = 0;

	do 
	{
		char* szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMATERIAL_LIST()
{
	int nLevel = 0;

	do 
	{
		char* szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_MATERIAL_COUNT))
		{
			m_vecMtlTex.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MATERIAL))
		{
			int nMtlRef = GetInteger();
			if(m_vecMtlTex[nMtlRef] == NULL)
				m_vecMtlTex[nMtlRef] = new cMtlTex;

			ProcessMATERIAL(m_vecMtlTex[nMtlRef]);
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMATERIAL( cMtlTex* pMtlTex )
{
	int nLevel = 0;

	do 
	{
		char* szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_AMBIENT))
		{
			D3DMATERIAL9& stMtl = pMtlTex->GetMtl();
			stMtl.Ambient.r = GetFloat();
			stMtl.Ambient.g = GetFloat();
			stMtl.Ambient.b = GetFloat();
			stMtl.Ambient.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_DIFFUSE))
		{
			D3DMATERIAL9& stMtl = pMtlTex->GetMtl();
			stMtl.Diffuse.r = GetFloat();
			stMtl.Diffuse.g = GetFloat();
			stMtl.Diffuse.b = GetFloat();
			stMtl.Diffuse.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_SPECULAR))
		{
			D3DMATERIAL9& stMtl = pMtlTex->GetMtl();
			stMtl.Specular.r = GetFloat();
			stMtl.Specular.g = GetFloat();
			stMtl.Specular.b = GetFloat();
			stMtl.Specular.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_MAP_DIFFUSE))
		{
			ProcessMAP_DIFFUSE(pMtlTex);
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMAP_DIFFUSE( cMtlTex* pMtlTex )
{
	int nLevel = 0;

	do 
	{
		char* szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_BITMAP))
		{
			pMtlTex->SetTexture(g_pTextureManager->GetTexture(GetToken()));
		}
	} while (nLevel > 0);
}

cFrame* cAseLoader::ProcessGEOMOBJECT()
{
	cFrame* pFrame = new cFrame;
	pFrame->AutoRelease();

	int nLevel = 0;

	do 
	{
		char* szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_NODE_NAME))
		{
			m_mapFrame[GetToken()] = pFrame;
		}
		else if (IsEqual(szToken, ID_NODE_PARENT))
		{
			cFrame* pParent = m_mapFrame[GetToken()];
			pParent->AddChild(pFrame);
		}
		else if (IsEqual(szToken, ID_NODE_TM))
		{
			ProcessNODE_TM(pFrame);
		}
		else if (IsEqual(szToken, ID_MESH))
		{
			ProcessMESH(pFrame);
		}
		else if (IsEqual(szToken, ID_TM_ANIMATION))
		{
			ProcessTM_ANIMATION(pFrame);
		}
		else if (IsEqual(szToken, ID_MATERIAL_REF))
		{
			pFrame->SetMtlTex(m_vecMtlTex[GetInteger()]);
		}
		
	} while (nLevel > 0);

	return pFrame;
}

void cAseLoader::ProcessMESH( cFrame* pFrame )
{
	std::vector<D3DXVECTOR3>	vecV;
	std::vector<D3DXVECTOR2>	vecVT;
	std::vector<ST_PNT_VERTEX>	vecVertex;

	int nLevel = 0;

	do 
	{
		char* szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_MESH_NUMVERTEX))
		{
			vecV.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MESH_NUMFACES))
		{
			vecVertex.resize(GetInteger() * 3);
		}
		else if (IsEqual(szToken, ID_MESH_VERTEX_LIST))
		{
			ProcessMESH_VERTEX_LIST(vecV);
		}
		else if (IsEqual(szToken, ID_MESH_FACE_LIST))
		{
			ProcessMESH_FACE_LIST(vecV, vecVertex);
		}
		else if (IsEqual(szToken, ID_MESH_NUMTVERTEX))
		{
			vecVT.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MESH_TVERTLIST))
		{
			ProcessMESH_TVERTLIST(vecVT);
		}
		else if (IsEqual(szToken, ID_MESH_NUMTVFACES))
		{
			GetToken();
		}
		else if (IsEqual(szToken, ID_MESH_TFACELIST))
		{
			ProcessMESH_TFACELIST(vecVT, vecVertex);
		}
		else if (IsEqual(szToken, ID_MESH_NORMALS))
		{
			ProcessMESH_NORMALS(vecVertex);
		}
		
	} while (nLevel > 0);

	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixInverse(&matInvWorld, 0, &pFrame->GetWorldTM());

	for (size_t i = 0; i < vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&vecVertex[i].p, &vecVertex[i].p, &matInvWorld);
		D3DXVec3TransformNormal(&vecVertex[i].n, &vecVertex[i].n, &matInvWorld);
	}

	pFrame->SetVertex(vecVertex);
}

void cAseLoader::ProcessMESH_VERTEX_LIST( std::vector<D3DXVECTOR3>& vecV )
{
	int nLevel = 0;

	do 
	{
		char* szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_MESH_VERTEX))
		{
			int nIndex = GetInteger();
			vecV[nIndex].x = GetFloat();
			vecV[nIndex].z = GetFloat();
			vecV[nIndex].y = GetFloat();
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMESH_FACE_LIST( IN std::vector<D3DXVECTOR3>& vecV, OUT std::vector<ST_PNT_VERTEX>& vecVertex )
{
	int nLevel = 0;

	do 
	{
		char* szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_MESH_FACE))
		{
			int nFaceIndex = GetInteger();
			GetToken();//A:
			int nA = GetInteger();
			GetToken();//B:
			int nB = GetInteger();
			GetToken();//C:
			int nC = GetInteger();
			vecVertex[nFaceIndex * 3 + 0].p = vecV[nA];
			vecVertex[nFaceIndex * 3 + 1].p = vecV[nC];
			vecVertex[nFaceIndex * 3 + 2].p = vecV[nB];
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMESH_TVERTLIST( std::vector<D3DXVECTOR2>& vecVT )
{
	int nLevel = 0;

	do 
	{
		char* szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_MESH_TVERT))
		{
			int nIndex = GetInteger();
			vecVT[nIndex].x = GetFloat();
			vecVT[nIndex].y = 1.0f - GetFloat();
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMESH_TFACELIST( IN std::vector<D3DXVECTOR2>& vecVT, OUT std::vector<ST_PNT_VERTEX>& vecVertex )
{
	int nLevel = 0;

	do 
	{
		char* szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_MESH_TFACE))
		{
			int nFaceIndex = GetInteger();
			int nA = GetInteger();
			int nB = GetInteger();
			int nC = GetInteger();
			vecVertex[nFaceIndex * 3 + 0].t = vecVT[nA];
			vecVertex[nFaceIndex * 3 + 1].t = vecVT[nC];
			vecVertex[nFaceIndex * 3 + 2].t = vecVT[nB];
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMESH_NORMALS( OUT std::vector<ST_PNT_VERTEX>& vecVertex )
{
	int nFaceIndex = 0;
	int nLevel = 0;
	int nCnt = 0;
	int aMod[] = {0, 2, 1};
	do 
	{
		char* szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_MESH_FACENORMAL))
		{
			nFaceIndex = GetInteger();
			nCnt = 0;
		}
		else if (IsEqual(szToken, ID_MESH_VERTEXNORMAL))
		{
			GetInteger();
			vecVertex[nFaceIndex * 3 + aMod[nCnt]].n.x = GetFloat();
			vecVertex[nFaceIndex * 3 + aMod[nCnt]].n.z = GetFloat();
			vecVertex[nFaceIndex * 3 + aMod[nCnt]].n.y = GetFloat();
			++nCnt;
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessNODE_TM( cFrame* pFrame )
{
	D3DXMATRIXA16& matWorld = pFrame->GetWorldTM();

	int nLevel = 0;

	do 
	{
		char* szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_TM_ROW0))
		{
			matWorld._11 = GetFloat();
			matWorld._13 = GetFloat();
			matWorld._12 = GetFloat();
			matWorld._14 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW1))
		{
			matWorld._31 = GetFloat();
			matWorld._33 = GetFloat();
			matWorld._32 = GetFloat();
			matWorld._34 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW2))
		{
			matWorld._21 = GetFloat();
			matWorld._23 = GetFloat();
			matWorld._22 = GetFloat();
			matWorld._24 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW3))
		{
			matWorld._41 = GetFloat();
			matWorld._43 = GetFloat();
			matWorld._42 = GetFloat();
			matWorld._44 = 1.0f;
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessTM_ANIMATION( cFrame* pFrame )
{
	int nLevel = 0;

	do 
	{
		char* szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_POS_TRACK))
		{
			ProcessPOS_TRACK(pFrame);
		}
		else if (IsEqual(szToken, ID_ROT_TRACK))
		{
			ProcessROT_TRACK(pFrame);
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessPOS_TRACK( cFrame* pFrame )
{
	std::vector<ST_POS_SAMPLE> vecPosTrack;

	int nLevel = 0;

	do 
	{
		char* szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_POS_SAMPLE))
		{
			ST_POS_SAMPLE s;
			s.n = GetInteger();
			s.p.x = GetFloat();
			s.p.z = GetFloat();
			s.p.y = GetFloat();

			vecPosTrack.push_back(s);
		}
	} while (nLevel > 0);

	pFrame->SetPosTrack(vecPosTrack);
}

void cAseLoader::ProcessROT_TRACK( cFrame* pFrame )
{
	std::vector<ST_ROT_SAMPLE> vecRotTrack;

	int nLevel = 0;

	do 
	{
		char* szToken = GetToken();

		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_ROT_SAMPLE))
		{
			ST_ROT_SAMPLE s;
			s.n = GetInteger();
			
			// Axis-Angle
			s.q.x = GetFloat();
			s.q.z = GetFloat();
			s.q.y = GetFloat();
			s.q.w = GetFloat();

			// To Quaternion
			s.q.x *= sinf(s.q.w / 2.0f);
			s.q.y *= sinf(s.q.w / 2.0f);
			s.q.z *= sinf(s.q.w / 2.0f);
			s.q.w = cosf(s.q.w / 2.0f);

			// Acc
			if(!vecRotTrack.empty())
			{
				s.q = vecRotTrack.back().q * s.q;
			}
			vecRotTrack.push_back(s);
		}
	} while (nLevel > 0);

	pFrame->SetRotTrack(vecRotTrack);
}
