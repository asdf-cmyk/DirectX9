#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"
#include "cCamera.h"
#include "cCubePC.h"
#include "cGrid.h"
#include "cCubeMan.h"
#include "cObjLoader.h"
#include "cGroup.h"
#include "cObjMap.h"	// << : 

#include "cAseLoader.h"
#include "cFrame.h"
#include "cRay.h"
#include "cHeightMap.h"
#include "cSkinnedMesh.h"
#include "cFrustum.h"

#include "cZealot.h"
#include "cOBB.h"

#include "XFileLoader.h"
#include "PopUpUI.h"
#include "UISprite.h"

DWORD FtoDw(float f)
{
	return *((DWORD*)&f);
}

cMainGame::cMainGame()
	: m_pCubePC(NULL)
	, m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCubeMan(NULL) 
	, m_pTexture(NULL)
	, m_pMap(NULL) 
	, m_pRootFrame(NULL) 
	, m_pMeshSphere(NULL)
	, m_pMeshTeapot(NULL)
	, m_pObjMesh(NULL)
	, m_pSkinnedMesh(NULL)
	, m_pXFileLoader(NULL)
	, m_pFrustum(NULL)
	//, m_pHoldZealot(NULL)
	//, m_pMoveZealot(NULL)
	, m_pFont(NULL)
	, m_p3DText(NULL)
	, m_pSprite(NULL)
	, m_pTextureUI(NULL)
	, m_pPopUpUI(NULL)
	, m_pTex0(NULL)
	, m_pTex1(NULL)
	, m_pTex2(NULL)
	, m_pTex3(NULL)
	, m_nType(-1)
{
}


cMainGame::~cMainGame()
{
	//SafeDelete(m_pHoldZealot);
	//SafeDelete(m_pMoveZealot);

	SafeDelete(m_pCubePC); 
	SafeDelete(m_pCamera); 
	SafeDelete(m_pGrid); 
	SafeDelete(m_pCubeMan); 
	SafeDelete(m_pMap); 
	SafeDelete(m_pSkinnedMesh);
	SafeDelete(m_pFrustum);
	SafeDelete(m_pXFileLoader);
	SafeDelete(m_pPopUpUI);

	SafeRelease(m_pTexture); 
	SafeRelease(m_pMeshSphere); 
	SafeRelease(m_pMeshTeapot); 
	SafeRelease(m_pObjMesh); 
	SafeRelease(m_pFont);
	SafeRelease(m_p3DText);
	SafeRelease(m_pSprite);
	SafeRelease(m_pTextureUI);

	for each(auto p in m_vecObjMtlTex)
		SafeRelease(p); 

	g_pFontManager->Destroy();
	
	for each(auto p in m_vecGroup)
		SafeRelease(p);
	m_vecGroup.clear(); 

	m_pRootFrame->Destroy(); 
	g_pObjectManager->Destroy(); 

	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	//m_pCubePC = new cCubePC; 
	//m_pCubePC->Setup(); 

	/*m_pCubeMan = new cCubeMan; 
	m_pCubeMan->Setup();*/

	m_pCamera = new cCamera; 
	m_pCamera->Setup(NULL); //(&m_pCubeMan->GetPosition());
	// &m_pCubePC->GetPosition());

	m_pGrid = new cGrid; 
	m_pGrid->Setup(); 

	//Setup_Frustum();

	/*{
		cAseLoader l; 
		m_pRootFrame = l.Load("woman/woman_01_all.ASE"); 
	}*/

	//Setup_Particle();
	Setup_MultiTexture();

	//Setup_Texture(); 
	//Setup_Obj();
	//Setup_OBB();
	Set_Light();

	Create_Font();

	Setup_UI();

	//Setup_MeshObject(); 
	//Setup_PickingObj(); 
	//Setup_HeightMap();
	//Setup_SphereGroup();

	/*m_pXFileLoader = new XFileLoader;
	m_pXFileLoader->Setup();*/

	/*m_pSkinnedMesh = new cSkinnedMesh;
	m_pSkinnedMesh->Setup("Zealot", "zealot.X");*/
}

