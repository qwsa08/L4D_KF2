#include "StdAfx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"
//#include "cPAllocateHierarchy.h"
#include "cSkinnedMeshManager.h"

//static LPD3DXMESH			pBoundingSphereMesh;
//static LPD3DXMESH			pBoundingBoxMesh;
cSkinnedMesh::cSkinnedMesh(char* szFolder, char* szFilename)
	: m_pRootFrame(NULL)
	, m_pAnimController(NULL)
	, m_dwWorkingPaletteSize(0)
	, m_pmWorkingPalette(NULL)
	, m_pEffect(NULL)
	, m_vPosition(0, 0, 0)
	, m_FrameNum(0)
	, m_isBlending(false)
	, m_fBlendTime(0.003f)
	, m_fPassedBlendTime(0.0f)
	, m_bChange(false)
	, m_fTimer(0.f)

{

	cSkinnedMesh* pSkinnedMesh =  g_pSkinnedMeshManager->GetSkinnedMesh(szFolder, szFilename);
	
	m_pRootFrame = pSkinnedMesh->m_pRootFrame;
	m_dwWorkingPaletteSize = pSkinnedMesh->m_dwWorkingPaletteSize;
	m_pmWorkingPalette = pSkinnedMesh->m_pmWorkingPalette;
	m_pEffect = pSkinnedMesh->m_pEffect;
	m_stBoundingSphere = pSkinnedMesh->m_stBoundingSphere;
	m_stBoundingBox = pSkinnedMesh->m_stBoundingBox;

	pSkinnedMesh->m_pAnimController->CloneAnimationController(
		pSkinnedMesh->m_pAnimController->GetMaxNumAnimationOutputs(),
		pSkinnedMesh->m_pAnimController->GetMaxNumAnimationSets(),
		pSkinnedMesh->m_pAnimController->GetMaxNumTracks(),
		pSkinnedMesh->m_pAnimController->GetMaxNumEvents(),
		&m_pAnimController);


}

cSkinnedMesh::cSkinnedMesh()
	: m_pRootFrame(NULL)
	, m_pAnimController(NULL)
	, m_dwWorkingPaletteSize(0)
	, m_pmWorkingPalette(NULL)
	, m_pEffect(NULL)
{
}

cSkinnedMesh::~cSkinnedMesh(void)
{
	SAFE_RELEASE(m_pAnimController);
	SAFE_RELEASE(m_stBoundingSphere.pBoundingSphereMesh);
	SAFE_RELEASE(m_stBoundingBox.pBoundingBoxMesh);
}

void cSkinnedMesh::Load( char* szDirectory, char* szFilename )
{
	m_pEffect = LoadEffect("MultiAnimation.hpp");
							
	int nPaletteSize = 0;
	m_pEffect->GetInt("MATRIX_PALETTE_SIZE", &nPaletteSize);

	cAllocateHierarchy ah;
	ah.SetDirectory(szDirectory);
	ah.SetDefaultPaletteSize(nPaletteSize);
	
	std::string sFullPath(szDirectory);
	sFullPath += std::string(szFilename);

	D3DXLoadMeshHierarchyFromX(sFullPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&ah,
		NULL,
		(LPD3DXFRAME*)&m_pRootFrame,
		&m_pAnimController);
	m_stBoundingSphere = ah.GetBoundingSphere();
	//m_stBoundingSphere.vCenter = (ah.GetMin() + ah.GetMax()) / 2.0f;
	//m_stBoundingSphere.fRadius = D3DXVec3Length( &(ah.GetMin() - ah.GetMax()) );

	//-------------------바운딩 박스
	m_stBoundingBox = ah.GetBoundingBox();

	if (m_stBoundingSphere.pBoundingSphereMesh == NULL)
	{
		D3DXCreateSphere(g_pD3DDevice, 
			m_stBoundingSphere.fRadius,
			20, 
			20, 
			&m_stBoundingSphere.pBoundingSphereMesh,
			NULL);
	}
	if (m_stBoundingBox.pBoundingBoxMesh == NULL)
	{
		D3DXCreateBox(g_pD3DDevice,
			m_stBoundingBox._max.x - m_stBoundingBox._min.x,
			m_stBoundingBox._max.y - m_stBoundingBox._min.y,
			m_stBoundingBox._max.z - m_stBoundingBox._min.z,
			&m_stBoundingBox.pBoundingBoxMesh,
			NULL);

	}

	if( m_pmWorkingPalette )
		delete [] m_pmWorkingPalette;

	m_dwWorkingPaletteSize = ah.GetMaxPaletteSize();
	m_pmWorkingPalette = new D3DXMATRIX[ m_dwWorkingPaletteSize];
	if( m_pmWorkingPalette == NULL )
	{
		m_dwWorkingPaletteSize = 0;
	}

	if(m_pRootFrame)
		SetupBoneMatrixPtrs(m_pRootFrame);
}

