#pragma once
#include "UISprite.h"

class PopUpUI;
class Button_B :
	public UISprite
{
	LPD3DXSPRITE		m_pSprite2;
	D3DXIMAGE_INFO		m_stImageInfo2;
	LPDIRECT3DTEXTURE9	m_pTextureUI2;

	PopUpUI* m_pPopUpBody;
	bool* m_PopUpActive;

	vector<D3DXIMAGE_INFO>		m_vecStImageInfo;
	vector<LPDIRECT3DTEXTURE9>	m_vecTextureUI;
public:
	Button_B();
	~Button_B();

	void SetUp2(char* szFolder, char* szFile);
	void SetPopUpActive(bool*);
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool&) override;
};

