#include "stdafx.h"
#include "cDijkstra.h"

#define RADIUS 30.0f

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
	//m_vecObstacleVertex.push_back(obsVertex);
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
	SetEdgeCost(&m_vecEdgeCost);
	for (int i = 0; i < m_vecNode.size(); ++i)
	{
		std::vector<ST_NODE> vN = MakeTable(i);
		m_vecNodeTable.push_back(vN);
	}
}

void cDijkstra::Render()
{
	for each(auto p in m_vecNode)
	{
		D3DXMATRIXA16 matT;
		D3DXMatrixTranslation(&matT, p.s.vCenter.x, p.s.vCenter.y, p.s.vCenter.z);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matT);
		g_pD3DDevice->SetTexture(0, NULL);

		g_pD3DDevice->SetMaterial(&m_stMtlPicked);

		m_pMesh->DrawSubset(0);
	}
}

void cDijkstra::SetEdgeCost(OUT std::vector<std::vector<float>>* vecEdgeCost)
{
	std::vector<float> vecRow;
	//아 몇번노드랑 연결되었는지 알아야하네 ㅅㅂ
}

std::vector<ST_NODE> cDijkstra::MakeTable(int nStart)
{

	return std::vector<ST_NODE>();
}

void cDijkstra::SetNode()
{
	ST_NODE node;
	node.s = ST_SPHERE(D3DXVECTOR3(-500, -60, 2200), RADIUS, false, NULL);	//0
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(-250, -60, 1200), RADIUS, false, NULL);	//1
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(1400, -60, 2200), RADIUS, false, NULL);	//2
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(900, -60, 1200), RADIUS, false, NULL);	//3
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(-250, -60, 400), RADIUS, false, NULL);	//4
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(-850, -60, -50), RADIUS, false, NULL);	//5
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(-950, -60, 450), RADIUS, false, NULL);	//6
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(-1300, -60, 400), RADIUS, false, NULL);	//7
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(-1250, -60, -400), RADIUS, false, NULL);	//8
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(-1300, -60, -900), RADIUS, false, NULL);	//9
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(100, -60, 670), RADIUS, false, NULL);	//10
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(350, -60, 670), RADIUS, false, NULL);	//11
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(630, -60, 300), RADIUS, false, NULL);	//12
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(300, -60, 300), RADIUS, false, NULL);	//13
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(250, -60, 150), RADIUS, false, NULL);	//14
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(0, -60, -50), RADIUS, false, NULL);		//15
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(-400, -60, -300), RADIUS, false, NULL);	//16
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(-850, -60, -350), RADIUS, false, NULL);	//17
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(300, -60, -200), RADIUS, false, NULL);	//18
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(50, -60, -330), RADIUS, false, NULL);	//19
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(-280, -60, -600), RADIUS, false, NULL);	//20
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(-280, -60, -870), RADIUS, false, NULL);	//21
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(90, -60, -870), RADIUS, false, NULL);	//22
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(-150, -60, -1350), RADIUS, false, NULL);	//23
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(280, -60, -1350), RADIUS, false, NULL);	//24
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(90, -60, -1600), RADIUS, false, NULL);	//25
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(-550, -60, -1300), RADIUS, false, NULL);	//26
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(-450, -60, -1100), RADIUS, false, NULL);	//27
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(-600, -60, -700), RADIUS, false, NULL);	//28
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(250, -60, -600), RADIUS, false, NULL);	//29
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(490, -60, -1150), RADIUS, false, NULL);	//30
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(700, -60, -830), RADIUS, false, NULL);	//31
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(920, -60, 730), RADIUS, false, NULL);	//32
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(950, -60, 450), RADIUS, false, NULL);	//33
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(1300, -60, 730), RADIUS, false, NULL);	//34
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(1420, -60, 470), RADIUS, false, NULL);	//35
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(1500, -60, 100), RADIUS, false, NULL);	//36
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(1200, -60, -830), RADIUS, false, NULL);	//37 
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(1200, -60, -1200), RADIUS, false, NULL);	//38
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(2500, -60, 100), RADIUS, false, NULL);	//39
	m_vecNode.push_back(node);
	node.s = ST_SPHERE(D3DXVECTOR3(-250, -60, -80), RADIUS, false, NULL);	//40
	m_vecNode.push_back(node);
}