void cSkinnedMesh::UpdateAndRender(D3DXMATRIXA16* pmat)
{	
	if(m_pAnimController)
	{
		m_pAnimController->AdvanceTime(g_pTimeManager->GetDeltaTime(), NULL);
	}

	if(m_pRootFrame)
	{
		D3DXMATRIXA16 mat , matI;
		D3DXMatrixIdentity(&mat);
		D3DXMatrixIdentity(&matI);
		
		//D3DXMatrixTranslation(&mat, m_vPosition.x, m_vPosition.y, m_vPosition.z);
		if(pmat)
		{
			mat = *pmat;
		}
	//	else
	//	{
	//		D3DXMatrixTranslation(&mat, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	//	}
		
		Update(m_pRootFrame, &mat);
		Render(m_pRootFrame);

		if (m_stBoundingSphere.pBoundingSphereMesh)
		{
			//D3DXVec3TransformCoord(&m_stBoundingSphere.vCenter, &m_stBoundingSphere.vCenter, &matI);
			D3DXMatrixTranslation(&matI,
				m_stBoundingSphere.vCenter.x,
				m_stBoundingSphere.vCenter.y,
				m_stBoundingSphere.vCenter.z);
			mat *= matI;

			if (false)
			{
				g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
				g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
				m_stBoundingSphere.pBoundingSphereMesh->DrawSubset(0);
				g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			}
		}
//		if (m_stBoundingBox.pBoundingBoxMesh)
//		{
//			g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
//			g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
//			m_stBoundingBox.pBoundingBoxMesh->DrawSubset(0);
//			g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
//		}
	}
}

