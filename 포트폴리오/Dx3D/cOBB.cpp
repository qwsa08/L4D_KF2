#include "StdAfx.h"
#include "cOBB.h"
#include "cSkinnedMesh.h"
#include "cCrtController.h"

cOBB::cOBB(void)
{
}


cOBB::~cOBB(void)
{
}

void cOBB::SetupOBJ(D3DXVECTOR3 _min, D3DXVECTOR3 _max, OUT ST_OBB &box, D3DXMATRIXA16* _World)
{
	D3DXVECTOR3 vMin = _min;
	D3DXVECTOR3 vMax = _max;
	m_vOrgCenterPos = (vMin + vMax) / 2.f;
	m_vCenterPos = (vMin + vMax) / 2.f;
	
	m_vOrgAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOrgAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOrgAxisDir[2] = D3DXVECTOR3(0, 0, 1);

	m_fAxisLen[0] = fabs(vMax.x - vMin.x);
	m_fAxisLen[1] = fabs(vMax.y - vMin.y);
	m_fAxisLen[2] = fabs(vMax.z - vMin.z);

	m_fAxisHalfLen[0] = m_fAxisLen[0] / 2.0f;
	m_fAxisHalfLen[1] = m_fAxisLen[1] / 2.0f;
	m_fAxisHalfLen[2] = m_fAxisLen[2] / 2.0f;

	D3DXMatrixIdentity(&m_matWorldTM);
	box.m_vOrgCenterPos = (vMin + vMax) / 2.f;
	box.vCenter = (vMin + vMax) / 2.f;

	box.vAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	box.vAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	box.vAxisDir[2] = D3DXVECTOR3(0, 0, 1);

	box.fAxisLen[0] = fabs(vMax.x - vMin.x);
	box.fAxisLen[1] = fabs(vMax.y - vMin.y);
	box.fAxisLen[2] = fabs(vMax.z - vMin.z);

	box.fAxisHalfLen[0] = box.fAxisLen[0] / 2.f;
	box.fAxisHalfLen[1] = box.fAxisLen[1] / 2.f;
	box.fAxisHalfLen[2] = box.fAxisLen[2] / 2.f;

	if (_World)
	{
		m_matWorldTM = *_World;
		for (int i = 0; i < 3; ++i)
		{
			D3DXVec3TransformNormal(
				&box.vAxisDir[i],
				&m_vOrgAxisDir[i],
				&m_matWorldTM);
		}

		D3DXVec3TransformCoord(
			&box.vCenter,
			&m_vOrgCenterPos,
			&m_matWorldTM);
	}
	
}
void cOBB::Setup(D3DXVECTOR3 _min, D3DXVECTOR3 _max, OUT ST_OBB &box)
{
	D3DXVECTOR3 vMin = _min;
	D3DXVECTOR3 vMax = _max;
	m_vOrgCenterPos = (vMin + vMax) / 2.f;
	m_vCenterPos = (vMin + vMax) / 2.f;

	m_vOrgAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOrgAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOrgAxisDir[2] = D3DXVECTOR3(0, 0, 1);

	box.vCenter = (vMin + vMax) / 2.f;

	box.vAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	box.vAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	box.vAxisDir[2] = D3DXVECTOR3(0, 0, 1);

	box.fAxisLen[0] = fabs(vMax.x - vMin.x);
	box.fAxisLen[1] = fabs(vMax.y - vMin.y);
	box.fAxisLen[2] = fabs(vMax.z - vMin.z);

	box.fAxisHalfLen[0] = box.fAxisLen[0] / 2.f;
	box.fAxisHalfLen[1] = box.fAxisLen[1] / 2.f;
	box.fAxisHalfLen[2] = box.fAxisLen[2] / 2.f;

}

