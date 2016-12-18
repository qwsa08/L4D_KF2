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

enum SECTOR
{
	SECTOR_1,
	SECTOR_2,
	SECTOR_3,
	SECTOR_4,
	SECTOR_5,
	SECTOR_6,
	SECTOR_7,
	SECTOR_8,
	SECTOR_NONE
};

class cDijkstra
{
private:
	std::vector<std::vector<D3DXVECTOR3>>	m_vecObstacleVertex;	//벽 점

	std::vector<ST_NODE>					m_vecNode;
	std::vector<std::vector<float>>			m_vecEdgeCost;
	std::vector<std::vector<ST_NODE>>		m_vecNodeTable;

	SECTOR									m_eFromSector;
	SECTOR									m_eToSector;

	//확인용
	LPD3DXMESH								m_pMesh;
	D3DMATERIAL9							m_stMtlPicked;

public:
	cDijkstra();
	~cDijkstra();

	void Setup();
	void Update(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vZombiePos);
	void Render();	//노드 렌더

	D3DXVECTOR3 GetNodePosition(int nIndex) { return m_vecNode[nIndex].vPosition; }
	bool IsDirect(D3DXVECTOR3* vFrom, D3DXVECTOR3* vTo);
	std::vector<D3DXVECTOR3> GetRoute(D3DXVECTOR3* vFrom, D3DXVECTOR3* vTo);

private:
	void SetNode();	//노드 세팅
	void SetEdgeCost();	//엣지 코스트 세팅
	void SetTable();	//표 세팅
	//노드 간 거리
	float GetLength(int nFrom, int nTo);
	std::vector<ST_NODE> MakeTable(int nStart);
	//어느 구역인지 결정..'ㅅ`
	SECTOR SetSector(D3DXVECTOR3* vPos);
	//벽 좌표 세팅
	void SetObstacleVertex(OUT std::vector< std::vector<D3DXVECTOR3>>& obsVertex);
	//노드 테이블
	std::vector<int> GetNodeTable(int nStart, int nDest);
	bool Intersect(std::vector<D3DXVECTOR3>* vecObs, D3DXVECTOR3* vFrom, D3DXVECTOR3* vTo);
	int GetFirstNode(D3DXVECTOR3* vPos);
	//음 구역 노드들
	void GetSectorNode(IN SECTOR eSector, OUT std::vector<int>& vecNode);
	int GetNearestNodeIndex(std::vector<int>* vecIndex, D3DXVECTOR3* vPos);
};

