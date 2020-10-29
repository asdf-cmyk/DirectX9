#include "stdafx.h"
#include "cZealot.h"
#include "cSkinnedMesh.h"
#include "cOBB.h"


cZealot::cZealot()
	: m_pSkinnedMesh(NULL)
	, m_pCharacterController(NULL)
	, m_pOBB(NULL)
{
}


cZealot::~cZealot()
{
	SafeRelease(m_pCharacterController);
	SafeDelete(m_pSkinnedMesh);
	SafeDelete(m_pOBB);
}

void cZealot::Setup()
{
	m_pSkinnedMesh = new cSkinnedMesh("Zealot", "zealot.X");
	m_pSkinnedMesh->SetRandomTrackPosition();

	m_pOBB = new cOBB;
	m_pOBB->Setup(m_pSkinnedMesh);
}

void cZealot::Update(iMap * pMap)
{
	if (m_pCharacterController)
		m_pCharacterController->Update(pMap);

	if (m_pOBB)
		m_pOBB->Update(m_pCharacterController ?
			m_pCharacterController->GetTransform() : NULL);
}

void cZealot::Render(D3DCOLOR c)
{
	if (m_pCharacterController)
		m_pSkinnedMesh->SetTransform(
			m_pCharacterController->GetTransform());

	m_pSkinnedMesh->UpdateAndRender();

	//if (m_pOBB)
	//	m_pOBB->OBBBOX_Render(c);
}

cOBB * cZealot::GetOBB()
{
	return m_pOBB;
}
