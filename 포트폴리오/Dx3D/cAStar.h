#pragma once

class cAstarNode;
class cMinHeap;

class cAStar
{
private:
	std::vector<cAstarNode*>	m_vecNode;
	cMinHeap*					m_pOpenList;

public:
	cAStar();
	~cAStar();

	void Setup();
	void Update(D3DXVECTOR3* pStart, D3DXVECTOR3* pTarget);

private:
	void SetNode();
	void FindPath(D3DXVECTOR3* pStart, D3DXVECTOR3* pTarget);
	cAstarNode* FindStartNode(D3DXVECTOR3* pStart);
	cAstarNode* FindDestNode(D3DXVECTOR3* pTarget);
	float CalcHeuristic(cAstarNode* pNode1, cAstarNode* pNode2);
	void InsertOpenList(cAstarNode* pNode);
	void MoveToCloseList(cAstarNode* pNode);
	void Extend(cAstarNode* pExtNode, cAstarNode* pDestNode);
	cAstarNode* GetAdjNode(cAstarNode* pExtNode, int nDirection);
};

