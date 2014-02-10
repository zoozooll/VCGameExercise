#include "WinMain.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE prevhInst, LPSTR cmdLine, int show)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MsgProc;
	wc.hInstance = hInst;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = WINDOW_CLASS;

	RegisterClassEx(&wc);
	HWND hWnd = CreateWindow(WINDOW_CLASS, WINDOW_NAME, WS_OVERLAPPEDWINDOW,
		100, 100, WINDOW_WIDTH, WINDOW_HEIGHT,
		GetDesktopWindow(), NULL, wc.hInstance, NULL);
	if (InitializeD3D(hWnd, false))
	{
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		
		// use peekmessage for loop
		while(msg.message != WM_QUIT)
		{
			if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else 
			{
				// run game code here
				RenderScene();
			}
		}
		/*
		// use the get message for loop
		while (GetMessage(&msg, NULL, 0 ,0 ))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}*/
		Shutdown();
		UnregisterClass(WINDOW_CLASS, wc.hInstance);
		
	}
	return 0;
}

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)  
{  
	switch(msg)  
	{  
	case WM_DESTROY:  
		PostQuitMessage(0);  
		return 0;  
		break;  
	case WM_KEYUP:  
		if(wParam == VK_ESCAPE) PostQuitMessage(0);  
		break;  
	}  
	return DefWindowProc(hWnd, msg, wParam, lParam);  
} 



