#include "WinMain.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

ATOM MyRegisterClass (HINSTANCE hInstance)
{
	WNDCLASSEX wClassEx;
	wClassEx.cbSize = sizeof(WNDCLASSEX);
	wClassEx.style = CS_HREDRAW | CS_VREDRAW;
	wClassEx.lpfnWndProc = (WNDPROC)WndProc;
	wClassEx.cbClsExtra = 0;
	wClassEx.cbWndExtra = 0;
	wClassEx.hInstance = hInstance;
	wClassEx.hIcon = NULL;
	wClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClassEx.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wClassEx.lpszMenuName = NULL;
	wClassEx.lpszClassName = "Game2DExercise";
	wClassEx.hIconSm = NULL;
	return RegisterClassEx(&wClassEx);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	HDC hdc;
	m_hInst = hInstance;
	hWnd = CreateWindow("Game2DExercise", "»æÖÆ´°¿Ú", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		return FALSE;
	}
	MoveWindow(hWnd, 10, 10, 800, 600, true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	hdc = GetDC(hWnd);
	m_hdc = CreateCompatibleDC(hdc);
	m_hbmp = (HBITMAP)LoadImage(NULL, "bg.bmp", IMAGE_BITMAP, 800, 600, LR_LOADFROMFILE);
	SelectObject(m_hdc, m_hbmp);
	MyPaint(hdc);
	ReleaseDC(hWnd, hdc);
	return TRUE;
}

void MyPaint(HDC hdc)
{
	BitBlt(hdc, 0, 0, 800, 600, m_hdc, 0, 0, SRCCOPY);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch(message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd,&ps);
		MyPaint(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteDC(m_hdc);
		DeleteObject(m_hbmp);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam,lParam);
	}
	return 0;
}