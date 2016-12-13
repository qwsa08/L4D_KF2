#pragma once

class iMap : public cObject
{
public:
	iMap(void);
	virtual ~iMap(void);

	virtual void Render(IN D3DXVECTOR4* LightPosition, IN D3DXVECTOR4* LightDirection) = 0;
	virtual bool GetHeight(IN float x, OUT float& y, IN float z) = 0;
};

