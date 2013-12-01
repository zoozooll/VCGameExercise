#include "stdafx.h"

HINSTANCE m_hInst;
HBITMAP m_hbmp;
HDC m_hdc;

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void MyPaint(HDC);