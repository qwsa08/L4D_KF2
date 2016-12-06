#pragma once
class cRay
{
private:
	SYNTHESIZE(D3DXVECTOR3, m_vRayPos, RayPos);
	SYNTHESIZE(D3DXVECTOR3, m_vRayDir, RayDir);

public:
	cRay(void);
	~cRay(void);

	static cRay RayAtViewSpace(int x, int y);
	static cRay RayAtWorldSpace(int x, int y);
	bool IsPicked(ST_SPHERE& s);
};

