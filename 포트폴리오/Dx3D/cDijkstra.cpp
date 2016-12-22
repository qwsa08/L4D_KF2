#include "stdafx.h"
#include "cDijkstra.h"
#include "cObjLoader.h"
#include "cRay.h"

#define RADIUS		20.0f
#define NUMOFNODE	73

cDijkstra::cDijkstra()
	: m_pMesh(NULL)
{
}


cDijkstra::~cDijkstra()
{
	SAFE_RELEASE(m_pMesh);
}

void cDijkstra::SetObstacleVertex(OUT std::vector< std::vector<D3DXVECTOR3>>& obsVertex)
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	cObjLoader obl;
	obl.DijkstraLoad("./Map/DijkstraWall.ptop", obsVertex);
}

void cDijkstra::Setup()
{
	//장애물
	SetObstacleVertex(m_vecObstacleVertex);
	//노드
	SetNode();

	D3DXCreateSphere(g_pD3DDevice, RADIUS, 20, 20, &m_pMesh, NULL);
	ZeroMemory(&m_stMtlPicked, sizeof(D3DMATERIAL9));
	m_stMtlPicked.Ambient = m_stMtlPicked.Diffuse = m_stMtlPicked.Specular = D3DXCOLOR(0.8f, 0.0f, 0.0f, 1.0f);

	//엣지코스트
	SetEdgeCost();
	//표
	SetTable();
}

void cDijkstra::Update(D3DXVECTOR3 * vPlayerPos, D3DXVECTOR3 * vZombiePos)
{

}

void cDijkstra::Render()
{
	for each(auto p in m_vecNode)
	{
		D3DXMATRIXA16 matT;
		D3DXMatrixTranslation(&matT, p.vPosition.x, p.vPosition.y, p.vPosition.z);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matT);
		g_pD3DDevice->SetTexture(0, NULL);

		g_pD3DDevice->SetMaterial(&m_stMtlPicked);

		m_pMesh->DrawSubset(0);
	}

	D3DXMATRIXA16 mt;
	D3DXMatrixIdentity(&mt);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mt);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecObstacleVertex[SECTOR_2].size() / 3, &m_vecObstacleVertex[SECTOR_2][0], sizeof(D3DXVECTOR3));
}

