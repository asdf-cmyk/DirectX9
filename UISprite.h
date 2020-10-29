#pragma once
class UISprite
{
protected:
	LPD3DXSPRITE		m_pSprite;
	D3DXIMAGE_INFO		m_stImageInfo;
	LPDIRECT3DTEXTURE9	m_pTextureUI;
	LPDIRECT3DTEXTURE9	m_pTextureUIRender;

	POINT				m_Pos;
	D3DXMATRIXA16		m_matLocalTM;
	D3DXMATRIXA16		m_matWorldTM;

	std::vector<UISprite*>		m_vecChild;

	Synthesize(D3DXMATRIXA16*, m_pParentWorldTM, ParentWorldTM);
	Synthesize(POINT, m_PosDelta, PosDelta);
public:
	UISprite();
	~UISprite();

	void SetUp(char* szFolder, char* szFile);
	void Update();
	void Render();

	virtual void AddChild(UISprite* pChild);
	virtual void Destroy();

	bool IsCursorOn(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool&);

	virtual UISprite* GetUI() { return this; }
};