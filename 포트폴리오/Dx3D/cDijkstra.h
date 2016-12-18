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
	std::vector<std::vector<D3DXVECTOR3>>	m_vecObstacleVertex;	//�� ��

	std::vector<ST_NODE>					m_vecNode;
	std::vector<std::vector<float>>			m_vecEdgeCost;
	std::vector<std::vector<ST_NODE>>		m_vecNodeTable;

	SECTOR									m_eFromSector;
	SECTOR									m_eToSector;

	//Ȯ�ο�
	LPD3DXMESH								m_pMesh;
	D3DMATERIAL9							m_stMtlPicked;

public:
	cDijkstra();
	~cDijkstra();

	void Setup();
	void Update(D3DXVECTOR3* vPlayerPos, D3DXVECTOR3* vZombiePos);
	void Render();	//��� ����

	D3DXVECTOR3 GetNodePosition(int nIndex) { return m_vecNode[nIndex].vPosition; }
	bool IsDirect(D3DXVECTOR3* vFrom, D3DXVECTOR3* vTo);
	std::vector<D3DXVECTOR3> GetRoute(D3DXVECTOR3* vFrom, D3DXVECTOR3* vTo);

private:
	void SetNode();	//��� ����
	void SetEdgeCost();	//���� �ڽ�Ʈ ����
	void SetTable();	//ǥ ����
	//��� �� �Ÿ�
	float GetLength(int nFrom, int nTo);
	std::vector<ST_NODE> MakeTable(int nStart);
	//��� �������� ����..'��`
	SECTOR SetSector(D3DXVECTOR3* vPos);
	//�� ��ǥ ����
	void SetObstacleVertex(OUT std::vector< std::vector<D3DXVECTOR3>>& obsVertex);
	//��� ���̺�
	std::vector<int> GetNodeTable(int nStart, int nDest);
	bool Intersect(std::vector<D3DXVECTOR3>* vecObs, D3DXVECTOR3* vFrom, D3DXVECTOR3* vTo);
	int GetFirstNode(D3DXVECTOR3* vPos);
	//�� ���� ����
	void GetSectorNode(IN SECTOR eSector, OUT std::vector<int>& vecNode);
	int GetNearestNodeIndex(std::vector<int>* vecIndex, D3DXVECTOR3* vPos);
};

