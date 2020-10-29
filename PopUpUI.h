#pragma once

class UISprite;
class PopUpUI
{
	//Synthesize(UISprite*, m_pRoot, Root);
	UISprite*			m_pRoot;
	D3DXMATRIXA16		m_matWorld;
public:
	PopUpUI();
	~PopUpUI();

	void SetUp();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool&);
	UISprite* GetRoot() { return m_pRoot; }
};

