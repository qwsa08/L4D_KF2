#include "stdafx.h"
#include "cAStar.h"
#include "cAstarNode.h"
#include "cMinHeap.h"


cAStar::cAStar()
	: m_pOpenList(new cMinHeap)
{
}


cAStar::~cAStar()
{
	for each(auto p in m_vecNode)
	{
		SAFE_DELETE(p);
	}
	m_vecNode.clear();

	SAFE_DELETE(m_pOpenList);	
}

void cAStar::Setup()
{
	//노드 잡자
	SetNode();
}

void cAStar::Update(D3DXVECTOR3* pStart, D3DXVECTOR3* pTarget)
{
	FindPath(pStart, pTarget);
}

void cAStar::SetNode()
{
	cAstarNode* pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(-500, -60, 2200);	//0
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(-250, -60, 1200);	//1
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(1400, -60, 2200);	//2
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(900, -60, 1200);	//3
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(-250, -60, 400);	//4
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(-850, -60, -50);	//5
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(-950, -60, 450);	//6
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(-1300, -60, 400);	//7
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(-1250, -60, -400);	//8
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(-1300, -60, -900);	//9
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(100, -60, 670);	//10
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(350, -60, 670);	//11
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(630, -60, 300);	//12
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(300, -60, 300);	//13
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(250, -60, 150);	//14
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(0, -60, -50);		//15
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(-400, -60, -300);	//16
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(-850, -60, -350);	//17
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(300, -60, -200);	//18
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(50, -60, -330);	//19
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(-280, -60, -600);	//20
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(-280, -60, -870);	//21
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(90, -60, -870);	//22
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(-150, -60, -1350);	//23
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(280, -60, -1350);	//24
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(90, -60, -1600);	//25
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(-550, -60, -1300);	//26
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(-450, -60, -1100);	//27
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(-600, -60, -700);	//28
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(250, -60, -600);	//29
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(490, -60, -1150);	//30
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(700, -60, -830);	//31
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(920, -60, 730);	//32
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(950, -60, 450);	//33
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(1300, -60, 730);	//34
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(1420, -60, 470);	//35
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(1500, -60, 100);	//36
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(1200, -60, -830);	//37 
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(1200, -60, -1200);	//38
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(2500, -60, 100);	//39
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
	pNode->m_vPosition = D3DXVECTOR3(-250, -60, -80);	//40
	m_vecNode.push_back(pNode);
	pNode = new cAstarNode;
}

void cAStar::FindPath(D3DXVECTOR3* pStart, D3DXVECTOR3* pTarget)
{
	//시작노드 끝노드 잡아야!!
	cAstarNode* pStartNode = FindStartNode(pStart);
	cAstarNode* pDestNode = FindDestNode(pTarget);

	pStartNode->G = 0.0f;
	pStartNode->H = CalcHeuristic(pStartNode, pDestNode);
	pStartNode->F = pStartNode->G + pStartNode->H;

	InsertOpenList(pStartNode);

	while (true)
	{
		cAstarNode* pMinFNode = m_pOpenList->GetMinFNode();

		if (pMinFNode == NULL)
		{
			// 길이 없음..
//			MarkNodeType(pDestNode);
			break;
		}

		MoveToCloseList(pMinFNode);

		Extend(pMinFNode, pDestNode);

		if (pMinFNode == pDestNode)
		{
			// 경로 찾음
//			MarkNodeType(pDestNode);
			break;
		}
	}
}

cAstarNode * cAStar::FindStartNode(D3DXVECTOR3 * pStart)
{
	//일단 거리로..
	int n = 0;
	for (int i = 0; i < m_vecNode.size(); ++i)
	{
		if (D3DXVec3Length(&(m_vecNode[n]->m_vPosition - *pStart)) > D3DXVec3Length(&(m_vecNode[i]->m_vPosition - *pStart)))
		{
			n = i;
		}
	}
	return m_vecNode[n];
}

cAstarNode * cAStar::FindDestNode(D3DXVECTOR3 * pTarget)
{
	int n = 0;
	for (int i = 0; i < m_vecNode.size(); ++i)
	{
		if (D3DXVec3Length(&(m_vecNode[n]->m_vPosition - *pTarget)) > D3DXVec3Length(&(m_vecNode[i]->m_vPosition - *pTarget)))
		{
			n = i;
		}
	}
	return m_vecNode[n];
}

float cAStar::CalcHeuristic(cAstarNode * pNode1, cAstarNode * pNode2)
{
	return D3DXVec3Length(&(pNode1->m_vPosition - pNode2->m_vPosition));
}

void cAStar::InsertOpenList(cAstarNode * pNode)
{
	pNode->m_isOpen = true;
	m_pOpenList->Insert(pNode);
}

void cAStar::MoveToCloseList(cAstarNode * pNode)
{
	pNode->m_isOpen = false;
	pNode->m_isClose = true;
}

void cAStar::Extend(cAstarNode * pExtNode, cAstarNode * pDestNode)
{
}

cAstarNode * cAStar::GetAdjNode(cAstarNode * pExtNode, int nDirection)
{
	return nullptr;
}