void cMainGame::Update()
{
	//if (m_pCubePC)
	//	m_pCubePC->Update(); 

	if (m_pCubeMan)
		m_pCubeMan->Update(m_pMap);

	/*g_pTimeManager->Update();
	if (m_pSkinnedMesh)
	{
		m_pSkinnedMesh->Update();

		if (((double)GetTickCount() - animStart) * 0.001f >= animTime - 0.3f)
		{
			m_pSkinnedMesh->SetAnimationIndex(4);
			animTime = 0.0f;
			animStart = 0.0f;
		}
	}*/

	/*if (m_pFrustum)
		m_pFrustum->Update();*/

	if (m_pCamera)
		m_pCamera->Update(); 
	//FrustumCulling();

	//Update_Particle();
	Update_MultiTexture();

	/*if (m_pHoldZealot)
		m_pHoldZealot->Update(m_pMap);
	if (m_pMoveZealot)
		m_pMoveZealot->Update(m_pMap);*/

	UI_Update();

	/*if (m_pRootFrame)
		m_pRootFrame->Update(m_pRootFrame->GetKeyFrame(), NULL); */

	/*if (m_pXFileLoader)
	{
		float currTime = (float)GetTickCount();
		float timeDelta = (currTime - lastTime) * 0.001f;

		m_pXFileLoader->Update(timeDelta);

		lastTime = currTime;
	}*/
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112) , 
		1.0F, 0);

	g_pD3DDevice->BeginScene();

	//if (m_pGrid)
	//	m_pGrid->Render();

	//Particle_Render();
	MultiTexture_Render();

	//OBB_Render();

	Text_Render();

	//Frustum_Redner();

	//SphereGroup_Render();
	//PickingObj_Render(); 
	//Mesh_Render();

	//if (m_pCubePC)
	//	m_pCubePC->Render(); 
	//	Obj_Render(); 

	/*if (m_pMap)
		m_pMap->Render();

	if (m_pCubeMan)
		m_pCubeMan->Render(); */

	//Draw_Texture(); 
	/*{
		if (m_pRootFrame)
			m_pRootFrame->Render(); 
	}*/

	//m_pXFileLoader->Display();
	//SkinnedMesh_Render();

	UI_Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	bool IsCursorOnUI = false;
	if (m_pPopUpUI->GetRoot())
		m_pPopUpUI->WndProc(hWnd, message, wParam, lParam, IsCursorOnUI);

	test = m_pPopUpUI->GetRoot();
	if (test->GetUI()->IsCursorOn(hWnd, message, wParam, lParam)) return;

	//if (IsCursorOnUI) return;

	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam); 

	switch (message)
	{
	case WM_LBUTTONDOWN:
		{
			cRay r = cRay::RayAtWorldSpace(LOWORD(lParam), HIWORD(lParam)); 
			for (int i = 0; i < m_vecSphere.size(); i++)
			{
				m_vecSphere[i].isPicked = r.IsPicked(&m_vecSphere[i]); 
			}
		}
		break; 
	case WM_RBUTTONDOWN:
	{
		{
			/*for each(ST_SPHERE* sphere in m_vecCullingSphere)
			{
				if (m_pFrustum->IsIn(sphere))
				{
					sphere->isPicked = true;
				}
				else
				{
					sphere->isPicked = false;
				}
			}*/
		}
		//static int n = 2;

		//animTime = m_pSkinnedMesh->GetAnimTime(n);

		//m_pSkinnedMesh->SetAnimationIndex(++n);

		//m_pSkinnedMesh->SetAnimationIndexBlend(n);
		//animStart = (float)GetTickCount();
	}
		/*{
			cRay r = cRay::RayAtWorldSpace(LOWORD(lParam), HIWORD(lParam));
			for (int i = 0; i < m_vecPlaneVertex.size(); i+= 3)
			{
				D3DXVECTOR3 v(0, 0, 0); 
				if (r.IntersectTri(
					m_vecPlaneVertex[i + 0].p,
					m_vecPlaneVertex[i + 1].p,
					m_vecPlaneVertex[i + 2].p,
					v
				))
				{
					m_vPickedPosition = v; 
				}
			}
		}*/
		break;
	}
}

