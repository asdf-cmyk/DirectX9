#include "stdafx.h"
#include "Terrain.h"


Terrain::Terrain()
	: m_pMesh(NULL)
{
}


Terrain::~Terrain()
{
}

void Terrain::LoadRaw()
{
	string sFullPath;
	//sFullPath += (string("/") + string(szFile));
	sFullPath = "HeightMapData/HeightMap.raw";

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "rb");

	while (true)
	{
		if (feof(fp)) break;

		m_vecHeight.push_back(fgetc(fp) / 4 - 21);
	}
	fclose(fp);

	m_vecHeight.pop_back();
}

void Terrain::SquareSet(int pv_i, int pv_j, int pv_rowNcol, vector<ST_PNT_VERTEX>& pv_vector)
{
	int maxWH = pv_rowNcol - 1;
	int tV = maxWH * 4;

	ST_PNT_VERTEX temp;
	temp.n = D3DXVECTOR3(0, 1, 0);

	int i2 = pv_i;
	int j2 = pv_j;
	temp.p.x = j2;
	temp.p.z = i2;
	temp.p.y = m_vecHeight[i2 * pv_rowNcol + j2];
	temp.t.x = j2 / 256.0f;
	//temp.t.y = (maxWH - i2) / 256.0f;
	temp.t.y = i2 / 256.0f;
	m_vecVertex.push_back(temp);

	i2 = pv_i + 1;
	j2 = pv_j + 1;
	temp.p.x = j2;
	temp.p.z = i2;
	temp.p.y = m_vecHeight[i2 * pv_rowNcol + j2];
	temp.t.x = j2 / 256.0f;
	//temp.t.y = (maxWH - i2) / 256.0f;
	temp.t.y = i2 / 256.0f;
	m_vecVertex.push_back(temp);

	i2 = pv_i;
	temp.p.x = j2;
	temp.p.z = i2;
	temp.p.y = m_vecHeight[i2 * pv_rowNcol + j2];
	temp.t.x = j2 / 256.0f;
	//temp.t.y = (maxWH - i2) / 256.0f;
	temp.t.y = i2 / 256.0f;
	m_vecVertex.push_back(temp);


	j2 = pv_j;
	temp.p.x = j2;
	temp.p.z = i2;
	temp.p.y = m_vecHeight[i2 * pv_rowNcol + j2];
	temp.t.x = j2 / 256.0f;
	//temp.t.y = (maxWH - i2) / 256.0f;
	temp.t.y = i2 / 256.0f;
	m_vecVertex.push_back(temp);

	i2 = pv_i + 1;
	temp.p.x = j2;
	temp.p.z = i2;
	temp.p.y = m_vecHeight[i2 * pv_rowNcol + j2];
	temp.t.x = j2 / 256.0f;
	//temp.t.y = (maxWH - i2) / 256.0f;
	temp.t.y = i2 / 256.0f;
	m_vecVertex.push_back(temp);

	i2 = pv_i + 1;
	j2 = pv_j + 1;
	temp.p.x = j2;
	temp.p.z = i2;
	temp.p.y = m_vecHeight[i2 * pv_rowNcol + j2];
	temp.t.x = j2 / 256.0f;
	//temp.t.y = (maxWH - i2) / 256.0f;
	temp.t.y = i2 / 256.0f;
	m_vecVertex.push_back(temp);
}

void Terrain::Setup()
{
	LoadRaw();
	D3DXCreateTextureFromFile(g_pD3DDevice, _T("HeightMapData/terrain.jpg"), &m_pTexture);

	int rowNcol = sqrt(m_vecHeight.size());
	vector<DWORD>		vecAttrBuf;
	//vecAttrBuf.push_back(0);

	ST_PNT_VERTEX temp;
	temp.n = D3DXVECTOR3(0, 1, 0);
	temp.t = D3DXVECTOR2(0, 0);

	for (int i = 0; i < rowNcol - 1; i++)
	{
		for (int j = 0; j < rowNcol - 1; j++)
		{
			SquareSet(i, j, rowNcol, m_vecVertex);
			vecAttrBuf.push_back(0);
			vecAttrBuf.push_back(0);
		}
	}


	//LPD3DXMESH	m_pMesh = NULL;
	/*HRESULT hr = D3DXCreateMeshFVF(vecAttrBuf.size(), m_vecVertex.size(), D3DXMESH_MANAGED, ST_PNT_VERTEX::FVF,
		g_pD3DDevice, &m_pMesh);*/
	D3DXCreateMeshFVF(vecAttrBuf.size(), m_vecVertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF, g_pD3DDevice, &m_pMesh);

	ST_PNT_VERTEX * pV = NULL;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &m_vecVertex[0], m_vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	m_pMesh->LockIndexBuffer(0, (LPVOID*)& pI);
	for (int i = 0; i < m_vecVertex.size(); ++i)
		pI[i] = i;
	m_pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	m_pMesh->LockAttributeBuffer(0, &pA);
	memcpy(pA, &vecAttrBuf[0], vecAttrBuf.size() * sizeof(DWORD));
	m_pMesh->UnlockAttributeBuffer();

	/*vector<DWORD> vecAdj(m_vecVertex.size());
	m_pMesh->GenerateAdjacency(0.0f, &vecAdj[0]);

	m_pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0], 0, 0, 0);*/
}

void Terrain::Render()
{
	D3DXMATRIXA16 matWorld;

	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0],
	//	sizeof(ST_PNT_VERTEX));
	m_pMesh->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	//g_pD3DDevice->SetTexture(0, NULL);
}

float Terrain::WalkOnTerra(float x, float z)
{
	float height;

	int OnTriangle;
	float minorityZ = z - (int)z;
	float minorityX = x - (int)x;
	if (minorityZ > minorityX)
	{
		OnTriangle = 2; // up tri
	}
	else OnTriangle = 1; // down tri

	if (x >= 0 && x < 256 && z >= 0 && z < 256)
		height = m_vecHeight[z * 257 + x];
	else
		return 0.0f;

	float uy, vy;
	float A = m_vecHeight[((int)z + 1) * 257 + (int)x];
	float B = m_vecHeight[((int)z + 1) * 257 + ((int)x + 1)];
	float C = m_vecHeight[(int)z * 257 + (int)x];
	float D = m_vecHeight[(int)z * 257 + ((int)x + 1)];
	switch (OnTriangle)
	{
	case 1:
		uy = C - D;
		vy = B - D;
		height = D + Lerp(0.0f, uy, 1.0f - minorityX) + Lerp(0.0f, vy, minorityZ);
		break;
	case 2:
		uy = B - A;
		vy = C - A;
		height = A + Lerp(0.0f, uy, minorityX) + Lerp(0.0f, vy, 1.0f - minorityZ);
		break;
	}


	/*if (x >= 0 && x < 256 && z >= 0 && z < 256)
		height = m_vecHeight[z * 257 + x];
	else
		height = 0.0f;*/

	return height;
}

float Terrain::GetHeight(int x, int z)
{
	float height;

	if (x >= 0 && x < 256 && z >= 0 && z < 256)
		height = m_vecHeight[z * 257 + x];
	else
		height = 0.0f;

	return height;
}
