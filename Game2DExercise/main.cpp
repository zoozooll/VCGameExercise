#include "WinMain.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	GetMessage(&msg, NULL, 0, 0);
	while (msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			tNow = GetTickCount();
			if (tNow - tPre >= 100)
				MyPaint(m_hdc);
		}
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
	m_hInst = hInstance;
	hWnd = CreateWindow("Game2DExercise", "绘制窗口", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		return FALSE;
	}
	MoveWindow(hWnd, 10, 10, 800, 600, true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	m_CacheHDC = GetDC(hWnd);
	m_hdc = CreateCompatibleDC(m_CacheHDC);
	m_hbmp = (HBITMAP)LoadImage(NULL, "bg.bmp", IMAGE_BITMAP, 800, 600, LR_LOADFROMFILE);
	// 载入各个人物的位图
	char filename[20];
	for (int i = 0; i < 7; i++)
	{
		sprintf(filename, "girl%d.bmp", i);
		m_Girls[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 640, 480, LR_LOADFROMFILE);
	}
	
	m_GirlIndex = 0;
	//SetTimer(hWnd, 1, 500, NULL);
	//载入位图完毕
	SelectObject(m_hdc, m_hbmp);
	MyPaint(m_CacheHDC);
	//ReleaseDC(hWnd, hdc);
	return TRUE;
}

void MyPaint(HDC hdc)
{
	//show the fps
	char str[50];
	if (tNow - tCheck >= 1000)
	{
		fps = frame;
		frame = 0;
		tCheck = tNow;
	}
	sprintf(str, "fps:%d", fps);
	TextOut(m_hdc, 0, 0, str, strlen(str));
	BitBlt(hdc, 0, 0, 800, 600, m_hdc, 0, 0, SRCCOPY);
	//draw the amimating girl images;
	m_GirlIndex = m_GirlIndex % 7;
	
	SelectObject(m_hdc, m_Girls[m_GirlIndex]);
	
	BitBlt(m_CacheHDC, 0, 0, 600, 450, m_hdc, 0, 0, SRCCOPY);
	m_GirlIndex ++;
	// draw the girl images end;
	frame++;
	tPre = GetTickCount();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch(message)
	{
	case WM_TIMER:
		// receive message of timer
		//MyPaint(m_CacheHDC);
		break;
	//case WM_PAINT:
	//	hdc = BeginPaint(hWnd,&ps);
	//	MyPaint(hdc);
	//	EndPaint(hWnd, &ps);
	//	break;
	case WM_DESTROY:
		DeleteDC(m_hdc);
		DeleteObject(m_hbmp);
		ReleaseDC(hWnd, m_CacheHDC);
		for (int i = 0; i < 7; i++)
		{
			DeleteObject(m_Girls[i]);
		}
		PostQuitMessage(0);
		KillTimer(hWnd, 1);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam,lParam);
	}
	return 0;
}