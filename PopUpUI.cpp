#include "stdafx.h"
#include "PopUpUI.h"

#include "UISprite.h"
#include "PopUp.h"
#include "Button_A.h"
#include "Button_B.h"

PopUpUI::PopUpUI()
	: m_pRoot(NULL)
{
}


PopUpUI::~PopUpUI()
{
	if (m_pRoot)
		m_pRoot->Destroy();
}

void PopUpUI::SetUp()
{
	D3DXMatrixIdentity(&m_matWorld);

	PopUp* pPopUp = new PopUp;
	pPopUp->SetUp("UI", "panel-info.png");
	pPopUp->SetParentWorldTM(&m_matWorld);
	m_pRoot = pPopUp;

	Button_A* pButton_A1 = new Button_A;
	pButton_A1->SetUp("UI", "btn-med-over.png");
	pButton_A1->SetUp2("UI", "btn-med-down.png");
	pButton_A1->SetUp2("UI", "btn-med-up.png");
	pButton_A1->SetParentWorldTM(&m_matWorld);
	pButton_A1->SetPosDelta({ 130, 300 });
	m_pRoot->AddChild(pButton_A1);

	Button_A* pButton_A2 = new Button_A;
	pButton_A2->SetUp("UI", "btn-med-over.png");
	pButton_A2->SetUp2("UI", "btn-med-down.png");
	pButton_A2->SetUp2("UI", "btn-med-up.png");
	pButton_A2->SetParentWorldTM(&m_matWorld);
	pButton_A2->SetPosDelta({ 130, 380 });
	m_pRoot->AddChild(pButton_A2);

	Button_B* pButton_B1 = new Button_B;
	pButton_B1->SetUp("UI", "btn-rewind.png");
	pButton_B1->SetUp2("UI", "btn-main-menu.png");
	pButton_B1->SetParentWorldTM(&m_matWorld);
	pButton_B1->SetPosDelta({ 390, 80 });
	m_pRoot->AddChild(pButton_B1);
}

void PopUpUI::Update()
{
	if (m_pRoot)
		m_pRoot->Update();
}

void PopUpUI::Render()
{
	if (m_pRoot)
		m_pRoot->Render();
}

void PopUpUI::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool& IsCursor)
{
	m_pRoot->WndProc(hWnd, message, wParam, lParam, IsCursor);

}