void cOBB::Update(D3DXMATRIXA16* pmatWorld, ST_OBB &box)
{
	if(pmatWorld)
		m_matWorldTM = *pmatWorld;
	
	for (int i = 0; i < 3; ++i)
	{
		D3DXVec3TransformNormal(
			&box.vAxisDir[i],
			&m_vOrgAxisDir[i],
			&m_matWorldTM);
	}

	D3DXVec3TransformCoord(
		&box.vCenter,
		&m_vOrgCenterPos,
		&m_matWorldTM);
}
bool cOBB::GetFaceBoxIntersect(ST_OBB* pOBB1, cCrtController* Controller, D3DXMATRIXA16* _World)
{
	
	std::vector<D3DXVECTOR3> vecVertex;
	vecVertex.reserve(8);

	D3DXVECTOR3 vec;
	
	vec = D3DXVECTOR3(
		pOBB1->m_vOrgCenterPos.x - pOBB1->fAxisLen[0] / 2.0f,
		pOBB1->m_vOrgCenterPos.y - pOBB1->fAxisLen[1] / 2.0f,
		pOBB1->m_vOrgCenterPos.z - pOBB1->fAxisLen[2] / 2.0f);
	vecVertex.push_back(vec);

	vec = D3DXVECTOR3(
		pOBB1->m_vOrgCenterPos.x - pOBB1->fAxisLen[0] / 2.0f,
		pOBB1->m_vOrgCenterPos.y + pOBB1->fAxisLen[1] / 2.0f,
		pOBB1->m_vOrgCenterPos.z - pOBB1->fAxisLen[2] / 2.0f);
	vecVertex.push_back(vec);

	vec = D3DXVECTOR3(
		pOBB1->m_vOrgCenterPos.x + pOBB1->fAxisLen[0] / 2.0f,
		pOBB1->m_vOrgCenterPos.y + pOBB1->fAxisLen[1] / 2.0f,
		pOBB1->m_vOrgCenterPos.z - pOBB1->fAxisLen[2] / 2.0f);
	vecVertex.push_back(vec);

	vec = D3DXVECTOR3(
		pOBB1->m_vOrgCenterPos.x + pOBB1->fAxisLen[0] / 2.0f,
		pOBB1->m_vOrgCenterPos.y - pOBB1->fAxisLen[1] / 2.0f,
		pOBB1->m_vOrgCenterPos.z - pOBB1->fAxisLen[2] / 2.0f);
	vecVertex.push_back(vec);

	vec = D3DXVECTOR3(
		pOBB1->m_vOrgCenterPos.x - pOBB1->fAxisLen[0] / 2.0f,
		pOBB1->m_vOrgCenterPos.y - pOBB1->fAxisLen[1] / 2.0f,
		pOBB1->m_vOrgCenterPos.z + pOBB1->fAxisLen[2] / 2.0f);
	vecVertex.push_back(vec);

	vec = D3DXVECTOR3(
		pOBB1->m_vOrgCenterPos.x - pOBB1->fAxisLen[0] / 2.0f,
		pOBB1->m_vOrgCenterPos.y + pOBB1->fAxisLen[1] / 2.0f,
		pOBB1->m_vOrgCenterPos.z + pOBB1->fAxisLen[2] / 2.0f);
	vecVertex.push_back(vec);

	vec = D3DXVECTOR3(
		pOBB1->m_vOrgCenterPos.x + pOBB1->fAxisLen[0] / 2.0f,
		pOBB1->m_vOrgCenterPos.y + pOBB1->fAxisLen[1] / 2.0f,
		pOBB1->m_vOrgCenterPos.z + pOBB1->fAxisLen[2] / 2.0f);
	vecVertex.push_back(vec);

	vec = D3DXVECTOR3(
		pOBB1->m_vOrgCenterPos.x + pOBB1->fAxisLen[0] / 2.0f,
		pOBB1->m_vOrgCenterPos.y - pOBB1->fAxisLen[1] / 2.0f,
		pOBB1->m_vOrgCenterPos.z + pOBB1->fAxisLen[2] / 2.0f);
	vecVertex.push_back(vec);

	for (int i = 0; i < vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(
			&vecVertex[i],
			&vecVertex[i],
			_World);
	}

	//���� =========================
	std::vector<D3DXVECTOR3> temp ;
	temp.push_back(vecVertex[0]); temp.push_back(vecVertex[1]); temp.push_back(vecVertex[2]);
	temp.push_back(vecVertex[0]); temp.push_back(vecVertex[2]); temp.push_back(vecVertex[3]);
	//�ĸ� ===========================
	temp.push_back(vecVertex[7]); temp.push_back(vecVertex[6]); temp.push_back(vecVertex[5]);
	temp.push_back(vecVertex[7]); temp.push_back(vecVertex[5]); temp.push_back(vecVertex[4]);
	//���� ===========================
	temp.push_back(vecVertex[4]); temp.push_back(vecVertex[5]); temp.push_back(vecVertex[1]);
	temp.push_back(vecVertex[4]); temp.push_back(vecVertex[1]); temp.push_back(vecVertex[0]);
	//���� ===========================
	temp.push_back(vecVertex[3]); temp.push_back(vecVertex[2]); temp.push_back(vecVertex[6]);
	temp.push_back(vecVertex[3]); temp.push_back(vecVertex[6]); temp.push_back(vecVertex[7]);
	//��� ==========================
	temp.push_back(vecVertex[1]); temp.push_back(vecVertex[5]); temp.push_back(vecVertex[6]);
	temp.push_back(vecVertex[1]); temp.push_back(vecVertex[6]); temp.push_back(vecVertex[2]);
	//�ϴ� ==========================
	temp.push_back(vecVertex[3]); temp.push_back(vecVertex[7]); temp.push_back(vecVertex[4]);
	temp.push_back(vecVertex[3]); temp.push_back(vecVertex[4]); temp.push_back(vecVertex[0]);


	D3DXVECTOR3 Position = *(Controller->GetPosition());
	D3DXVECTOR3 vRayPos(Position.x, Position.y, Position.z);
	D3DXVECTOR3 vRayDir = Controller->GetDirection();
	float u, v, d;

	for (int i = 0; i < temp.size(); i += 3)
	{
		D3DXVECTOR3 v0 = temp[i];
		D3DXVECTOR3 v1 = temp[i + 1];
		D3DXVECTOR3 v2 = temp[i + 2];

		if (D3DXIntersectTri(&v0, &v1, &v2, &vRayPos, &vRayDir, &u, &v, &d))
		{
			return true;
		}
	}
	return false;
}
void cOBB::DebugRender(ST_OBB* pOBB1,D3DCOLOR c)
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	
	std::vector<ST_PC_VERTEX> vecVertex;
	vecVertex.reserve(8);

	ST_PC_VERTEX v;
	v.c = c;
	v.p = D3DXVECTOR3(
		pOBB1->m_vOrgCenterPos.x - pOBB1->fAxisLen[0] / 2.0f,
		pOBB1->m_vOrgCenterPos.y - pOBB1->fAxisLen[1] / 2.0f,
		pOBB1->m_vOrgCenterPos.z - pOBB1->fAxisLen[2] / 2.0f);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3(
		pOBB1->m_vOrgCenterPos.x - pOBB1->fAxisLen[0] / 2.0f,
		pOBB1->m_vOrgCenterPos.y + pOBB1->fAxisLen[1] / 2.0f,
		pOBB1->m_vOrgCenterPos.z - pOBB1->fAxisLen[2] / 2.0f);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3(
		pOBB1->m_vOrgCenterPos.x + pOBB1->fAxisLen[0] / 2.0f,
		pOBB1->m_vOrgCenterPos.y + pOBB1->fAxisLen[1] / 2.0f,
		pOBB1->m_vOrgCenterPos.z - pOBB1->fAxisLen[2] / 2.0f);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3(
		pOBB1->m_vOrgCenterPos.x + pOBB1->fAxisLen[0] / 2.0f,
		pOBB1->m_vOrgCenterPos.y - pOBB1->fAxisLen[1] / 2.0f,
		pOBB1->m_vOrgCenterPos.z - pOBB1->fAxisLen[2] / 2.0f);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3(
		pOBB1->m_vOrgCenterPos.x - pOBB1->fAxisLen[0] / 2.0f,
		pOBB1->m_vOrgCenterPos.y - pOBB1->fAxisLen[1] / 2.0f,
		pOBB1->m_vOrgCenterPos.z + pOBB1->fAxisLen[2] / 2.0f);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3(
		pOBB1->m_vOrgCenterPos.x - pOBB1->fAxisLen[0] / 2.0f,
		pOBB1->m_vOrgCenterPos.y + pOBB1->fAxisLen[1] / 2.0f,
		pOBB1->m_vOrgCenterPos.z + pOBB1->fAxisLen[2] / 2.0f);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3(
		pOBB1->m_vOrgCenterPos.x + pOBB1->fAxisLen[0] / 2.0f,
		pOBB1->m_vOrgCenterPos.y + pOBB1->fAxisLen[1] / 2.0f,
		pOBB1->m_vOrgCenterPos.z + pOBB1->fAxisLen[2] / 2.0f);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3(
		pOBB1->m_vOrgCenterPos.x + pOBB1->fAxisLen[0] / 2.0f,
		pOBB1->m_vOrgCenterPos.y - pOBB1->fAxisLen[1] / 2.0f,
		pOBB1->m_vOrgCenterPos.z + pOBB1->fAxisLen[2] / 2.0f);
	vecVertex.push_back(v);


	std::vector<WORD> vecIndex;
	vecIndex.reserve(24);

	vecIndex.push_back(0); vecIndex.push_back(1);
	vecIndex.push_back(1); vecIndex.push_back(2);
	vecIndex.push_back(2); vecIndex.push_back(3);
	vecIndex.push_back(3); vecIndex.push_back(0);
	vecIndex.push_back(4); vecIndex.push_back(5);
	vecIndex.push_back(5); vecIndex.push_back(6);
	vecIndex.push_back(6); vecIndex.push_back(7);
	vecIndex.push_back(7); vecIndex.push_back(4);
	vecIndex.push_back(0); vecIndex.push_back(4);
	vecIndex.push_back(1); vecIndex.push_back(5);
	vecIndex.push_back(2); vecIndex.push_back(6);
	vecIndex.push_back(3); vecIndex.push_back(7);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawIndexedPrimitiveUP(D3DPT_LINELIST,
		0,
		8,
		12,
		&vecIndex[0],
		D3DFMT_INDEX16,
		&vecVertex[0],
		sizeof(ST_PC_VERTEX));
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}

