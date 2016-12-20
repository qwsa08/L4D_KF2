#include "stdafx.h"
#include "cDijkstra.h"
#include "cObjLoader.h"
#include "cRay.h"

#define RADIUS		20.0f
#define NUMOFNODE	41

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
	//노드
	SetNode();

	D3DXCreateSphere(g_pD3DDevice, RADIUS, 20, 20, &m_pMesh, NULL);
	ZeroMemory(&m_stMtlPicked, sizeof(D3DMATERIAL9));
	m_stMtlPicked.Ambient = m_stMtlPicked.Diffuse = m_stMtlPicked.Specular = D3DXCOLOR(0.8f, 0.0f, 0.0f, 1.0f);

	//엣지코스트
	SetEdgeCost();
	//표
	SetTable();
	//장애물
	SetObstacleVertex(m_vecObstacleVertex);
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

//	D3DXMATRIXA16 mt;
//	D3DXMatrixIdentity(&mt);
//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mt);
//	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecObstacleVertex[SECTOR_5].size() / 3, &m_vecObstacleVertex[SECTOR_5][0], sizeof(D3DXVECTOR3));
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
	m_vecEdgeCost[1][3] = GetLength(1, 3);
	m_vecEdgeCost[1][4] = GetLength(1, 4);
	//2
	m_vecEdgeCost[2][3] = GetLength(2, 3);
	//3
	m_vecEdgeCost[3][1] = GetLength(3, 1);
	m_vecEdgeCost[3][2] = GetLength(3, 2);
	m_vecEdgeCost[3][32] = GetLength(3, 32);
	//4
	m_vecEdgeCost[4][1] = GetLength(4, 1);
	m_vecEdgeCost[4][5] = GetLength(4, 5);
	m_vecEdgeCost[4][10] = GetLength(4, 10);
	//5
	m_vecEdgeCost[5][4] = GetLength(5, 4);
	m_vecEdgeCost[5][6] = GetLength(5, 6);
	m_vecEdgeCost[5][17] = GetLength(5, 17);
	//6
	m_vecEdgeCost[6][5] = GetLength(6, 5);
	m_vecEdgeCost[6][7] = GetLength(6, 7);
	//7
	m_vecEdgeCost[7][6] = GetLength(7, 6);
	m_vecEdgeCost[7][8] = GetLength(7, 8);
	//8
	m_vecEdgeCost[8][7] = GetLength(8, 7);
	m_vecEdgeCost[8][9] = GetLength(8, 9);
	m_vecEdgeCost[8][28] = GetLength(8, 28);
	//9
	m_vecEdgeCost[9][8] = GetLength(9, 8);
	//10
	m_vecEdgeCost[10][4] = GetLength(10, 4);
	m_vecEdgeCost[10][11] = GetLength(10, 11);
	//11
	m_vecEdgeCost[11][10] = GetLength(11, 10);
	m_vecEdgeCost[11][12] = GetLength(11, 12);
	//12
	m_vecEdgeCost[12][11] = GetLength(12, 11);
	m_vecEdgeCost[12][13] = GetLength(12, 13);
	m_vecEdgeCost[12][18] = GetLength(12, 18);
	//13
	m_vecEdgeCost[13][12] = GetLength(13, 12);
	m_vecEdgeCost[13][14] = GetLength(13, 14);
	//14
	m_vecEdgeCost[14][13] = GetLength(14, 13);
	m_vecEdgeCost[14][15] = GetLength(14, 15);
	//15
	m_vecEdgeCost[15][14] = GetLength(15, 14);
	m_vecEdgeCost[15][18] = GetLength(15, 18);
	m_vecEdgeCost[15][19] = GetLength(15, 19);
	m_vecEdgeCost[15][40] = GetLength(15, 40);
	//16
	m_vecEdgeCost[16][40] = GetLength(16, 40);
	m_vecEdgeCost[16][17] = GetLength(16, 17);
	//17
	m_vecEdgeCost[17][5] = GetLength(17, 5);
	m_vecEdgeCost[17][16] = GetLength(17, 16);
	//18
	m_vecEdgeCost[18][12] = GetLength(18, 12);
	m_vecEdgeCost[18][15] = GetLength(18, 15);
	//19
	m_vecEdgeCost[19][15] = GetLength(19, 15);
	m_vecEdgeCost[19][20] = GetLength(19, 20);
	//20
	m_vecEdgeCost[20][19] = GetLength(20, 19);
	m_vecEdgeCost[20][21] = GetLength(20, 21);
	//21
	m_vecEdgeCost[21][20] = GetLength(21, 20);
	m_vecEdgeCost[21][22] = GetLength(21, 22);
	//22
	m_vecEdgeCost[22][21] = GetLength(22, 21);
	m_vecEdgeCost[22][23] = GetLength(22, 23);
	m_vecEdgeCost[22][24] = GetLength(22, 24);
	m_vecEdgeCost[22][29] = GetLength(22, 29);
	m_vecEdgeCost[22][30] = GetLength(22, 30);
	//23
	m_vecEdgeCost[23][22] = GetLength(23, 22);
	m_vecEdgeCost[23][25] = GetLength(23, 25);
	m_vecEdgeCost[23][26] = GetLength(23, 26);
	//24
	m_vecEdgeCost[24][22] = GetLength(24, 22);
	m_vecEdgeCost[24][25] = GetLength(24, 25);
	//25
	m_vecEdgeCost[25][23] = GetLength(25, 23);
	m_vecEdgeCost[25][24] = GetLength(25, 24);
	//26
	m_vecEdgeCost[26][23] = GetLength(26, 23);
	m_vecEdgeCost[26][27] = GetLength(26, 27);
	//27
	m_vecEdgeCost[27][26] = GetLength(27, 26);
	m_vecEdgeCost[27][28] = GetLength(27, 28);
	//28
	m_vecEdgeCost[28][8] = GetLength(28, 8);
	m_vecEdgeCost[28][27] = GetLength(28, 27);
	//29
	m_vecEdgeCost[29][22] = GetLength(29, 22);
	m_vecEdgeCost[29][30] = GetLength(29, 30);
	m_vecEdgeCost[29][31] = GetLength(29, 31);
	//30
	m_vecEdgeCost[30][22] = GetLength(30, 22);
	m_vecEdgeCost[30][29] = GetLength(30, 29);
	//31
	m_vecEdgeCost[31][29] = GetLength(31, 29);
	m_vecEdgeCost[31][37] = GetLength(31, 37);
	//32
	m_vecEdgeCost[32][3] = GetLength(32, 3);
	m_vecEdgeCost[32][33] = GetLength(32, 33);
	m_vecEdgeCost[32][34] = GetLength(32, 34);
	//33
	m_vecEdgeCost[33][32] = GetLength(33, 32);
	//34
	m_vecEdgeCost[34][32] = GetLength(34, 32);
	m_vecEdgeCost[34][35] = GetLength(34, 35);
	//35
	m_vecEdgeCost[35][34] = GetLength(35, 34);
	m_vecEdgeCost[35][36] = GetLength(35, 36);
	//36
	m_vecEdgeCost[36][35] = GetLength(36, 35);
	m_vecEdgeCost[36][37] = GetLength(36, 37);
	m_vecEdgeCost[36][39] = GetLength(36, 39);
	//37
	m_vecEdgeCost[37][31] = GetLength(37, 31);
	m_vecEdgeCost[37][36] = GetLength(37, 36);
	m_vecEdgeCost[37][38] = GetLength(37, 38);
	//38
	m_vecEdgeCost[38][37] = GetLength(38, 37);
	//39
	m_vecEdgeCost[39][36] = GetLength(39, 36);
	//40
	m_vecEdgeCost[40][15] = GetLength(40, 15);
	m_vecEdgeCost[40][16] = GetLength(40, 16);
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

	int nIndex = 0;
	//가까운 노드를 찾아서 다이렉트를 체크하자..
	for (int i = 0; i < vecNodeIndex.size(); ++i)
	{
		nIndex = GetNearestNodeIndex(&vecNodeIndex, vPos);
		if (IsDirect(vPos, &m_vecNode[nIndex].vPosition) == false)	continue;
		else break;
	}
	
	return nIndex;
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
	}
		break;
	case SECTOR_2:
	{
		vecNode.push_back(4);
		vecNode.push_back(10);
		vecNode.push_back(11);
	}
		break;
	case SECTOR_3:
	{
		vecNode.push_back(32);
		vecNode.push_back(33);
		vecNode.push_back(34);
		vecNode.push_back(35);
	}
		break;
	case SECTOR_4:
	{
		vecNode.push_back(5);
		vecNode.push_back(6);
		vecNode.push_back(7);
		vecNode.push_back(8);
		vecNode.push_back(9);
		vecNode.push_back(16);
		vecNode.push_back(17);
		vecNode.push_back(26);
		vecNode.push_back(27);
		vecNode.push_back(28);
	}
		break;
	case SECTOR_5:
	{
		vecNode.push_back(12);
		vecNode.push_back(13);
		vecNode.push_back(14);
		vecNode.push_back(15);
		vecNode.push_back(18);
		vecNode.push_back(19);
		vecNode.push_back(20);
		vecNode.push_back(40);
	}
		break;
	case SECTOR_6:
	{
		vecNode.push_back(21);
		vecNode.push_back(22);
		vecNode.push_back(29);

	}
		break;
	case SECTOR_7:
	{
		vecNode.push_back(23);
		vecNode.push_back(24);
		vecNode.push_back(25);
		vecNode.push_back(30);
	}
		break;
	case SECTOR_8:
	{
		vecNode.push_back(31);
		vecNode.push_back(36);
		vecNode.push_back(37);
		vecNode.push_back(38);
		vecNode.push_back(39);
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
	//
	////저기서 직접 갈수 있는.............
	//int nS = 0;
	////시작점
	//for (int i = 0; i < vecRoute.size(); ++i)
	//{
	//	if (IsDirect(vFrom, &m_vecNode[vecRoute[i]].vPosition))
	//	{
	//		nS = i;
	//	}
	//}
	//
	//if (nS > 0)	vecRoute.erase(vecRoute.begin(), vecRoute.begin() + nS - 1);

	////끝점
	//int nD = vecRoute.size() - 1;
	//for (int i = vecRoute.size() - 1; i >= 0; --i)
	//{
	//	if (IsDirect(vTo, &m_vecNode[vecRoute[i]].vPosition))
	//	{
	//		nD = i;
	//	}
	//}

	//if (nD < vecRoute.size() - 1) vecRoute.erase(vecRoute.end() - nD, vecRoute.end());

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
	node.vPosition = D3DXVECTOR3(-500, -140, 2200);	//0
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-250, -140, 1200);	//1
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(1400, -140, 2200);	//2
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(900, -140, 1200);	//3
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-250, -120, 400);	//4
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-850, -120, -50);	//5
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-950, -120, 450);	//6
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-1300, -120, 400);	//7
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-1250, -120, -400);	//8
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-1300, -120, -900);	//9
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(100, -105, 670);	//10
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(350, -105, 670);	//11
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(630, -120, 300);	//12
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(300, -120, 300);	//13
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(250, -120, 150);	//14
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(0, -120, -50);		//15
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-400, -120, -300);	//16
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-850, -120, -350);	//17
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(300, -120, -200);	//18
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(50, -120, -330);	//19
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-280, -120, -600);	//20
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-280, -120, -870);	//21
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(90, -120, -870);	//22
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-150, -120, -1350);	//23
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(280, -120, -1350);	//24
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(90, -120, -1600);	//25
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-550, -120, -1300);	//26
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-450, -120, -1100);	//27
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-600, -120, -700);	//28
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(250, -120, -600);	//29
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(490, -120, -1150);	//30
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(700, -120, -830);	//31
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(920, -105, 730);	//32
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(950, -105, 450);	//33
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(1300, -105, 730);	//34
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(1420, -105, 470);	//35
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(1500, -120, 100);	//36
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(1200, -120, -830);	//37 
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(1200, -120, -1200);	//38
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(2500, -120, 100);	//39
	m_vecNode.push_back(node);
	node.vPosition = D3DXVECTOR3(-250, -120, -80);	//40
	m_vecNode.push_back(node);
}

float cDijkstra::GetLength(int nFrom, int nTo)
{
	return D3DXVec3Length(&(m_vecNode[nFrom].vPosition - m_vecNode[nTo].vPosition));
}