void cDijkstra::SetEdgeCost()
{
	m_vecEdgeCost.resize(NUMOFNODE);
	for (int i = 0; i < m_vecEdgeCost.size(); ++i)
	{
		std::vector<float> vecNodeEdge(NUMOFNODE, 10000.f);
		vecNodeEdge[i] = 0.f;
		m_vecEdgeCost[i] = vecNodeEdge;
	}

	//0번 노드
	m_vecEdgeCost[0][1] = GetLength(0, 1);
	//1
	m_vecEdgeCost[1][0] = GetLength(1, 0);
	m_vecEdgeCost[1][2] = GetLength(1, 2);
	m_vecEdgeCost[1][4] = GetLength(1, 4);
	//2
	m_vecEdgeCost[2][1] = GetLength(2, 1);
	m_vecEdgeCost[2][3] = GetLength(2, 3);
	m_vecEdgeCost[2][5] = GetLength(2, 5);
	//3
	m_vecEdgeCost[3][2] = GetLength(3, 2);
	//4
	m_vecEdgeCost[4][1] = GetLength(4, 1);
	m_vecEdgeCost[4][6] = GetLength(4, 6);
	//5
	m_vecEdgeCost[5][2] = GetLength(5, 2);
	m_vecEdgeCost[5][71] = GetLength(5, 71);
	//6
	m_vecEdgeCost[6][4] = GetLength(6, 4);
	m_vecEdgeCost[6][7] = GetLength(6, 7);
	m_vecEdgeCost[6][12] = GetLength(6, 12);
	//7
	m_vecEdgeCost[7][6] = GetLength(7, 6);
	m_vecEdgeCost[7][8] = GetLength(7, 8);
	//8
	m_vecEdgeCost[8][7] = GetLength(8, 7);
	m_vecEdgeCost[8][9] = GetLength(8, 9);
	m_vecEdgeCost[8][10] = GetLength(8, 10);
	//9
	m_vecEdgeCost[9][8] = GetLength(9, 8);
	m_vecEdgeCost[9][10] = GetLength(9, 10);
	m_vecEdgeCost[9][11] = GetLength(9, 11);
	//10
	m_vecEdgeCost[10][8] = GetLength(10, 8);
	m_vecEdgeCost[10][9] = GetLength(10, 9);
	m_vecEdgeCost[10][34] = GetLength(10, 34);
	//11
	m_vecEdgeCost[11][9] = GetLength(11, 9);
	m_vecEdgeCost[11][35] = GetLength(11, 35);
	//12
	m_vecEdgeCost[12][6] = GetLength(12, 6);
	m_vecEdgeCost[12][13] = GetLength(12, 13);
	//13
	m_vecEdgeCost[13][12] = GetLength(13, 12);
	m_vecEdgeCost[13][14] = GetLength(13, 14);
	//14
	m_vecEdgeCost[14][13] = GetLength(14, 13);
	m_vecEdgeCost[14][15] = GetLength(14, 15);
	//15
	m_vecEdgeCost[15][14] = GetLength(15, 14);
	m_vecEdgeCost[15][16] = GetLength(15, 16);
	//16
	m_vecEdgeCost[16][15] = GetLength(16, 15);
	m_vecEdgeCost[16][17] = GetLength(16, 17);
	//17
	m_vecEdgeCost[17][16] = GetLength(17, 16);
	m_vecEdgeCost[17][18] = GetLength(17, 18);
	//18
	m_vecEdgeCost[18][17] = GetLength(18, 17);
	m_vecEdgeCost[18][19] = GetLength(18, 19);
	m_vecEdgeCost[18][21] = GetLength(18, 21);
	//19
	m_vecEdgeCost[19][18] = GetLength(19, 18);
	m_vecEdgeCost[19][20] = GetLength(19, 20);
	//20
	m_vecEdgeCost[20][19] = GetLength(20, 19);
	m_vecEdgeCost[20][22] = GetLength(20, 22);
	m_vecEdgeCost[20][23] = GetLength(20, 23);
	//21
	m_vecEdgeCost[21][18] = GetLength(21, 18);
	m_vecEdgeCost[21][24] = GetLength(21, 24);
	//22
	m_vecEdgeCost[22][20] = GetLength(22, 20);
	m_vecEdgeCost[22][25] = GetLength(22, 25);
	m_vecEdgeCost[22][27] = GetLength(22, 27);
	//23
	m_vecEdgeCost[23][20] = GetLength(23, 20);
	m_vecEdgeCost[23][24] = GetLength(23, 24);
	m_vecEdgeCost[23][25] = GetLength(23, 25);
	//24
	m_vecEdgeCost[24][21] = GetLength(24, 21);
	m_vecEdgeCost[24][23] = GetLength(24, 23);
	//25
	m_vecEdgeCost[25][22] = GetLength(25, 22);
	m_vecEdgeCost[25][23] = GetLength(25, 23);
	//26
	m_vecEdgeCost[26][27] = GetLength(26, 27);
	m_vecEdgeCost[26][51] = GetLength(26, 51);
	//27
	m_vecEdgeCost[27][22] = GetLength(27, 22);
	m_vecEdgeCost[27][26] = GetLength(27, 26);
	m_vecEdgeCost[27][28] = GetLength(27, 28);
	//28
	m_vecEdgeCost[28][27] = GetLength(28, 27);
	m_vecEdgeCost[28][30] = GetLength(28, 30);
	//29
	m_vecEdgeCost[29][30] = GetLength(29, 30);
	//30
	m_vecEdgeCost[30][28] = GetLength(30, 28);
	m_vecEdgeCost[30][29] = GetLength(30, 29);
	m_vecEdgeCost[30][31] = GetLength(30, 31);
	m_vecEdgeCost[30][32] = GetLength(30, 32);
	//31
	m_vecEdgeCost[31][30] = GetLength(31, 30);
	//32
	m_vecEdgeCost[32][30] = GetLength(32, 30);
	m_vecEdgeCost[32][33] = GetLength(32, 33);
	//33
	m_vecEdgeCost[33][32] = GetLength(33, 32);
	m_vecEdgeCost[33][34] = GetLength(33, 34);
	//34
	m_vecEdgeCost[34][10] = GetLength(34, 10);
	m_vecEdgeCost[34][33] = GetLength(34, 33);
	//35
	m_vecEdgeCost[35][11] = GetLength(35, 11);
	m_vecEdgeCost[35][36] = GetLength(35, 36);
	//36
	m_vecEdgeCost[36][35] = GetLength(36, 35);
	m_vecEdgeCost[36][37] = GetLength(36, 37);
	m_vecEdgeCost[36][38] = GetLength(36, 38);
	//37
	m_vecEdgeCost[37][36] = GetLength(37, 36);
	m_vecEdgeCost[37][38] = GetLength(37, 38);
	m_vecEdgeCost[37][39] = GetLength(37, 39);
	//38
	m_vecEdgeCost[38][36] = GetLength(38, 36);
	m_vecEdgeCost[38][37] = GetLength(38, 37);
	//39
	m_vecEdgeCost[39][37] = GetLength(39, 37);
	m_vecEdgeCost[39][40] = GetLength(39, 40);
	//40
	m_vecEdgeCost[40][39] = GetLength(40, 39);
	m_vecEdgeCost[40][41] = GetLength(40, 41);
	//41
	m_vecEdgeCost[41][40] = GetLength(41, 40);
	m_vecEdgeCost[41][42] = GetLength(41, 42);
	//42
	m_vecEdgeCost[42][41] = GetLength(42, 41);
	m_vecEdgeCost[42][43] = GetLength(42, 43);
	//43
	m_vecEdgeCost[43][42] = GetLength(43, 42);
	m_vecEdgeCost[43][44] = GetLength(43, 44);
	//44
	m_vecEdgeCost[44][43] = GetLength(44, 43);
	m_vecEdgeCost[44][45] = GetLength(44, 45);
	m_vecEdgeCost[44][46] = GetLength(44, 46);
	//45
	m_vecEdgeCost[45][44] = GetLength(45, 44);
	//46
	m_vecEdgeCost[46][44] = GetLength(46, 44);
	m_vecEdgeCost[46][47] = GetLength(46, 47);
	m_vecEdgeCost[46][49] = GetLength(46, 49);
	//47
	m_vecEdgeCost[47][46] = GetLength(47, 46);
	m_vecEdgeCost[47][48] = GetLength(47, 48);
	//48
	m_vecEdgeCost[48][47] = GetLength(48, 47);
	m_vecEdgeCost[48][49] = GetLength(48, 49);
	//49
	m_vecEdgeCost[49][46] = GetLength(49, 46);
	m_vecEdgeCost[49][48] = GetLength(49, 48);
	m_vecEdgeCost[49][54] = GetLength(49, 54);
	//50
	m_vecEdgeCost[50][55] = GetLength(50, 55);
	//51
	m_vecEdgeCost[51][26] = GetLength(51, 26);
	m_vecEdgeCost[51][52] = GetLength(51, 52);
	//52
	m_vecEdgeCost[52][51] = GetLength(52, 51);
	m_vecEdgeCost[52][53] = GetLength(52, 53);
	//53
	m_vecEdgeCost[53][52] = GetLength(53, 52);
	m_vecEdgeCost[53][54] = GetLength(53, 54);
	//54
	m_vecEdgeCost[54][49] = GetLength(54, 49);
	m_vecEdgeCost[54][53] = GetLength(54, 53);
	m_vecEdgeCost[54][55] = GetLength(54, 55);
	m_vecEdgeCost[54][56] = GetLength(54, 56);
	//55
	m_vecEdgeCost[55][50] = GetLength(55, 50);
	m_vecEdgeCost[55][54] = GetLength(55, 54);
	//56
	m_vecEdgeCost[56][54] = GetLength(56, 54);
	m_vecEdgeCost[56][57] = GetLength(56, 57);
	//57
	m_vecEdgeCost[57][56] = GetLength(57, 56);
	m_vecEdgeCost[57][58] = GetLength(57, 58);
	//58
	m_vecEdgeCost[58][57] = GetLength(58, 57);
	m_vecEdgeCost[58][72] = GetLength(58, 72);
	//59
	m_vecEdgeCost[59][60] = GetLength(59, 60);
	m_vecEdgeCost[59][72] = GetLength(59, 72);
	//60
	m_vecEdgeCost[60][59] = GetLength(60, 59);
	m_vecEdgeCost[60][61] = GetLength(60, 61);
	m_vecEdgeCost[60][62] = GetLength(60, 62);
	//61
	m_vecEdgeCost[61][60] = GetLength(61, 60);
	//62
	m_vecEdgeCost[62][60] = GetLength(62, 60);
	m_vecEdgeCost[62][63] = GetLength(62, 63);
	m_vecEdgeCost[62][64] = GetLength(62, 64);
	//63
	m_vecEdgeCost[63][62] = GetLength(63, 62);
	m_vecEdgeCost[63][64] = GetLength(63, 64);
	m_vecEdgeCost[63][65] = GetLength(63, 65);
	//64
	m_vecEdgeCost[64][62] = GetLength(64, 62);
	m_vecEdgeCost[64][63] = GetLength(64, 63);
	//65
	m_vecEdgeCost[65][63] = GetLength(65, 63);
	m_vecEdgeCost[65][66] = GetLength(65, 66);
	//66
	m_vecEdgeCost[66][65] = GetLength(66, 65);
	m_vecEdgeCost[66][67] = GetLength(66, 67);
	//67
	m_vecEdgeCost[67][66] = GetLength(67, 66);
	m_vecEdgeCost[67][68] = GetLength(67, 68);
	//68
	m_vecEdgeCost[68][67] = GetLength(68, 67);
	m_vecEdgeCost[68][69] = GetLength(68, 69);
	//69
	m_vecEdgeCost[69][68] = GetLength(69, 68);
	m_vecEdgeCost[69][71] = GetLength(69, 71);
	//70
	m_vecEdgeCost[70][71] = GetLength(71, 68);
	//71
	m_vecEdgeCost[71][5] = GetLength(71, 5);
	m_vecEdgeCost[71][69] = GetLength(71, 69);
	m_vecEdgeCost[71][70] = GetLength(71, 70);
	//72
	m_vecEdgeCost[72][58] = GetLength(72, 58);
	m_vecEdgeCost[72][59] = GetLength(72, 59);
}

