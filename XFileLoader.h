#pragma once
class XFileLoader
{
	ID3DXMesh* m_pMesh = 0;
	vector<D3DMATERIAL9> m_vecMtrls;
	vector<IDirect3DTexture9*> m_vecTextures;
	D3DXMATRIX World;

public:
	XFileLoader();
	~XFileLoader();

	bool Setup();
	void Update(float);
	bool Display();
};

