#include "stdafx.h"
#include "PopUp.h"


PopUp::PopUp()
	/*: m_pSprite(NULL)
	, m_pTextureUI(NULL)
	, m_Pos({ 0, 0 })*/
{
}


PopUp::~PopUp()
{
	/*SafeRelease(m_pSprite);
	SafeRelease(m_pTextureUI);*/
}

void PopUp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool& IsCursor)
{
	if (this->IsCursorOn(hWnd, message, wParam, lParam)) IsCursor = true;

	if (!this->IsCursorOn(hWnd, message, wParam, lParam)) return;

	static POINT tmpPos, tmpPos2;
	static LONG tmpX, tmpY;
	static bool downFlag = false;

	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		downFlag = true;

		tmpPos.x = LOWORD(lParam);
		tmpPos.y = HIWORD(lParam);
		//GetCursorPos(&tmpPos);
		//ScreenToClient(hWnd, &tmpPos);
		tmpX = tmpPos.x - m_Pos.x;
		tmpY = tmpPos.y - m_Pos.y;
	}
	break;
	case WM_LBUTTONUP:
	{
		downFlag = false;

		tmpPos.x = tmpPos2.x = 0;// = m_Pos.x;
		tmpPos.y = tmpPos2.y = 0;// = m_Pos.y;
		tmpX = tmpY = 0;
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (downFlag)
		{
			tmpPos2.x = LOWORD(lParam);
			tmpPos2.y = HIWORD(lParam);
			m_Pos.x += (tmpPos2.x - tmpPos.x);// +tmpX;
			m_Pos.y += (tmpPos2.y - tmpPos.y);// +tmpY;

			tmpPos.x = tmpPos2.x;
			tmpPos.y = tmpPos2.y;
		}
	}
	break;
	}


	for each(auto p in m_vecChild)
	{
		p->WndProc(hWnd, message, wParam, lParam, IsCursor);
	}
}

/*void PopUp::SetUp()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	//m_pTextureUI = g_pTextureManager->GetTexture("UI/±èÅÂÈñ.jpg");
	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		L"UI/panel-info.png",
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

	m_Pos.x = 0;
	m_Pos.y = 0;
}

void PopUp::Update()
{
}

void PopUp::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	RECT rc;
	SetRect(&rc, 0, 0,
		m_stImageInfo.Width, m_stImageInfo.Height);

	D3DXMATRIXA16 matT, matS, matR, mat;
	D3DXMatrixTranslation(&matT, m_Pos.x, m_Pos.y, 0);
	mat = matT;

	m_pSprite->SetTransform(&mat);

	m_pSprite->Draw(m_pTextureUI,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();
}

bool PopUp::IsCursorOn()
{
	POINT cursor;
	GetCursorPos(&cursor);

	if (cursor.x >= m_Pos.x && cursor.y >= m_Pos.y &&
		cursor.x < m_Pos.x + m_stImageInfo.Width &&
		cursor.y < m_Pos.y + m_stImageInfo.Height)
		return true;

	return false;
}*/