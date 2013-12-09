#include "stdafx.h"
#include <stdio.h>

HINSTANCE m_hInst;
HBITMAP m_bmpGirls[4], m_bmgBg, m_bmpbird;
HDC m_hdc, m_CacheHDC, m_hdcBuf;
int m_GirlIndex, frame, fps, dir, x, y;
HWND hWnd;
DWORD tPre, tNow, tCheck, nowX, nowY;

POINT m_p[3];

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void MyPaint(HDC);