void cDijkstra::SetTable()
{
	for (int i = 0; i < m_vecNode.size(); ++i)
	{
		std::vector<ST_NODE> table = MakeTable(i);
		m_vecNodeTable.push_back(table);
	}
}

std::vector<ST_NODE> cDijkstra::MakeTable(int nStart)
{
	std::vector<ST_NODE> vN = m_vecNode;
	//1이 출발노드일 경우
	int nVia = nStart;
	vN[nVia].nViaNode = nVia;
	vN[nVia].fTotalCost = 0.f;

	for (int k = 0; k < vN.size(); ++k)
	{
		for (int i = 0; i < vN.size(); ++i)
		{
			if (vN[i].isClosed == false)
				nVia = i;
			else continue;

			break;
		}
		for (int i = 0; i < vN.size(); ++i)
		{
			//1.클로즈 안된 노드중 코스트가 가장 작은 노드 찾기
			if (vN[i].isClosed == false)
			{
				if (vN[nVia].fTotalCost > vN[i].fTotalCost)
				{
					nVia = i;	//경유노드.
				}
				else continue;
			}
			else continue;
		}
		vN[nVia].isClosed = true;	//경유노드 클로즈
										//2. 출발노드에서 다른 노드로 가는 경로 갱신
		for (int i = 0; i < vN.size(); ++i)
		{
			if (vN[i].isClosed == true) continue;	//클로즈상태면 갱신노노?
			//출발노드에서 경유노드까지의 코스트 + 경유에서 목적까지 엣지코스트 가 토탈코스트보다 작으면
			if (vN[i].fTotalCost >(vN[nVia].fTotalCost) + (m_vecEdgeCost[nVia][i]))
			{
				//via 갱신 totalCost 갱신
				vN[i].nViaNode = nVia;
				vN[i].fTotalCost = (vN[nVia].fTotalCost) + (m_vecEdgeCost[nVia][i]);
			}
			else continue;
		}
		//3. 이짓을 다 채워질 때까지 반복.
	}

	return vN;
}

