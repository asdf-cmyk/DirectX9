#pragma once
class cFrustum
{
public:
	cFrustum();
	~cFrustum();
private:
	vector<D3DXVECTOR3>		m_vecProjVertex;
	vector<D3DXVECTOR3>		m_vecWorldVertex;
	vector<D3DXPLANE>		m_vecPlane;

public:
	void Setup();
	void Update();
	bool IsIn(ST_SPHERE* pSphere);


};