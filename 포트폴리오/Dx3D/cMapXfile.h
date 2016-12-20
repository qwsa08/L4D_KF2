#pragma once

class cMapXfile 
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

	void Render();

};