void cMainGame::Set_Light()
{
	D3DLIGHT9	stLight; 
	ZeroMemory(&stLight, sizeof(D3DLIGHT9)); 
	stLight.Type = D3DLIGHT_DIRECTIONAL; 
	stLight.Ambient = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F); 
	stLight.Diffuse = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);
	stLight.Specular = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);

	D3DXVECTOR3  vDir(1.0f, -1.0f, 1.0f); 
	D3DXVec3Normalize(&vDir, &vDir); 
	stLight.Direction = vDir; 
	g_pD3DDevice->SetLight(0, &stLight); 
	g_pD3DDevice->LightEnable(0, true); 
}

void cMainGame::Setup_Texture()
{
	D3DXCreateTextureFromFile(g_pD3DDevice, _T("../image/수지.png"), &m_pTexture);
	ST_PT_VERTEX v;
	v.p = D3DXVECTOR3(0, 0, 0);
	v.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 2, 0);
	v.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(2, 2, 0);
	v.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(v);


	// : 왼쪽에 뒤집어 출력
	v.p = D3DXVECTOR3(0, 0, 0);
	v.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-2, 2, 0);
	v.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(0, 2, 0);
	v.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(v);
}

void cMainGame::Draw_Texture()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false); 

	D3DXMATRIXA16 matWorld; 
	D3DXMatrixIdentity(&matWorld); 
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld); 
	g_pD3DDevice->SetTexture(0, m_pTexture); 
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF); 
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PT_VERTEX)); 
	g_pD3DDevice->SetTexture(0, NULL); 
}

void cMainGame::Setup_Obj()
{
	cObjLoader l; 
	l.Load(m_vecGroup, "obj", "map.obj"); 

	Load_Surface();
}

void cMainGame::Obj_Render()
{
	D3DXMATRIXA16 matWorld, matS, matR; 
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f); 
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F); 

	matWorld = matS * matR; 
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld); 
	for each(auto p in m_vecGroup)
	{
		p->Render(); 
	}
}

void cMainGame::Load_Surface()
{
	D3DXMATRIXA16 matWorld, matS, matR; 
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);
	matWorld = matS * matR;
	//m_pMap = new cObjMap("obj", "map_surface.obj", &matWorld);
}

void cMainGame::Setup_MultiTexture()
{
	D3DXCreateTextureFromFile(g_pD3DDevice, L"Texture/stones.png", &m_pTex0);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"Texture/env0.png", &m_pTex1);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"Texture/env1.png", &m_pTex2);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"Texture/Albedo00.jpg", &m_pTex3);

	ST_PT_VERTEX v;
	v.p = D3DXVECTOR3(0, 0, 0); v.t = D3DXVECTOR2(0, 1); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(0, 2, 0); v.t = D3DXVECTOR2(0, 0); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(2, 0, 0); v.t = D3DXVECTOR2(1, 1); m_vecVertex_Multi.push_back(v);

	v.p = D3DXVECTOR3(2, 2, 0); v.t = D3DXVECTOR2(1, 0); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(2, 0, 0); v.t = D3DXVECTOR2(1, 1); m_vecVertex_Multi.push_back(v);
	v.p = D3DXVECTOR3(0, 2, 0); v.t = D3DXVECTOR2(0, 0); m_vecVertex_Multi.push_back(v);
}

void cMainGame::Update_MultiTexture()
{
	if (::GetAsyncKeyState('1') & 0x8000) m_nType = 1;
	if (::GetAsyncKeyState('2') & 0x8000) m_nType = 2;
	if (::GetAsyncKeyState('3') & 0x8000) m_nType = 3;
	if (::GetAsyncKeyState('4') & 0x8000) m_nType = 4;
	if (::GetAsyncKeyState('5') & 0x8000) m_nType = 5;
	if (::GetAsyncKeyState('6') & 0x8000) m_nType = 6;
	if (::GetAsyncKeyState('7') & 0x8000) m_nType = 7;
	if (::GetAsyncKeyState('8') & 0x8000) m_nType = 8;
	if (::GetAsyncKeyState('9') & 0x8000) m_nType = 9;
	if (::GetAsyncKeyState('0') & 0x8000) m_nType = 0;
	if (::GetAsyncKeyState('R') & 0x8000) m_nType = -1;
}