SECTOR cDijkstra::SetSector(D3DXVECTOR3* vPos)
{
	if ((*vPos).z > 800)	//1
	{
		return SECTOR_1;
	}
	else if ((*vPos).z > 380)	//2 , 3
	{
		if ((*vPos).x < -385)
		{
			return SECTOR_4;
		}
		else if ((*vPos).x < 640)
		{
			return SECTOR_2;
		}
		else if ((*vPos).x >= 790 && (*vPos).x < 1550)
		{
			return SECTOR_3;
		}
		else if ((*vPos).x >= 1550)
		{
			return SECTOR_8;
		}
	}
	else if ((*vPos).z > -400)	//5
	{
		if ((*vPos).x < -385)
		{
			return SECTOR_4;
		}
		else if ((*vPos).x < 790)
		{
			return SECTOR_5;
		}
		else return SECTOR_8;
	}
	else if ((*vPos).z > -950)	//6
	{
		if ((*vPos).x < -385)
		{
			return SECTOR_4;
		}
		else if ((*vPos).x < 500)
		{
			return SECTOR_6;
		}
		else 
			return SECTOR_8;
	}
	else //7
	{
		if ((*vPos).x < -385)
		{
			return SECTOR_4;
		}
		else if ((*vPos).x < 600)
		{
			return SECTOR_7;
		}
		else 
			return SECTOR_8;
	}

	return SECTOR_NONE;
}

