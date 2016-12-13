#include "stdafx.h"
#include "cMinHeap.h"
#include "cAstarNode.h"


cMinHeap::cMinHeap()
{
}


cMinHeap::~cMinHeap()
{
}

void cMinHeap::Insert(cAstarNode * pNode)
{
	pNode->m_nHeapIndex = m_vecHeap.size();
	m_vecHeap.push_back(pNode);
	UpdateUpper(m_vecHeap.size() - 1);
}

cAstarNode * cMinHeap::GetMinFNode()
{
	if (m_vecHeap.empty()) return NULL;

	cAstarNode* pMinFNode = m_vecHeap[0];
	m_vecHeap[0] = m_vecHeap.back();
	m_vecHeap[0]->m_nHeapIndex = 0;
	m_vecHeap.pop_back();
	if (m_vecHeap.empty())
		return pMinFNode;
	UpdateLower(0);
	return pMinFNode;
}

void cMinHeap::UpdateUpper(int nIndex)
{
	if (nIndex == 0) return;

	int nParent = (nIndex - 1) / 2;
	if (m_vecHeap[nIndex]->F < m_vecHeap[nParent]->F)
	{
		Swap(nIndex, nParent);
		UpdateUpper(nParent);
	}
}

void cMinHeap::UpdateLower(int nIndex)
{
	int nLChild = nIndex * 2 + 1;
	if (nLChild >= m_vecHeap.size())
		return;
	int nMinChild = nLChild;
	int nRChild = nIndex * 2 + 2;
	if (nRChild < m_vecHeap.size() &&
		m_vecHeap[nRChild]->F < m_vecHeap[nMinChild]->F)
	{
		nMinChild = nRChild;
	}
	if (m_vecHeap[nMinChild]->F < m_vecHeap[nIndex]->F)
	{
		Swap(nIndex, nMinChild);
		UpdateLower(nMinChild);
	}
}

void cMinHeap::Swap(int nIndex1, int nIndex2)
{
	cAstarNode* pTemp = m_vecHeap[nIndex1];
	m_vecHeap[nIndex1] = m_vecHeap[nIndex2];
	m_vecHeap[nIndex2] = pTemp;

	int nTemp = m_vecHeap[nIndex1]->m_nHeapIndex;
	m_vecHeap[nIndex1]->m_nHeapIndex = m_vecHeap[nIndex2]->m_nHeapIndex;
	m_vecHeap[nIndex2]->m_nHeapIndex = nTemp;
}
