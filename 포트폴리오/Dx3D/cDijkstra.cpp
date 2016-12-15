#include "stdafx.h"
#include "cDijkstra.h"

#define RADIUS		20.0f
#define NUMOFNODE	42

cDijkstra::cDijkstra()
	: m_pMesh(NULL)
{
}


cDijkstra::~cDijkstra()
{
	SAFE_RELEASE(m_pMesh);
}

void cDijkstra::SetObstacleVertex(std::vector<D3DXVECTOR3> obsVertex)
{
	m_vecObstacleVertex.push_back(obsVertex);
}

void cDijkstra::Setup()
{
	//노드
	SetNode();
	D3DXCreateSphere(g_pD3DDevice, RADIUS, 20, 20, &m_pMesh, NULL);

	ZeroMemory(&m_stMtlNormal, sizeof(D3DMATERIAL9));
	m_stMtlNormal.Ambient = m_stMtlNormal.Diffuse = m_stMtlNormal.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	ZeroMemory(&m_stMtlPicked, sizeof(D3DMATERIAL9));
	m_stMtlPicked.Ambient = m_stMtlPicked.Diffuse = m_stMtlPicked.Specular = D3DXCOLOR(0.8f, 0.0f, 0.0f, 1.0f);

	//엣지코스트
	SetEdgeCost();
	//표
	SetTable();
	int a = 0;
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

int cDijkstra::GetFirstNode(D3DXVECTOR3 * vPos)
{
	int nIndex = 0;
	for (int i = 0; i < m_vecNode.size(); ++i)
	{
		if (D3DXVec3Length(&(*vPos - m_vecNode[nIndex].vPosition)) > D3DXVec3Length(&(*vPos - m_vecNode[i].vPosition)))
		{
			nIndex = i;
		}
	}
	return nIndex;
}

std::vector<D3DXVECTOR3> cDijkstra::GetNodeTable(int nStart, int nDest)
{
	std::vector<D3DXVECTOR3> vecNode;

	int nIndex = nStart;
	while (nIndex != nDest)
	{
		vecNode.push_back(m_vecNodeTable[nDest][nIndex].vPosition);
		nIndex = m_vecNodeTable[nDest][nIndex].nViaNode;
	}
	vecNode.push_back(m_vecNode[nDest].vPosition);
	
	return vecNode;
}

bool cDijkstra::IsDirect(D3DXVECTOR3 vFrom, D3DXVECTOR3 vTo)
{
	if (vFrom.z > 800)	//1
	{
		m_eZombieSector = SECTOR_1;
	}
	else if (vFrom.z > 380)	//2 , 3
	{
		if (vFrom.x < -385)
		{
			m_eZombieSector = SECTOR_4;
		}
		else if (vFrom.x < 640)
		{
			m_eZombieSector = SECTOR_2;
		}
		else if (vFrom.x >= 790 && vFrom.x < 1550)
		{
			m_eZombieSector = SECTOR_3;
		}
		else if (vFrom.x >= 1550)
		{
			m_eZombieSector = SECTOR_8;
		}
		else
		{
			m_eZombieSector = SECTOR_NONE;
		}
	}
	else if (vFrom.z > -400)	//5
	{
		if (vFrom.x < -385)
		{
			m_eZombieSector = SECTOR_4;
		}
		else if (vFrom.x < 790)
		{
			m_eZombieSector = SECTOR_5;
		}
		else m_eZombieSector = SECTOR_8;
	}
	else if (vFrom.z > -950)	//6
	{
		if (vFrom.x < -385)
		{
			m_eZombieSector = SECTOR_4;
		}
		else if (vFrom.x < 500)
		{
			m_eZombieSector = SECTOR_6;
		}
		else m_eZombieSector = SECTOR_8;
	}
	else //7
	{
		if (vFrom.x < -385)
		{
			m_eZombieSector = SECTOR_4;
		}
		else if (vFrom.x < 600)
		{
			m_eZombieSector = SECTOR_7;
		}
		else m_eZombieSector = SECTOR_8;
	}
	/////////////////////////////
	if (vTo.z > 800)	//1
	{
		m_ePlayerSector = SECTOR_1;
	}
	else if (vTo.z > 380)	//2 , 3
	{
		if (vTo.x < -385)
		{
			m_ePlayerSector = SECTOR_4;
		}
		else if (vTo.x < 640)
		{
			m_ePlayerSector = SECTOR_2;
		}
		else if (vTo.x >= 790 && vTo.x < 1550)
		{
			m_ePlayerSector = SECTOR_3;
		}
		else if (vTo.x >= 1550)
		{
			m_ePlayerSector = SECTOR_8;
		}
		else
		{
			m_ePlayerSector = SECTOR_NONE;
		}
	}
	else if (vTo.z > -400)	//5
	{
		if (vTo.x < -385)
		{
			m_ePlayerSector = SECTOR_4;
		}
		else if (vTo.x < 790)
		{
			m_ePlayerSector = SECTOR_5;
		}
		else m_ePlayerSector = SECTOR_8;
	}
	else if (vTo.z > -950)	//6
	{
		if (vTo.x < -385)
		{
			m_ePlayerSector = SECTOR_4;
		}
		else if (vTo.x < 500)
		{
			m_ePlayerSector = SECTOR_6;
		}
		else m_ePlayerSector = SECTOR_8;
	}
	else //7
	{
		if (vTo.x < -385)
		{
			m_ePlayerSector = SECTOR_4;
		}
		else if (vTo.x < 600)
		{
			m_ePlayerSector = SECTOR_7;
		}
		else m_ePlayerSector = SECTOR_8;
	}
	


	return false;
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

	node.vPosition = D3DXVECTOR3(500, -100, -600);	//40
	m_vecNode.push_back(node);
}

float cDijkstra::GetLength(int nFrom, int nTo)
{
	return D3DXVec3Length(&(m_vecNode[nFrom].vPosition - m_vecNode[nTo].vPosition));
}
