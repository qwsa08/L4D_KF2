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
	std::vector<std::vector<D3DXVECTOR3>>	m_vecObstacleVertex;	//벽 점

	std::vector<ST_NODE>					m_vecNode;
	std::vector<std::vector<float>>			m_vecEdgeCost;
	std::vector<std::vector<ST_NODE>>		m_vecNodeTable;

	//확인용
	LPD3DXMESH								m_pMesh;
	D3DMATERIAL9							m_stMtlNormal;
	D3DMATERIAL9							m_stMtlPicked;

public:
	cDijkstra();
	~cDijkstra();

	void SetObstacleVertex(std::vector<D3DXVECTOR3> obsVertex);	//벽 좌표 세팅하기..
	void Setup();
	void Render();	//노드 렌더

private:
	void SetNode();	//노드 세팅
	void SetEdgeCost();	//엣지 코스트 세팅
	void SetTable();	//표 세팅
	float GetLength(int nFrom, int nTo);
	std::vector<ST_NODE> MakeTable(int nStart);
	
//	static 
};

