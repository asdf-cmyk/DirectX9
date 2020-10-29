#pragma once
class Terrain
{
	vector<float>			m_vecHeight;
	vector<ST_PNT_VERTEX>	m_vecVertex;

	LPDIRECT3DTEXTURE9		m_pTexture;
	LPD3DXMESH				m_pMesh;
public:
	Terrain();
	~Terrain();

	void LoadRaw();
	void SquareSet(int, int, int, vector<ST_PNT_VERTEX>&);
	void Setup();
	void Render();

	float Lerp(float a, float b, float t)
	{
		return a - (a*t) + (b*t);
	}
	float WalkOnTerra(float, float);
	float GetHeight(int, int);
};