int cDijkstra::GetFirstNode(D3DXVECTOR3 * vPos)
{
	SECTOR eSector = SetSector(vPos);
	std::vector<int> vecNodeIndex;
	std::vector<D3DXVECTOR3> vecObs = m_vecObstacleVertex[eSector];
	GetSectorNode(eSector, vecNodeIndex);

	//가까운 노드를 찾아서 다이렉트를 체크하자.. 다이렉트 체크 노노
	
	return GetNearestNodeIndex(&vecNodeIndex, vPos);
}

void cDijkstra::GetSectorNode(IN SECTOR eSector, OUT std::vector<int>& vecNode)
{
	switch (eSector)
	{
	case SECTOR_1:
	{
		vecNode.push_back(0);
		vecNode.push_back(1);
		vecNode.push_back(2);
		vecNode.push_back(3);
		vecNode.push_back(4);
		vecNode.push_back(5);
		vecNode.push_back(6);
		vecNode.push_back(71);
	}
		break;
	case SECTOR_2:
	{
		vecNode.push_back(4);
		vecNode.push_back(6);
		vecNode.push_back(7);
		vecNode.push_back(12);
		vecNode.push_back(13);
		vecNode.push_back(14);
		vecNode.push_back(15);
		vecNode.push_back(16);
		vecNode.push_back(17);
		vecNode.push_back(18);
	}
		break;
	case SECTOR_3:
	{
		vecNode.push_back(5);
		vecNode.push_back(63);
		vecNode.push_back(65);
		vecNode.push_back(66);
		vecNode.push_back(67);
		vecNode.push_back(68);
		vecNode.push_back(69);
		vecNode.push_back(70);
		vecNode.push_back(71);
	}
		break;
	case SECTOR_4:
	{
		vecNode.push_back(7);
		vecNode.push_back(8);
		vecNode.push_back(9);
		vecNode.push_back(10);
		vecNode.push_back(11);
		vecNode.push_back(29);
		vecNode.push_back(30);
		vecNode.push_back(32);
		vecNode.push_back(33);
		vecNode.push_back(34);
		vecNode.push_back(35);
		vecNode.push_back(36);
		vecNode.push_back(37);
		vecNode.push_back(38);
		vecNode.push_back(39);
		vecNode.push_back(40);
		vecNode.push_back(41);
		vecNode.push_back(42);
		vecNode.push_back(43);
		vecNode.push_back(44);
	}
		break;
	case SECTOR_5:
	{
		vecNode.push_back(6);
		vecNode.push_back(7);
		vecNode.push_back(8);
		vecNode.push_back(17);
		vecNode.push_back(18);
		vecNode.push_back(19);
		vecNode.push_back(20);
		vecNode.push_back(21);
		vecNode.push_back(22);
		vecNode.push_back(23);
		vecNode.push_back(24);
		vecNode.push_back(25);
		vecNode.push_back(26);
		vecNode.push_back(27);
		vecNode.push_back(28);
		vecNode.push_back(30);
		vecNode.push_back(31);
		vecNode.push_back(32);
		vecNode.push_back(51);
	}
		break;
	case SECTOR_6:
	{
		vecNode.push_back(26);
		vecNode.push_back(49);
		vecNode.push_back(50);
		vecNode.push_back(51);
		vecNode.push_back(52);
		vecNode.push_back(53);
		vecNode.push_back(54);
		vecNode.push_back(55);
		vecNode.push_back(56);
		vecNode.push_back(57);
		vecNode.push_back(58);
	}
		break;
	case SECTOR_7:
	{
		vecNode.push_back(43);
		vecNode.push_back(44);
		vecNode.push_back(45);
		vecNode.push_back(46);
		vecNode.push_back(47);
		vecNode.push_back(48);
		vecNode.push_back(49);
		vecNode.push_back(50);
		vecNode.push_back(54);
		vecNode.push_back(55);
	}
		break;
	case SECTOR_8:
	{
		vecNode.push_back(57);
		vecNode.push_back(58);
		vecNode.push_back(59);
		vecNode.push_back(60);
		vecNode.push_back(61);
		vecNode.push_back(62);
		vecNode.push_back(63);
		vecNode.push_back(64);
		vecNode.push_back(65);
		vecNode.push_back(72);
	}
		break;
	default:
		break;
	}
}