void cSkinnedMesh::RenderPlayer(ST_BONE* pBone)
{
	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		while (pBoneMesh)
		{
			for (size_t i = 0; i < pBoneMesh->vecMaterial.size(); ++i)
			{
				g_pD3DDevice->SetMaterial(&pBoneMesh->vecMaterial[i]);
				g_pD3DDevice->SetTexture(0, pBoneMesh->vecTexture[i]);
				pBoneMesh->pWorkingMesh->DrawSubset(i);
			}
			pBoneMesh = (ST_BONE_MESH*)pBoneMesh->pNextMeshContainer;
		}
	}

	if (pBone->pFrameFirstChild)
	{
		Render((ST_BONE*)pBone->pFrameFirstChild);
	}

	if (pBone->pFrameSibling)
	{
		Render((ST_BONE*)pBone->pFrameSibling);
	}
}
void cSkinnedMesh::Render(ST_BONE* pBone /*= NULL*/)
{
	assert(pBone);

	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.
	if(pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;

		// get bone combinations
		LPD3DXBONECOMBINATION pBoneCombos = 
			( LPD3DXBONECOMBINATION )( pBoneMesh->pBufBoneCombos->GetBufferPointer() );

		D3DXMATRIXA16 matViewProj, matView, matProj;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
		matViewProj = matView * matProj;

		D3DXMATRIXA16 mView, mInvView;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &mView);
		D3DXMatrixInverse(&mInvView, 0, &mView);
		D3DXVECTOR3 vEye = D3DXVECTOR3(0, 0, 0);
		D3DXVec3TransformCoord(&vEye, &vEye, &mInvView);

		// for each palette
		for( DWORD dwAttrib = 0; dwAttrib < pBoneMesh->dwNumAttrGroups; ++ dwAttrib )
		{
			// set each transform into the palette
			for( DWORD dwPalEntry = 0; dwPalEntry < pBoneMesh->dwNumPaletteEntries; ++ dwPalEntry )
			{
				DWORD dwMatrixIndex = pBoneCombos[ dwAttrib ].BoneId[ dwPalEntry ];
				if( dwMatrixIndex != UINT_MAX )
				{
					m_pmWorkingPalette[ dwPalEntry ] = 
						pBoneMesh->pBoneOffsetMatrices[ dwMatrixIndex ] * 
						(*pBoneMesh->ppBoneMatrixPtrs[ dwMatrixIndex ]);
				}
			}

			// set the matrix palette into the effect
			m_pEffect->SetMatrixArray( "amPalette",
				m_pmWorkingPalette,
				pBoneMesh->dwNumPaletteEntries );

			m_pEffect->SetMatrix("g_mViewProj", &matViewProj);
			m_pEffect->SetVector("vLightDiffuse", &D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ) );
			m_pEffect->SetVector("vWorldLightPos", &D3DXVECTOR4( 500.0f, -1000.0f, 500.0f, 1.0f ) );
			m_pEffect->SetVector("vWorldCameraPos", &D3DXVECTOR4( vEye, 1.0f ) );
			m_pEffect->SetVector("vMaterialAmbient", &D3DXVECTOR4( 0.2f, 0.2f, 0.2f, 0.2f ) );
			m_pEffect->SetVector("vMaterialDiffuse", &D3DXVECTOR4( 0.2f, 0.2f, 0.2f, 0.2f ) );

			// we're pretty much ignoring the materials we got from the x-file; just set
			// the texture here
			m_pEffect->SetTexture( "g_txScene", pBoneMesh->vecTexture[ pBoneCombos[ dwAttrib ].AttribId ] );

			// set the current number of bones; this tells the effect which shader to use
			m_pEffect->SetInt( "CurNumBones", pBoneMesh->dwMaxNumFaceInfls - 1 );

			// set the technique we use to draw
			m_pEffect->SetTechnique( "Skinning20" );

			UINT uiPasses, uiPass;

			// run through each pass and draw
			m_pEffect->Begin( & uiPasses, 0 );
			for( uiPass = 0; uiPass < uiPasses; ++ uiPass )
			{
				m_pEffect->BeginPass( uiPass );
				pBoneMesh->pWorkingMesh->DrawSubset( dwAttrib );
				m_pEffect->EndPass();
			}
			m_pEffect->End();
		}
	}

	//재귀적으로 모든 프레임에 대해서 실행.
	if(pBone->pFrameSibling)
	{
		Render((ST_BONE*)pBone->pFrameSibling);
	}

	if(pBone->pFrameFirstChild)
	{
		Render((ST_BONE*)pBone->pFrameFirstChild);
	}
}

LPD3DXEFFECT cSkinnedMesh::LoadEffect( char* szFilename )
{
	LPD3DXEFFECT pEffect = NULL;

	D3DXMACRO mac[2] =
	{
		{ "MATRIX_PALETTE_SIZE_DEFAULT", "35" },
		{ NULL,                          NULL }
	};

	D3DCAPS9 caps;
	D3DXMACRO *pmac = NULL;
	g_pD3DDevice->GetDeviceCaps( & caps );
	if( caps.VertexShaderVersion > D3DVS_VERSION( 1, 1 ) )
		pmac = mac;

	DWORD dwShaderFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DXSHADER_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

#ifdef DEBUG_VS
	dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
	dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

	ID3DXBuffer* pBuffer = NULL;
	if(FAILED(D3DXCreateEffectFromFile( g_pD3DDevice,
		szFilename,
		pmac,
		NULL,
		dwShaderFlags,
		NULL,
		&pEffect,
		&pBuffer )))
	{
		// if creation fails, and debug information has been returned, output debug info
		if (pBuffer)
		{
			OutputDebugStringA((char*)pBuffer->GetBufferPointer());
			SAFE_RELEASE(pBuffer);
		}

		return NULL;
	}

	return pEffect;
}

void cSkinnedMesh::Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent )
{
	pCurrent->CombinedTransformationMatrix = pCurrent->TransformationMatrix;
	if(pmatParent)
	{
		pCurrent->CombinedTransformationMatrix =
			pCurrent->CombinedTransformationMatrix * (*pmatParent);
	}

	if(pCurrent->pFrameSibling)
	{
		Update((ST_BONE*)pCurrent->pFrameSibling, pmatParent);
	}

	if(pCurrent->pFrameFirstChild)
	{
		Update((ST_BONE*)pCurrent->pFrameFirstChild, &(pCurrent->CombinedTransformationMatrix));
	}


	
}