void cMainGame::MultiTexture_Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	for (int i = 0; i < 4; ++i)
	{
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);

		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_TEXCOORDINDEX, 0);
	g_pD3DDevice->SetTextureStageState(3, D3DTSS_TEXCOORDINDEX, 0);


	switch (m_nType)
	{
	case 1:		MultiTexture_Render1(); break;
	case 2:		MultiTexture_Render2(); break;
	case 3:		MultiTexture_Render3(); break;
	case 4:		MultiTexture_Render4(); break;
	case 5:		MultiTexture_Render5(); break;
	case 6:		MultiTexture_Render6(); break;
	case 7:		MultiTexture_Render7(); break;
	case 8:		MultiTexture_Render8(); break;
	case 9:		MultiTexture_Render9(); break;
	case 0:		MultiTexture_Render0(); break;
	default:	MultiTexture_Render_default(); break;
	}

	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex_Multi.size() / 3,
		&m_vecVertex_Multi[0],
		sizeof(ST_PT_VERTEX));

	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetTexture(1, NULL);
	g_pD3DDevice->SetTexture(2, NULL);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_RESULTARG, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_RESULTARG, D3DTA_CURRENT);
}

void cMainGame::MultiTexture_Render1()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex1);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);

}

void cMainGame::MultiTexture_Render2()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex1);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE2X);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::MultiTexture_Render3()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex1);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE4X);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::MultiTexture_Render4()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex1);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADD);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::MultiTexture_Render5()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex1);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_SUBTRACT);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::MultiTexture_Render6()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex3);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADDSIGNED);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::MultiTexture_Render7()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex3);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADDSIGNED2X);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::MultiTexture_Render8()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex3);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADDSMOOTH);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::MultiTexture_Render9()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex2);
	g_pD3DDevice->SetTexture(2, m_pTex3);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_RESULTARG, D3DTA_TEMP);

	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG0, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_TEMP);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MULTIPLYADD);

	g_pD3DDevice->SetTextureStageState(3, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::MultiTexture_Render0()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTexture(1, m_pTex2);
	g_pD3DDevice->SetTexture(2, m_pTex3);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_RESULTARG, D3DTA_TEMP);

	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG0, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_TEMP);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_LERP);

	g_pD3DDevice->SetTextureStageState(3, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::MultiTexture_Render_default()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void cMainGame::Setup_MeshObject()
{
	D3DXCreateTeapot(g_pD3DDevice, &m_pMeshTeapot, NULL); 
	D3DXCreateSphere(g_pD3DDevice, 0.5f , 10,10 , &m_pMeshSphere, NULL); 

	ZeroMemory(&m_stMtlTeapot, sizeof(D3DMATERIAL9)); 
	m_stMtlTeapot.Ambient = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f); 
	m_stMtlTeapot.Diffuse = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMtlTeapot.Specular = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);

	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);

	cObjLoader l; 
	m_pObjMesh = l.LoadMesh(m_vecObjMtlTex, "obj", "map.obj"); 
}										

void cMainGame::Mesh_Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTexture(0, NULL); 

	D3DXMATRIXA16 matWorld, matS, matR; 
	{
		D3DXMatrixIdentity(&matS); 
		D3DXMatrixIdentity(&matR);
		matWorld = matS * matR; 
		D3DXMatrixTranslation(&matWorld, 0, 0, 10); 
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(&m_stMtlTeapot); 
		m_pMeshTeapot->DrawSubset(0); 
	}
	{
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		matWorld = matS * matR;
		//D3DXMatrixTranslation(&matWorld, 0, 0, 10);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(&m_stMtlSphere);
		m_pMeshSphere->DrawSubset(0);
	}

	{
		D3DXMatrixIdentity(&matWorld); 
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);

		D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
		D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);
		matWorld = matS * matR;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		for( size_t i = 0 ; i < m_vecObjMtlTex.size() ; ++i)
		{
			g_pD3DDevice->SetMaterial(&m_vecObjMtlTex[i]->GetMaterial()); 
			g_pD3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture()); 
			m_pObjMesh->DrawSubset(i); 
		}
	}
}