bool cOBB::IsCollision(ST_OBB* pOBB1, ST_OBB* pOBB2)
{
	float cos[3][3];		
	float absCos[3][3];
	float dist[3];
	float r0, r1, r;

	const float cutOff = 0.999999f;
	bool existsParallelPair = false;

	D3DXVECTOR3 D = pOBB2->vCenter - pOBB1->vCenter;

	// OBB_A �� 3 ���� �������� OBB_B �� 3���� �˻�
	for( int a = 0 ; a < 3 ; a++ )
	{
		for( int b = 0 ; b < 3 ; b++ )
		{
			//OBB_A a ��� OBB_B b ���� cos ��
			cos[a][b] = D3DXVec3Dot( &pOBB1->vAxisDir[a], &pOBB2->vAxisDir[b] );
			
			//������ ���� cos ���� ���밪
			absCos[a][b] = abs( cos[a][b] );


			//������ �����̴� 
			//�̷��Ѱ�� AABB ���°� �ȴ�.
			if( absCos[a][b] > cutOff )
				existsParallelPair = true;
		}


		//�簢�� ������ �߽� �Ÿ� ���͸� OBB_A �� a ������ ������ �Ÿ�
		dist[a] = D3DXVec3Dot( &pOBB1->vAxisDir[a], &D );
		r = abs( dist[a] );

		//OBB_A �� a ���� ����
		r0 = pOBB1->fAxisHalfLen[a];

		//OBB_B �� �������� OBB_A ��a ������ ������ ����
		r1 = pOBB2->fAxisHalfLen[0] * absCos[a][0] + 
			pOBB2->fAxisHalfLen[1] * absCos[a][1] +
			pOBB2->fAxisHalfLen[2] * absCos[a][2];

		if( r > r0 + r1 )
			return false;
	}



	// OBB_B �� 3���� �������� OBB_A �� 3���� �˻�
	for( int b = 0 ; b < 3 ; b++ )
	{
		r = abs( D3DXVec3Dot( &pOBB2->vAxisDir[b], &D ) );
		r0 = pOBB1->fAxisHalfLen[0] * absCos[0][b] + 
			pOBB1->fAxisHalfLen[1] * absCos[1][b] +
			pOBB1->fAxisHalfLen[2] * absCos[2][b];

		r1 = pOBB2->fAxisHalfLen[b];

		if( r > r0 + r1 )
			return false;
	}


	if( existsParallelPair ) return true;




	/////////////////////////////////////////////////////////////////

	r = abs( dist[0] * cos[2][0] - dist[2] * cos[0][0] );
	r0 = pOBB1->fAxisHalfLen[0] * absCos[2][0] + pOBB1->fAxisHalfLen[2] * absCos[0][0];
	r1 = pOBB2->fAxisHalfLen[1] * absCos[1][2] + pOBB2->fAxisHalfLen[2] * absCos[1][1];
	if( r > r0 + r1 )
		return false;

	r = abs( dist[0] * cos[2][1] - dist[2] * cos[0][1] );
	r0 = pOBB1->fAxisHalfLen[0] * absCos[2][1] + pOBB1->fAxisHalfLen[2] * absCos[0][1];
	r1 = pOBB2->fAxisHalfLen[0] * absCos[1][2] + pOBB2->fAxisHalfLen[2] * absCos[1][0];
	if( r > r0 + r1 )
		return false;

	r = abs( dist[0] * cos[2][2] - dist[2] * cos[0][2] );
	r0 = pOBB1->fAxisHalfLen[0] * absCos[2][2] + pOBB1->fAxisHalfLen[2] * absCos[0][2];
	r1 = pOBB2->fAxisHalfLen[0] * absCos[1][1] + pOBB2->fAxisHalfLen[1] * absCos[1][0];
	if( r > r0 + r1 )
		return false;


	/////////////////////////////////////////////////////////////////	 


	r = abs( dist[1] * cos[0][0] - dist[0] * cos[1][0] );
	r0 = pOBB1->fAxisHalfLen[0] * absCos[1][0] + pOBB1->fAxisHalfLen[1] * absCos[0][0];
	r1 = pOBB2->fAxisHalfLen[1] * absCos[2][2] + pOBB2->fAxisHalfLen[2] * absCos[2][1];
	if( r > r0 + r1 )
		return false;

	r = abs( dist[1] * cos[0][1] - dist[0] * cos[1][1] );
	r0 = pOBB1->fAxisHalfLen[0] * absCos[1][1] + pOBB1->fAxisHalfLen[1] * absCos[0][1];
	r1 = pOBB2->fAxisHalfLen[0] * absCos[2][2] + pOBB2->fAxisHalfLen[2] * absCos[2][0];
	if( r > r0 + r1 )
		return false;


	r = abs( dist[1] * cos[0][2] - dist[0] * cos[1][2] );
	r0 = pOBB1->fAxisHalfLen[0] * absCos[1][2] + pOBB1->fAxisHalfLen[1] * absCos[0][2];
	r1 = pOBB2->fAxisHalfLen[0] * absCos[2][1] + pOBB2->fAxisHalfLen[1] * absCos[2][0];
	if( r > r0 + r1 )
		return false;


	/////////////////////////////////////////////////////////////////

	r = abs( dist[2] * cos[1][0] - dist[1] * cos[2][0] );
	r0 = pOBB1->fAxisHalfLen[1] * absCos[2][0] + pOBB1->fAxisHalfLen[2] * absCos[1][0];
	r1 = pOBB2->fAxisHalfLen[1] * absCos[0][2] + pOBB2->fAxisHalfLen[2] * absCos[0][1];
	if( r > r0 + r1 )
		return false;



	r = abs( dist[2] * cos[1][1] - dist[1] * cos[2][1] );
	r0 = pOBB1->fAxisHalfLen[1] * absCos[2][1] + pOBB1->fAxisHalfLen[2] * absCos[1][1];
	r1 = pOBB2->fAxisHalfLen[0] * absCos[0][2] + pOBB2->fAxisHalfLen[2] * absCos[0][0];
	if( r > r0 + r1 )
		return false;



	r = abs( dist[2] * cos[1][2] - dist[1] * cos[2][2] );
	r0 = pOBB1->fAxisHalfLen[1] * absCos[2][2] + pOBB1->fAxisHalfLen[2] * absCos[1][2];
	r1 = pOBB2->fAxisHalfLen[0] * absCos[0][1] + pOBB2->fAxisHalfLen[1] * absCos[0][0];
	if( r > r0 + r1 )
		return false;




	return true;
}