void cSkinnedMesh::SetupBoneMatrixPtrs( ST_BONE* pBone )
{
	assert(pBone);

	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.
	if(pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if(pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			// pSkinInfo->GetNumBones() 으로 영향받는 본의 개수를 찾음.
			// pSkinInfo->GetBoneName(i) 로 i번 프레임의 이름을 찾음
			// D3DXFrameFind(루트 프레임, 프레임 이름) 로 프레임을 찾음.
			// 찾아서 월드매트릭스를 걸어줘라.
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				LPCSTR szBoneName = pSkinInfo->GetBoneName(i);
				if(szBoneName == NULL || strlen(szBoneName) == 0)
					continue;
				ST_BONE* pInfluence = (ST_BONE*)D3DXFrameFind(m_pRootFrame, szBoneName);
				pBoneMesh->ppBoneMatrixPtrs[i] = &(pInfluence->CombinedTransformationMatrix);
			}
		}
	}

	//재귀적으로 모든 프레임에 대해서 실행.
	if(pBone->pFrameSibling)
	{
		SetupBoneMatrixPtrs((ST_BONE*)pBone->pFrameSibling);
	}

	if(pBone->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs((ST_BONE*)pBone->pFrameFirstChild);
	}
}

void cSkinnedMesh::SetNomalAnimationIndex(int nIndex)
{
	if (!m_pAnimController)
		return;

	
	LPD3DXANIMATIONSET pAnimSet = NULL;
	m_pAnimController->GetAnimationSet(nIndex, &pAnimSet);
	m_pAnimController->SetTrackAnimationSet(0, pAnimSet);
	
	SAFE_RELEASE(pAnimSet);
}

void cSkinnedMesh::SetAnimationIndex( int nIndex )
{
	if (m_isBlending&& !m_FrameNum) return;
	float a = AnimationFrame(m_FrameNum);

	//switch (m_GunName)
	//{
	//case HANDGUN:
	//	/*if (m_FrameNum == 1) m_fBlendTime = 0.03f;
	//	else*/ m_fBlendTime = 0.03f;
	//	break;
	//case BUSTER:
	//	if (m_FrameNum == 1) m_fBlendTime = 0.01f;
	//	//else m_fBlendTime = 0.1f;
	//	break;
	//case KNIFE:
	//	if (m_FrameNum == 1) m_fBlendTime = 0.3f;
	//	else m_fBlendTime = 0.3f;
	//	break;
	//case SHOT:
	//	if (m_FrameNum == 1) m_fBlendTime = 0.1f;
	//	else m_fBlendTime = 0.01f;
	//	break;
	//case HEAL:
	//	if (m_FrameNum == 1) m_fBlendTime = 0.01f;
	//	//else m_fBlendTime = 0.1f;
	//	break;
	//default:
	//	break;
	//}

	LPD3DXANIMATIONSET pPrevAnimSet = NULL;
	LPD3DXANIMATIONSET pCurrAnimSet = NULL;

	// 기존 애니매이션을 1번 트랙에 세팅
	m_pAnimController->GetTrackAnimationSet(0, &pPrevAnimSet);
	m_pAnimController->GetAnimationSet(nIndex, &pCurrAnimSet);

	D3DXTRACK_DESC stTrackDesc;
	m_pAnimController->GetTrackDesc(0, &stTrackDesc);
	stTrackDesc.Position -= m_fBlendTime;
	m_pAnimController->SetTrackDesc(1, &stTrackDesc);

	// 새로운 애니매이션을 0번 트랙에 세팅
	m_pAnimController->SetTrackAnimationSet(1, pPrevAnimSet);
	m_pAnimController->SetTrackAnimationSet(0, pCurrAnimSet);

	// 트랙 가중치 설정
	m_pAnimController->SetTrackWeight(0, 0.0f);
	m_pAnimController->SetTrackWeight(1, 1.0f);

	// 트랙 포지션 설정
	
	//m_pAnimController->SetTrackPosition(1, a - m_fBlendTime);// a - m_fBlendTime);
	m_pAnimController->SetTrackPosition(0, 0.0f);

	m_fPassedBlendTime = 0.0f;
	m_pAnimController->ResetTime();
	m_pAnimController->AdvanceTime(0, NULL);
	m_isBlending = true;

	SAFE_RELEASE(pPrevAnimSet);
	SAFE_RELEASE(pCurrAnimSet);
}
void cSkinnedMesh::SetskinningAnimationIndex(int current, int next)
{

}
float cSkinnedMesh::AnimationFrame(int num)
{
	LPD3DXANIMATIONSET pAnimSet = NULL;
	m_pAnimController->GetAnimationSet(num, &pAnimSet);
	double dPeriod = pAnimSet->GetPeriod();

	return dPeriod;

	SAFE_RELEASE(pAnimSet);
}
void cSkinnedMesh::AnimationReset()
{
	m_pAnimController->ResetTime();
	m_pAnimController->AdvanceTime(0, NULL);
	
}
void cSkinnedMesh::Destroy()
{
	cAllocateHierarchy ah;
	D3DXFrameDestroy((LPD3DXFRAME)m_pRootFrame, &ah);
	SAFE_DELETE_ARRAY(m_pmWorkingPalette);
	SAFE_RELEASE(m_pEffect);
}

