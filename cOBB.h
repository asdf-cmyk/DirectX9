#pragma once

class cSkinnedMesh;

class cOBB
{
public:
	cOBB();
	~cOBB();

private:
	D3DXVECTOR3		m_vOriCenterPos;
	D3DXVECTOR3		m_vOriAxisDir[3];

	D3DXVECTOR3		m_vCenterPos;
	D3DXVECTOR3		m_vAxisDir[3];
	float			m_fAxisLen[3];

	float			m_fAxisHalfLen[3];
	
	D3DXMATRIXA16	m_matWorldTM;

	//D3DXMATRIXA16	m_matWorldBox;
	LPD3DXMESH		m_pBoundingBox;
	D3DMATERIAL9	m_stBoxMtl;
	LPD3DXMESH			m_pMesh;
	vector<ST_PC_VERTEX>	m_vecVertexBB;
public:
	void Setup(cSkinnedMesh* pSkinnedMesh);
	void Update(D3DXMATRIXA16* pmatWorld);
	static bool IsCollision(cOBB* pOBB1, cOBB* pOBB2);

	void OBBBOX_Render(D3DCOLOR c);
};