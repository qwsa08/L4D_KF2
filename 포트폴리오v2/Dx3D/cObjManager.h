#pragma once
class cObjMap;

class cObjManager
{
private:
	cObjMap*	m_Map;

public:
	cObjManager();
	~cObjManager();

	bool GetHeight(IN float x, OUT float& y, IN float z);
	bool Plane(D3DXVECTOR3 center, float radius);
};

