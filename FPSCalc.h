#pragma once
class FPSCalc
{
	float curTime;
	float lastTime;
	DWORD FrameCnt;
	float TimeElapsed;
	float FPS;

	LPD3DXFONT m_pFont;
public:
	FPSCalc();
	~FPSCalc();

	void CalCurTime();
	void CalFPS();
	void FontFPS();
};

