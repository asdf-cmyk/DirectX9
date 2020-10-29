#include "stdafx.h"
#include "XFileLoader.h"


XFileLoader::XFileLoader()
	: m_pMesh(0)
{
}


XFileLoader::~XFileLoader()
{
}

bool XFileLoader::Setup()
{
	HRESULT hr = 0;

	ID3DXBuffer* adjBuffer = 0;
	ID3DXBuffer* mtrlBuffer = 0;
	DWORD numMtrls = 0;

	hr = D3DXLoadMeshFromX(
		L"bigship1.X",
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&adjBuffer,
		&mtrlBuffer,
		0,
		&numMtrls,
		&m_pMesh);

	if (FAILED(hr))
	{
		::MessageBox(0, L"D3DXLoadMeshFromX() - FAILED", 0, 0);
		return false;
	}


	if (!(m_pMesh->GetFVF() & D3DFVF_NORMAL))
	{
		ID3DXMesh* pTempMesh = 0;
	}


	if (mtrlBuffer != 0 && numMtrls != 0)
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		for (int i = 0; i < numMtrls; i++)
		{
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;

			m_vecMtrls.push_back(mtrls[i].MatD3D);

			if (mtrls[i].pTextureFilename != 0)
			{
				IDirect3DTexture9* tex = 0;
				D3DXCreateTextureFromFileA(
					g_pD3DDevice,
					mtrls[i].pTextureFilename,
					&tex);

				m_vecTextures.push_back(tex);
			}
			else
			{
				m_vecTextures.push_back(0);
			}
		}
	}

	SafeRelease(mtrlBuffer);

	return true;
}

void XFileLoader::Update(float timeDelta)
{
	if (g_pD3DDevice)
	{
		static float y = 0.0f;
		D3DXMATRIX yRot, matT;
		D3DXMatrixRotationZ(&yRot, y);
		D3DXMatrixIdentity(&matT);
		D3DXMatrixTranslation(&matT, 0, 9.0f, 0);
		y += timeDelta;

		if (y >= 6.28f) y = 0.0f;

		/*D3DXMATRIX*/ World = yRot * matT;

		//g_pD3DDevice->SetTransform(D3DTS_WORLD, &World);
	}
}

bool XFileLoader::Display()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &World);
	for (int i = 0; i < m_vecMtrls.size(); i++)
	{
		g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);
		g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
		m_pMesh->DrawSubset(i);
	}

	return true;
}
