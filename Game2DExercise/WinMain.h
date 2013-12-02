#include "stdafx.h"
#include <stdio.h>

HINSTANCE m_hInst;
HBITMAP m_hbmp;
HBITMAP m_Girls[7];
HDC m_hdc, m_CacheHDC;
int m_GirlIndex, frame, fps;
HWND hWnd;
DWORD tPre, tNow, tCheck;

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void MyPaint(HDC);