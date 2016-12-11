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
	std::vector<std::vector<D3DXVECTOR3>>	m_vecObstacleVertex;	//벽 점

	std::vector<ST_NODE>					m_vecNode;
	std::vector<std::vector<ST_NODE>>		m_vecNodeTable;
	std::vector<std::vector<float>>			m_vecEdgeCost;

	//확인용
	LPD3DXMESH								m_pMesh;
	D3DMATERIAL9							m_stMtlNormal;
	D3DMATERIAL9							m_stMtlPicked;

public:
	cDijkstra();
	~cDijkstra();

	void SetObstacleVertex(std::vector<D3DXVECTOR3> obsVertex);	//벽 좌표 가져오기..
	void Setup();	//노드 세팅
	void Render();	//노드 렌더
	void SetEdgeCost(std::vector<OUT std::vector<float>>* vecEdgeCost);
	std::vector<ST_NODE> MakeTable(int nStart);
	void SetNode();
};