int cDijkstra::GetNearestNodeIndex(std::vector<int>* vecIndex, D3DXVECTOR3* vPos)
{
	float minLength = D3DXVec3Length(&(*vPos - m_vecNode[(*vecIndex)[0]].vPosition));
	int minIndex = 0;
	for (int i = 0; i < (*vecIndex).size(); ++i)
	{
		float length = D3DXVec3Length(&(*vPos - m_vecNode[(*vecIndex)[i]].vPosition));

		if (minLength > length)
		{
			minIndex = i;
			minLength = length;
		}
	}

	return (*vecIndex)[minIndex];
}

std::vector<int> cDijkstra::GetNodeTable(int nStart, int nDest)
{
	std::vector<int> vecNode;

	int nIndex = nStart;
	vecNode.push_back(nIndex);
	while (nIndex != nDest)
	{
		vecNode.push_back(m_vecNodeTable[nDest][nIndex].nViaNode);
		nIndex = m_vecNodeTable[nDest][nIndex].nViaNode;
	}
	
	return vecNode;
}

bool cDijkstra::Intersect(std::vector<D3DXVECTOR3>* vecObs, D3DXVECTOR3 * vFrom, D3DXVECTOR3 * vTo)
{
	D3DXVECTOR3 vF = *vFrom;// +D3DXVECTOR3(0, 70, 0);
	float u, v, d = 0.f;
	float length = D3DXVec3Length(&(*vTo - vF));

	for (int i = 0; i < (*vecObs).size(); i += 3)
	{
		D3DXVECTOR3 vNormal = (*vTo - vF);
		D3DXVec3Normalize(&vNormal, &vNormal);
		if (D3DXIntersectTri(&(*vecObs)[i], &(*vecObs)[i + 1], &(*vecObs)[i + 2], &vF, &vNormal, &u, &v, &d))
		{
			if (d < length)	//충돌하는데 d가 거리보다 짧다면 충돌 ㅇㅇ
			{
				return false;
			}
		}
	}

	return true;
}

