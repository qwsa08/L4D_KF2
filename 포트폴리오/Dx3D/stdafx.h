// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <d3dx9.h>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <assert.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern HWND	g_hWnd;

#define EPSILON 0.00001f

#define SAFE_ADD_REF(p) if(p) { (p)->AddRef(); }
#define SAFE_RELEASE(p) if(p) { (p)->Release(); (p) = NULL; }
#define SAFE_DELETE(p) if(p) { delete (p); (p) = NULL; }
#define SAFE_DELETE_ARRAY(p) if(p) { delete [] (p); }

#define SINGLETONE(class_name) private:\
	class_name(void);\
	~class_name(void);\
public:\
	static class_name* GetInstance()\
	{\
		static class_name instance;\
		return &instance;\
	}

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }

#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: inline varType& Get##funName(void) { return varName; }\
public: inline void Set##funName(const varType& var){ varName = var; }

#define SYNTHESIZE_ADD_REF(varType, varName, funName)    \
protected: varType varName; \
public: virtual varType Get##funName(void) const { return varName; } \
public: virtual void Set##funName(varType var){\
	if (varName != var) {\
	SAFE_ADD_REF(var);\
	SAFE_RELEASE(varName);\
	varName = var;\
	}\
}

// 1. Position 정점의 좌표 x,y,z(float)			: D3DFVF_XYZ
// 2. RHW (float)                               : D3DFVF_XYZRHW (D3DFVF_XYZ 또는 D3DFVF_NORMAL과 같이 사용불가)
// 3. Blending Weight Data 결합 가중치 (float)	: D3DFVF_XYZB1 ~ D3DFVF_XYZB5
// 4. Vertex Normal 정점의 법선 벡터 x,y,z(float)	: D3DFVF_NORMAL
// 5. Vertex Point Size 정점의 점 크기 (float)	: D3DFVF_PSIZE
// 6. Diffuse Color (DWORD)						: D3DFVF_DIFFUSE
// 7. Specular Color (DWORD)                    : D3DFVF_SPECULAR
// 8. Texture Coordinate Set 1 (float)          : D3DFVF_TEX0 - D3DFVF_TEX8

struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;

	ST_PC_VERTEX() : p(0, 0, 0), c(D3DCOLOR_XRGB(0, 0, 0)) {}
	ST_PC_VERTEX(D3DXVECTOR3 _p, D3DCOLOR _c) : p(_p), c(_c) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE, };
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2	t;

	ST_PT_VERTEX() : p(0, 0, 0), t(0, 0) {}
	ST_PT_VERTEX(D3DXVECTOR3 _p, D3DXVECTOR2 _t) : p(_p), t(_t) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1, };
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2	t;

	ST_PNT_VERTEX() : p(0, 0, 0), n(0, 0, 0), t(0, 0) {}
	ST_PNT_VERTEX(D3DXVECTOR3 _p, D3DXVECTOR3 _n, D3DXVECTOR2 _t) : p(_p), n(_n), t(_t) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, };
};

struct ST_POS_SAMPLE
{
	int				n;
	D3DXVECTOR3		p;
};

struct ST_ROT_SAMPLE
{
	int				n;
	D3DXQUATERNION	q;
};

struct ST_SPHERE
{
	D3DXVECTOR3 vCenter;
	float		fRadius;
	bool		isPicked;

	ST_SPHERE() : vCenter(0, 0, 0), fRadius(0.0f), isPicked(false) {}
	ST_SPHERE(D3DXVECTOR3 _vCenter, float _fRadius, bool _isPicked)
		: vCenter(_vCenter), fRadius(_fRadius), isPicked(_isPicked) {}
};

struct ST_BoundingBox
{
	D3DXVECTOR3 vCenter;
	D3DXVECTOR3 _min;
	D3DXVECTOR3 _max;

	ST_BoundingBox() : vCenter(0, 0, 0), _min(D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX)), _max(D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX)) {}
	ST_BoundingBox(D3DXVECTOR3 _vCenter, D3DXVECTOR3 min, D3DXVECTOR3 max)
		: vCenter(_vCenter), _min(min), _max(max) {}
};

struct ST_OBB
{
	D3DXVECTOR3 vCenter;
	D3DXVECTOR3 m_vOrgCenterPos;
	D3DXVECTOR3 vAxisDir[3];
	D3DXVECTOR3 m_vOrgAxisDir[3];
	float fAxisLen[3];
	float fAxisHalfLen[3];
	ST_OBB()
	{
		vCenter = D3DXVECTOR3(0, 0, 0);
		m_vOrgCenterPos = D3DXVECTOR3(0, 0, 0);
		for (int i = 0; i < 3; i++)
		{
			vAxisDir[i] = D3DXVECTOR3(0, 0, 0);
			m_vOrgAxisDir[i] = D3DXVECTOR3(0, 0, 0);
			fAxisHalfLen[i] = 0.f;
			fAxisLen[i] = 0.f;
		}
	}
};

struct ST_OBBbox
{
	D3DXVECTOR3 _min;
	D3DXVECTOR3 _max;
	ST_OBB     OBB;

	ST_OBBbox() : _min(0, 0, 0), _max(0, 0, 0), OBB() {}
	ST_OBBbox(D3DXVECTOR3 min, D3DXVECTOR3 max, ST_OBB _OBB)
		:_min(min), _max(max), OBB(_OBB) {}

};

#include "cDeviceManager.h"
#include "cTimeManager.h"
#include "cTextureManager.h"
#include "cSkinnedMeshManager.h"
#include "cAutoReleasePool.h"
#include "cObject.h"
#include "cGameObject.h"