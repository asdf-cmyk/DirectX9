#pragma once
#include "UISprite.h"
class Button_B :
	public UISprite
{
	LPD3DXSPRITE		m_pSprite2;
	D3DXIMAGE_INFO		m_stImageInfo2;
	LPDIRECT3DTEXTURE9	m_pTextureUI2;

	vector<D3DXIMAGE_INFO>		m_vecStImageInfo;
	vector<LPDIRECT3DTEXTURE9>	m_vecTextureUI;
public:
	Button_B();
	~Button_B();

	void SetUp2(char* szFolder, char* szFile);
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool&) override;
};

