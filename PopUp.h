#pragma once
#include "UISprite.h"

class PopUp:
	public UISprite
{
private:
	/*LPD3DXSPRITE		m_pSprite;
	D3DXIMAGE_INFO		m_stImageInfo;
	LPDIRECT3DTEXTURE9	m_pTextureUI;

	POINT				m_Pos;*/
public:
	PopUp();
	~PopUp();

	/*void SetUp();
	void Update();
	void Render();

	bool& IsCursorOn();*/
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool&) override;
};