#pragma once

class CCore
{
	SINGLETON(CCore);
private:
	HWND m_hWnd;			// ���� ������ �ڵ�
	POINT m_ptResolution;	// ���� ������ �ػ�
	HDC	m_hDC;				// ���� ������ Draw �� Device Context


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