bool cDijkstra::IsDirect(D3DXVECTOR3* vFrom, D3DXVECTOR3* vTo)
{
	m_eFromSector = SetSector(vFrom);
	m_eToSector = SetSector(vTo);

	if (m_eFromSector == m_eToSector)	//같은 구역에 있다면
	{
		std::vector<D3DXVECTOR3> vecObs = m_vecObstacleVertex[m_eFromSector];

		return Intersect(&vecObs, vFrom, vTo);
	}
	else  //다른 구역에 있다면..'ㅅ`
	{
		std::vector<D3DXVECTOR3> vecObs = m_vecObstacleVertex[m_eFromSector];
		std::vector<D3DXVECTOR3> vecObs2 = m_vecObstacleVertex[m_eToSector];

		vecObs.insert(vecObs.end(), vecObs2.begin(), vecObs2.end());

		return Intersect(&vecObs, vFrom, vTo);		
	}

	return true;
}

std::vector<D3DXVECTOR3> cDijkstra::GetRoute(D3DXVECTOR3* vFrom, D3DXVECTOR3* vTo)
{
	int nStart = GetFirstNode(vFrom);
	int nDest = GetFirstNode(vTo);
	std::vector<int> vecRoute = GetNodeTable(nStart, nDest);

	//일단 그냥 쓰자
	std::vector<D3DXVECTOR3> vec;
	vec.resize(vecRoute.size());
	for (int i = 0; i < vecRoute.size(); ++i)
	{
		vec[i] = m_vecNode[vecRoute[i]].vPosition;
	}

	return vec;
}

void cDijkstra::SetNode()
{
	ST_NODE node;
	node.vPosition = D3DXVECTOR3(-400, -140, 2200);	//0
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-250, -140, 1250);	//1
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(1100, -140, 1250);	//2
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(1200, -140, 2200);	//3
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-250, -120, 950);	//4
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(920, -120, 950);	//5
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-250, -120, 470);	//6
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-300, -120, 200);	//7
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-600, -120, 150);	//8
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-850, -120, 150);	//9
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-850, -120, -50);	//10
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-880, -120, 450);	//11
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-20, -105, 470);	//12
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-20, -105, 675);	//13
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(115, -105, 675);	//14
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(360, -105, 675);	//15
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(360, -105, 490);	//16
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(550, -105, 490);	//17
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(550, -120, 300);	//18
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(295, -120, 300);	//19
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(295, -120, 150);	//20
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(550, -120, 150);	//21
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(100, -120, -50);	//22
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(430, -120, -50);	//23
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(650, -120, -50);	//24
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(300, -120, -200);	//25
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-50, -120, -330);	//26
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-100, -120, -60);	//27
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-260, -115, -60);	//28
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-440, -115, -60);	//29
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-330, -115, -200);	//30
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-260, -115, -330);	//31
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-440, -115, -340);	//32
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-600, -115, -340);	//33
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-850, -115, -220);	//34
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-1100, -140, 450);	//35
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-1330, -140, 450);	//36
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-1100, -140, -550);	//37 
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-1300, -140, -1000);	//38
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-880, -120, -550);	//39
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-530, -120, -720);	//40
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-560, -120, -1020);	//41
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-450, -120, -1020);	//42
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-540, -120, -1290);	//43
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-330, -120, -1300);	//44
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-330, -120, -1500);	//45
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-130, -120, -1350);	//46
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(70, -120, -1550);	//47
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(270, -120, -1350);	//48
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(170, -120, -1130);	//49
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(410, -120, -1050);	//50
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-50, -120, -510);	//51
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-270, -120, -510);	//52
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-270, -120, -850);	//53
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(170, -120, -850);	//54
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(330, -120, -850);	//55
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(170, -105, -700);	//56
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(410, -105, -600);	//57
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(570, -105, -600);	//58
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(970, -120, -900);	//59
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(1220, -140, -900);	//60
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(1220, -120, -1200);	//61
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(1220, -140, 80);	//62
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(1450, -120, 270);	//63
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(2680, -140, 150);	//64
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(1450, -105, 530);	//65
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(1340, -105, 570);	//66
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(1340, -105, 740);	//67
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(1250, -105, 740);	//68
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(1100, -105, 740);	//69
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(940, -105, 580);	//70
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(920, -105, 740);	//71
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(810, -105, -900);	//72
	m_vecNode.push_back(node);
}

float cDijkstra::GetLength(int nFrom, int nTo)
{
	return D3DXVec3Length(&(m_vecNode[nFrom].vPosition - m_vecNode[nTo].vPosition));
}
