#pragma once

class cSkinnedMesh;

struct ST_NODE
{
	D3DXVECTOR3	vPosition;
	bool		isClosed;
	int			nViaNode;
	float		fTotalCost;

	ST_NODE() : vPosition(D3DXVECTOR3(0, 0, 0)), isClosed(false), nViaNode(-1), fTotalCost(10000.0f) {}
};

class cDijkstra
{
private:
	std::vector<std::vector<D3DXVECTOR3>>	m_vecObstacleVertex;	//�� ��

	std::vector<ST_NODE>					m_vecNode;
	std::vector<std::vector<float>>			m_vecEdgeCost;
	std::vector<std::vector<ST_NODE>>		m_vecNodeTable;

	//Ȯ�ο�
	LPD3DXMESH								m_pMesh;
	D3DMATERIAL9							m_stMtlNormal;
	D3DMATERIAL9							m_stMtlPicked;

public:
	cDijkstra();
	~cDijkstra();

	void SetObstacleVertex(std::vector<D3DXVECTOR3> obsVertex);	//�� ��ǥ �����ϱ�..
	void Setup();
	void Render();	//��� ����

private:
	void SetNode();	//��� ����
	void SetEdgeCost();	//���� �ڽ�Ʈ ����
	void SetTable();	//ǥ ����
	float GetLength(int nFrom, int nTo);
	std::vector<ST_NODE> MakeTable(int nStart);
	
//	static 
};