void cSkinnedMesh::ResetTrackPosition()
{
	m_pAnimController->SetTrackPosition(0, 0.0f);
}

void cSkinnedMesh::SetRandomTrackPosition()
{
	m_pAnimController->SetTrackPosition(0, (rand() % 100) / 10.0f);
}


void cSkinnedMesh::Render(D3DXMATRIXA16* pmat)
{
	D3DXMATRIXA16 mat, matI;
	D3DXMatrixIdentity(&mat);
	D3DXMatrixIdentity(&matI);
	if (pmat)
	{
		mat = *pmat;
	}
	RenderPlayer(m_pRootFrame);
	//if (m_stBoundingSphere.pBoundingSphereMesh)
	//{
	//	//이걸하면 반대방향으로 원운동함
	//
	//	D3DXMatrixTranslation(&matI,
	//	m_stBoundingSphere.vCenter.x,
	//	m_stBoundingSphere.vCenter.y,
	//	m_stBoundingSphere.vCenter.z);
	//	mat *= matI;
	//
	//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	//	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//	m_stBoundingSphere.pBoundingSphereMesh->DrawSubset(0);
	//	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//}
	if (m_stBoundingBox.pBoundingBoxMesh)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		m_stBoundingBox.pBoundingBoxMesh->DrawSubset(0);
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}


}
void cSkinnedMesh::Update(D3DXMATRIXA16* pmat, int state)
{
	if (m_pRootFrame == NULL) return;
	m_pAnimController->AdvanceTime(g_pTimeManager->GetDeltaTime(), NULL);

	
	if (m_isBlending)
	{
		m_fPassedBlendTime += g_pTimeManager->GetDeltaTime();

		if (m_fPassedBlendTime >= m_fBlendTime)
		{
			m_isBlending = false;
			m_pAnimController->SetTrackWeight(0, 1.0f);
			m_pAnimController->SetTrackWeight(1, 0.0f);
			m_pAnimController->SetTrackEnable(1, false);
			m_fPassedBlendTime = 0.f;
		}
		else
		{
			float fWeight = m_fPassedBlendTime / m_fBlendTime;
			m_pAnimController->SetTrackWeight(0, fWeight);
			m_pAnimController->SetTrackWeight(1, 1.0f - fWeight);
		}
	}
	else
	{
		D3DXTRACK_DESC tc;
		m_pAnimController->GetTrackDesc(0, &tc);
		float m_fPassedTime = tc.Position;
		float a = AnimationFrame(m_FrameNum);
		if (m_fPassedTime - 0.001 >= a)
		{
			if (m_FrameNum != 0)
			{
				m_FrameNum = 0;
				SetAnimationIndex(0);
			}
		}
	}
	/*else
	{
		m_fTimer += g_pTimeManager->GetDeltaTime();
		float a = AnimationFrame(m_FrameNum);
		if (m_fTimer > a-0.01)
		{
			m_fTimer = 0.f;
			m_bChange = false;
		}
	}*/
	/*if (m_fPassedBlendTime >= a)
	{
		m_fPassedBlendTime = 0.f;
		if (m_FrameNum != 0)
		{
			m_FrameNum = 0;
			SetAnimationIndex(0);
		}
	}*/
	
	


	Update(m_pRootFrame, pmat);
	SetupBoneMatrixPtrs(m_pRootFrame);
}