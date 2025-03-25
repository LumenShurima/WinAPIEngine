#pragma once

class CCore
{
	SINGLETON(CCore);
private:
	HWND m_hWnd;			// 메인 윈도우 핸들
	POINT m_ptResolution;	// 메인 윈도우 해상도
	HDC	m_hDC;				// 메인 윈도우 Draw 할 Device Context


	HBITMAP m_hBit;
	HDC m_memDC;
public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void update();
	void render();

public:
	HWND getMainHwnd() { return m_hWnd; }
	POINT GetResolution() { return m_ptResolution; }

};

