#include "stdafx.h"
#include "Button_B.h"


Button_B::Button_B()
	: m_pSprite2(NULL)
	, m_pTextureUI2(NULL)
{
}


Button_B::~Button_B()
{
	SafeRelease(m_pSprite2);
	SafeRelease(m_pTextureUI2);

	for each(auto p  in m_vecTextureUI)
		SafeRelease(p);
}

void Button_B::SetUp2(char* szFolder, char* szFile)
{
	string sFullPath(szFolder);
	sFullPath = sFullPath + string("/") + string(szFile);

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite2);

	D3DXCreateTextureFromFileExA(
		g_pD3DDevice,
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
		&m_stImageInfo2,
		NULL,
		&m_pTextureUI2);

	m_vecTextureUI.push_back(m_pTextureUI2);
	m_vecStImageInfo.push_back(m_stImageInfo2);
}

void Button_B::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool&)
{
	if (this->IsCursorOn(hWnd, message, wParam, lParam))
	{
		switch (message)
		{
		case WM_LBUTTONDOWN:
			if (m_vecTextureUI.size())
				m_pTextureUIRender = m_vecTextureUI[0];
			break;
		}
	}
	else
		m_pTextureUIRender = m_pTextureUI;
}
