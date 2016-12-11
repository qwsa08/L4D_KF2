#pragma once

class cSkinnedMesh;

struct ST_NODE
{
	ST_SPHERE	s;
	bool		isClosed;
	int			nViaNode;
	float		fTotalCost;

	ST_NODE() : s(ST_SPHERE(D3DXVECTOR3(0, 0, 0), 0.0f, false, NULL)), isClosed(false), nViaNode(-1), fTotalCost(10000.0f) {}
};

class cDijkstra
{
private:
	std::vector<std::vector<D3DXVECTOR3>>	m_vecObstacleVertex;	//�� ��

	std::vector<ST_NODE>					m_vecNode;
	std::vector<std::vector<ST_NODE>>		m_vecNodeTable;
	std::vector<std::vector<float>>			m_vecEdgeCost;

	//Ȯ�ο�
	LPD3DXMESH								m_pMesh;
	D3DMATERIAL9							m_stMtlNormal;
	D3DMATERIAL9							m_stMtlPicked;

public:
	cDijkstra();
	~cDijkstra();

	void SetObstacleVertex(std::vector<D3DXVECTOR3> obsVertex);	//�� ��ǥ ��������..
	void Setup();	//��� ����
	void Render();	//��� ����
	void SetEdgeCost(std::vector<OUT std::vector<float>>* vecEdgeCost);
	std::vector<ST_NODE> MakeTable(int nStart);
	void SetNode();
};