void cMainGame::Setup_PickingObj()
{
	for (int i = 0; i <= 10; i++)
	{
		ST_SPHERE s; 
		s.fRadius = 0.5f; 
		s.vCenter = D3DXVECTOR3(0, 0, -10 + 2 * i); 
		m_vecSphere.push_back(s); 
	}

	ZeroMemory(&m_stMtlNone, sizeof(D3DMATERIAL9)); 
	m_stMtlNone.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f); 
	m_stMtlNone.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlNone.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);

	ZeroMemory(&m_stMtlPicked, sizeof(D3DMATERIAL9));
	m_stMtlPicked.Ambient = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);
	m_stMtlPicked.Diffuse = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);
	m_stMtlPicked.Specular = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);

	ZeroMemory(&m_stMtlPlane, sizeof(D3DMATERIAL9));
	m_stMtlPlane.Ambient  = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlPlane.Diffuse  = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlPlane.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	ST_PN_VERTEX v; 
	v.n = D3DXVECTOR3(0, 1, 0); 
	v.p = D3DXVECTOR3(-10, 0, -10); m_vecPlaneVertex.push_back(v); 
	v.p = D3DXVECTOR3(-10, 0,  10); m_vecPlaneVertex.push_back(v);
	v.p = D3DXVECTOR3( 10, 0,  10); m_vecPlaneVertex.push_back(v);
	
	v.p = D3DXVECTOR3(-10, 0, -10); m_vecPlaneVertex.push_back(v);
	v.p = D3DXVECTOR3( 10, 0,  10); m_vecPlaneVertex.push_back(v);
	v.p = D3DXVECTOR3( 10, 0, -10); m_vecPlaneVertex.push_back(v);
}

void cMainGame::PickingObj_Render()
{
	D3DXMATRIXA16 matWorld; 

	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF); 
	g_pD3DDevice->SetMaterial(&m_stMtlPlane); 
	D3DXMatrixIdentity(&matWorld); 

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld); 
	g_pD3DDevice->SetTexture(0, 0); 
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2,
		&m_vecPlaneVertex[0], sizeof(ST_PN_VERTEX)); 

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	for (int i = 0; i < m_vecSphere.size(); i++)
	{
		D3DXMatrixIdentity(&matWorld); 
		matWorld._41 = m_vecSphere[i].vCenter.x; 
		matWorld._42 = m_vecSphere[i].vCenter.y;
		matWorld._43 = m_vecSphere[i].vCenter.z;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld); 
		g_pD3DDevice->SetMaterial(m_vecSphere[i].isPicked ?
			&m_stMtlPicked : &m_stMtlNone); 
		m_pMeshSphere->DrawSubset(0); 
	}

	g_pD3DDevice->SetMaterial(&m_stMtlNone); 
	D3DXMatrixTranslation(&matWorld,
		m_vPickedPosition.x,
		m_vPickedPosition.y,
		m_vPickedPosition.z); 

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld); 
	m_pMeshSphere->DrawSubset(0); 
}

void cMainGame::SkinnedMesh_Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Render(NULL);
}

void cMainGame::Setup_HeightMap()
{
	cHeightMap* pMap = new cHeightMap;
	pMap->Setup("HeightMapData/", "HeightMap.raw", "terrain.jpg");
	m_pMap = pMap;
}

