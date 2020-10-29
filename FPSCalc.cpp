#include "stdafx.h"
#include "FPSCalc.h"
#include <ctime>


FPSCalc::FPSCalc()
	: curTime(0.0f)
	, lastTime(0.0f)
	, FrameCnt(0)
	, TimeElapsed(0.0f)
	, FPS(0.0f)
{
}


FPSCalc::~FPSCalc()
{
}

void FPSCalc::CalCurTime()
{
	/*curTime = (float)GetTickCount();
	float timeDelta = (curTime - lastTime) * 0.001f;
	lastTime = curTime;*/
}

void FPSCalc::CalFPS()
{
	curTime = (float)GetTickCount();
	float timeDelta = (curTime - lastTime) * 0.001f;
	lastTime = curTime;

	FrameCnt++;
	TimeElapsed += timeDelta;
	this->FontFPS();
	if (TimeElapsed > 1.0f)
	{
		FPS = (float) FrameCnt / TimeElapsed;

		FrameCnt = 0;
		TimeElapsed = 0.0f;
	}
}

void FPSCalc::FontFPS()
{
	//폰트 생성
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 45;
	fd.Width = 28;
	fd.Weight = FW_MEDIUM;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	//strcpy_s(fd.FaceName, "궁서체");   //글꼴 스타일
	AddFontResource(L"umberto.ttf");
	strcpy((char*)fd.FaceName, "umberto");

	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);

	if (m_pFont)
	{
		RECT rc;
		SetRect(&rc, 60, 40, 80, 80);
		char szTemp[1024];
		sprintf(szTemp, "FPS %.2f", FPS);
		m_pFont->DrawTextA(nullptr,
			szTemp,
			strlen(szTemp),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 0, 0));
	}
}
