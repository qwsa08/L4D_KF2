#pragma once

class cAstarNode;

class cMinHeap
{
private:
	std::vector<cAstarNode*>	m_vecHeap;

public:
	cMinHeap();
	~cMinHeap();

	void	Insert(cAstarNode* pNode);
	cAstarNode*	GetMinFNode();
	void	UpdateUpper(int nIndex);
	void	UpdateLower(int nIndex);
	void	Swap(int nIndex1, int nIndex2);
};

