#include "stdafx.h"
#include "UISprite.h"


UISprite::UISprite()
	: m_pSprite(NULL)
	, m_pTextureUI(NULL)
	, m_pTextureUIRender(NULL)
	, m_Pos({ 0, 0 })
	, m_PosDelta({ 0, 0 })
{
}


UISprite::~UISprite()
{
	SafeRelease(m_pSprite);
	SafeRelease(m_pTextureUI);
	SafeRelease(m_pTextureUIRender);
}

void UISprite::SetUp(char* szFolder, char* szFile)
{
	string sFullPath(szFolder);
	sFullPath = sFullPath + string("/") + string(szFile);

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	D3DXCreateTextureFromFileExA(
		g_pD3DDevice,
		//L"UI/panel-info.png",
		sFullPath.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stImageInfo,
		NULL,
		&m_pTextureUI);

	m_pTextureUIRender = m_pTextureUI;

	//m_Pos.x = 500;
	//m_Pos.y = 80;
}

void UISprite::Update()
{
	D3DXMATRIXA16 matT, matS, matR;
	D3DXMatrixTranslation(&matT, m_Pos.x + m_PosDelta.x, m_Pos.y + m_PosDelta.y, 0);
	m_matLocalTM = matT;

	m_matWorldTM = m_matLocalTM;
	if (m_pParentWorldTM)
	{
		m_matWorldTM *= *m_pParentWorldTM;
	}

	for each(auto p in m_vecChild)
	{
		p->Update();
	}
}

void UISprite::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	RECT rc;
	SetRect(&rc, 0, 0,
		m_stImageInfo.Width, m_stImageInfo.Height);

	/*D3DXMATRIXA16 matT, matS, matR;
	D3DXMatrixTranslation(&matT, m_Pos.x, m_Pos.y, 0);
	m_matLocalTM = matT;*/

	m_pSprite->SetTransform(&m_matWorldTM);

	m_pSprite->Draw(m_pTextureUIRender,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();

	for each(auto p in m_vecChild)
	{
		p->Render();
	}
}

void UISprite::AddChild(UISprite * pChild)
{
	pChild->m_pParentWorldTM = &m_matWorldTM;
	m_vecChild.push_back(pChild);
}

void UISprite::Destroy()
{
	for each(auto p  in m_vecChild)
	{
		p->Destroy();
	}
	delete this;
}

bool UISprite::IsCursorOn(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	POINT cursor;
	//GetCursorPos(&cursor);
	//ScreenToClient(hWnd, &cursor);
	cursor.x = LOWORD(lParam);
	cursor.y = HIWORD(lParam);

	if (m_stImageInfo.Height != 512)
		int test = 0;

	if (cursor.x > m_matWorldTM._41 &&
		cursor.y > m_matWorldTM._42 &&
		cursor.x < m_matWorldTM._41 + m_stImageInfo.Width &&
		cursor.y < m_matWorldTM._42 + m_stImageInfo.Height)
	{
		//if (m_stImageInfo.Height != 512)
		//	int test = 0;
		return true;
	}

	return false;
}

void UISprite::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool& IsCursor)
{
	/*if (m_vecChild.size())
		this->WndProc(hWnd, message, wParam, lParam);

	for each(auto p in m_vecChild)
	{
		p->WndProc(hWnd, message, wParam, lParam);
	}*/
}