/*void cMainGame::Setup_SphereGroup()
{
	for (int i = 0; i <= 30; i++)
	{
		ST_SPHERE s;
		s.fRadius = 0.5f;
		s.vCenter = D3DXVECTOR3(0, 0, -15 + 1 * i);
		m_vecSphere2.push_back(s);
	}
}

void cMainGame::SphereGroup_Render()
{
	D3DXMATRIXA16 matWorld;
	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);


	D3DXPLANE frustumPlane[6];

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	float x = rc.right / 2.0f;
	float y = rc.bottom / 2.0f;

	D3DXPlaneFromPoints(OUT &frustumPlane[0],
		&D3DXVECTOR3(m_pCamera->GetEye().x, m_pCamera->GetEye().y, 0.0f),
		&D3DXVECTOR3(-x, -y, 1.0f),
		&D3DXVECTOR3(-x, y, 1.0f));
	D3DXPlaneFromPoints(OUT &frustumPlane[1],
		&D3DXVECTOR3(m_pCamera->GetEye().x, m_pCamera->GetEye().y, 0.0f),
		&D3DXVECTOR3(x, y, 1.0f),
		&D3DXVECTOR3(x, -y, 1.0f));


	D3DXVECTOR3 UnProjVC;

	for (int i = 0; i < m_vecSphere2.size(); i++)
	{
		D3DXMatrixIdentity(&matWorld);
		matWorld._41 = m_vecSphere2[i].vCenter.x;
		matWorld._42 = m_vecSphere2[i].vCenter.y;
		matWorld._43 = m_vecSphere2[i].vCenter.z;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		//m_pMeshSphere->DrawSubset(0);

		D3DXVec3Unproject(OUT &UnProjVC, IN &m_vecSphere2[i].vCenter, NULL,
			&m_pCamera->GetMatProj(), &m_pCamera->GetMatView(), NULL);
		if (D3DXPlaneDotCoord(&frustumPlane[0], &UnProjVC) < 0 &&
			D3DXPlaneDotCoord(&frustumPlane[1], &UnProjVC) < 0)
		{
			m_pMeshSphere->DrawSubset(0);
		}
	}
}

void cMainGame::FrustumCulling()
{
	D3DXPLANE frustumPlane;

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	float x = rc.right / 2.0f;
	float y = rc.bottom / 2.0f;

	D3DXPlaneFromPoints(OUT &frustumPlane,
		&D3DXVECTOR3(m_pCamera->GetEye().x, m_pCamera->GetEye().y, 0.0f),
		&D3DXVECTOR3(-x, y, 1000.0f),
		&D3DXVECTOR3(-x, -y, 1000.0f));


	D3DXVECTOR3 UnProjVC;
	for (unsigned int i = 0; i < m_vecSphere2.size(); i++)
	{
		D3DXVec3Unproject(OUT &UnProjVC, IN &m_vecSphere2[i].vCenter, NULL,
			&m_pCamera->GetMatProj(), &m_pCamera->GetMatView(), NULL);

	}
}*/

void cMainGame::Setup_Frustum()
{
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pSphere, NULL);

	for (int i = -20; i <= 20; ++i)
	{
		for (int j = -20; j <= 20; ++j)
		{
			for (int k = -20; k <= 20; ++k)
			{
				ST_SPHERE* s = new ST_SPHERE;
				s->fRadius = 0.5;
				s->vCenter = D3DXVECTOR3((float)i, (float)j, (float)k);
				s->isPicked = true;
				m_vecCullingSphere.push_back(s);
			}
		}
	}

	ZeroMemory(&m_stCullingMtl, sizeof(D3DMATERIAL9));
	m_stCullingMtl.Ambient =  D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stCullingMtl.Diffuse =  D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stCullingMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	m_pFrustum = new cFrustum;
	m_pFrustum->Setup();
}

void cMainGame::Frustum_Redner()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	for each(ST_SPHERE* sphere in m_vecCullingSphere)
	{
		if (sphere->isPicked)
		{
			D3DXMatrixIdentity(&matWorld);
			matWorld._41 = sphere->vCenter.x;
			matWorld._42 = sphere->vCenter.y;
			matWorld._43 = sphere->vCenter.z;
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
			g_pD3DDevice->SetMaterial(&m_stCullingMtl);
			m_pSphere->DrawSubset(0);
		}
	}
}

void cMainGame::Setup_OBB()
{
	m_pHoldZealot = new cZealot;
	m_pHoldZealot->Setup();

	m_pMoveZealot = new cZealot;
	m_pMoveZealot->Setup();

	cCharacter* pCharacter = new cCharacter;
	m_pMoveZealot->SetCharacterController(pCharacter);
	SafeRelease(pCharacter);
}

void cMainGame::OBB_Render()
{
	D3DCOLOR c = cOBB::IsCollision(
		m_pHoldZealot->GetOBB(), m_pMoveZealot->GetOBB()) ?
		D3DCOLOR_XRGB(255, 0, 0) : D3DCOLOR_XRGB(255, 255, 255);
	if (m_pHoldZealot)
		m_pHoldZealot->Render(c);
	if (m_pMoveZealot)
		m_pMoveZealot->Render(c);
}

