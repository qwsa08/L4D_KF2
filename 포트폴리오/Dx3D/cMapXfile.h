#pragma once
#include "iMap.h"

class cMapXfile : public iMap
{
private:
	ID3DXMesh* Mesh;
	std::vector<D3DMATERIAL9> Mtrls;
	std::vector<IDirect3DTexture9*> Textures;

public:
	cMapXfile();
	~cMapXfile();

	void Setup(char* szFilename);
	//void Render();

	virtual void Render() override;
	virtual bool GetHeight(IN float x, OUT float& y, IN float z) override;
};