void cMainGame::Create_Font()
{
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 50;
	fd.Width = 25;
	fd.Weight = FW_MEDIUM;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;

	//wcscpy_s(fd.FaceName, L"굴림체");
	AddFontResource(L"font/umberto.ttf");
	wcscpy_s(fd.FaceName, L"umberto");

	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);


	// >> :
	HDC hdc = CreateCompatibleDC(0);
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 25;
	lf.lfWidth = 12;
	lf.lfWeight = 500;
	lf.lfItalic = false;
	lf.lfUnderline = false;
	lf.lfStrikeOut = false;
	lf.lfCharSet = DEFAULT_CHARSET;
	//wcscpy_s(lf.lfFaceName, L"굴림체");
	wcscpy_s(lf.lfFaceName, L"umberto");

	HFONT hFont;
	HFONT hFontOld;

	hFont = CreateFontIndirect(&lf);
	hFontOld = (HFONT)SelectObject(hdc, hFont);
	D3DXCreateText(g_pD3DDevice, hdc,
		L"Direct3D 가나다라",
		0.001f,
		0.01f,
		&m_p3DText,
		0, 0);

	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
	DeleteDC(hdc);
	// << :
}

void cMainGame::Text_Render()
{
	/*string sText("ABC 123 !@#$ 가나다라");
	RECT rc;
	SetRect(&rc, 100, 100, 201, 101);

	LPD3DXFONT pFont = g_pFontManager->GetFont(cFontManager::E_QUEST);


	pFont->DrawTextA(NULL,
		sText.c_str(),
		sText.length(),
		&rc,
		DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 0));

	// >> :
	D3DXMATRIXA16	matWorld, matS, matR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 5.0f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 4.0f);
	D3DXMatrixTranslation(&matT, -2.0f, 1.0f, 0.0f);
	matWorld = matS * matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	m_p3DText->DrawSubset(0);
	// << :
	*/
}

void cMainGame::Setup_UI()
{
	//m_pPopUp = new PopUp;
	//m_pPopUp->SetUp("UI", "panel-info.png");
	m_pPopUpUI = new PopUpUI;
	m_pPopUpUI->SetUp();
}

void cMainGame::UI_Update()
{
	if (m_pPopUpUI)
		m_pPopUpUI->Update();
}

void cMainGame::UI_Render()
{
	//m_pPopUp->Render();
	if(m_pPopUpUI)
		m_pPopUpUI->Render();
}

void cMainGame::Setup_Particle()
{
	m_vecVertexParticle.resize(1000);
	for (int i = 0; i < m_vecVertexParticle.size(); ++i)
	{
		float fRadius = rand() % 100 / 10.0f;

		m_vecVertexParticle[i].p = D3DXVECTOR3(0, 0, fRadius);
		D3DXVECTOR3 vAngle = D3DXVECTOR3(
			D3DXToRadian(rand() % 3600 / 1.0f),
			D3DXToRadian(rand() % 3600 / 1.0f),
			D3DXToRadian(rand() % 3600 / 1.0f)
		);

		D3DXMATRIXA16 matRx, matRy, matRz, matWorld;
		D3DXMatrixRotationX(&matRx, vAngle.x);
		D3DXMatrixRotationY(&matRy, vAngle.y);
		D3DXMatrixRotationZ(&matRz, vAngle.z);
		matWorld = matRx * matRy * matRz;

		D3DXVec3TransformCoord(
			&m_vecVertexParticle[i].p,
			&m_vecVertexParticle[i].p,
			&matWorld
		);

		m_vecVertexParticle[i].c = D3DCOLOR_ARGB(255, 180, 70, 20);
	}
}

void cMainGame::Update_Particle()
{
	static int nAlpha = 0;
	static int nDelta = 4;
	nAlpha += nDelta;

	if (nAlpha > 255)
	{
		nAlpha = 255;
		nDelta *= -1;
	}
	if (nAlpha < 0)
	{
		nAlpha = 0;
		nDelta *= -1;
	}

	for (int i = 0; i < m_vecVertexParticle.size(); ++i)
	{
		if (i % 2) continue;
		m_vecVertexParticle[i].c = D3DCOLOR_ARGB(nAlpha,
			180, 70, 20);
	}
}

void cMainGame::Particle_Render()
{
	D3DXMATRIXA16	matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(5.0f));

	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(10.0f));

	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MAX, FtoDw(100.0f));

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);

	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0,
		g_pTextureManager->GetTexture("image/alpha_tex.tga"));
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST,
		m_vecVertexParticle.size(),
		&m_vecVertexParticle[0],
		sizeof(ST_PC_VERTEX));

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}
