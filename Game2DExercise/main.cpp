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
	HBITMAP bmp;
	m_hInst = hInstance;
	hWnd = CreateWindow("Game2DExercise", "��Ϸ����", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		return FALSE;

	}
	MoveWindow(hWnd, 10, 10, 640, 480, true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	m_hdc =GetDC(hWnd);
	m_CacheHDC = CreateCompatibleDC(m_hdc);
	m_hdcBuf = CreateCompatibleDC(m_hdc);
	
	bmp = CreateCompatibleBitmap(m_hdc, 640, 480);	
	SelectObject(m_CacheHDC, bmp);
	x = 300;
	y = 250;
	dir = 0;
	m_GirlIndex = 0;
	nowX = 300;
	nowY = 300;

	//����������ƶ�λͼ������ͼ  
	m_bmpGirls[0] = (HBITMAP)LoadImage(NULL,"girl0.bmp",IMAGE_BITMAP,440,148,LR_LOADFROMFILE);  
	m_bmpGirls[1] = (HBITMAP)LoadImage(NULL,"girl1.bmp",IMAGE_BITMAP,424,154,LR_LOADFROMFILE);  
	m_bmpGirls[2] = (HBITMAP)LoadImage(NULL,"girl2.bmp",IMAGE_BITMAP,480,148,LR_LOADFROMFILE);  
	m_bmpGirls[3] = (HBITMAP)LoadImage(NULL,"girl3.bmp",IMAGE_BITMAP,480,148,LR_LOADFROMFILE); 

	m_bmgBg = (HBITMAP)LoadImage(NULL, "bg.bmp", IMAGE_BITMAP, 640, 480, LR_LOADFROMFILE);
	m_bmpbird = (HBITMAP)LoadImage(NULL, "bird.bmp", IMAGE_BITMAP, 122, 122, LR_LOADFROMFILE);
	m_p[0].x = 30;
	m_p[0].y = 100;
	m_p[1].x = 250;
	m_p[1].y = 250;
	m_p[2].x = 500;
	m_p[2].y = 400;

	MyPaint(m_hdc);
	return TRUE;
}

void MyPaint(HDC hdc)
{
	int w, h, i;
	SelectObject(m_hdcBuf, m_bmgBg);
	BitBlt(m_CacheHDC, 0, 0, 640, 480, m_hdcBuf, 0, 0, SRCCOPY);

	SelectObject(m_hdcBuf, m_bmpGirls[dir]);
	switch(dir)
	{
	case 0:
		w = 55;
		h = 74;
		break;
	case 1:
		w = 53;
		h = 77;
		break;
	case 2:
		w = 60;
		h = 74;
		break;
	case 3:
		w = 60;
		h = 74;
		break;
	}

	BitBlt(m_CacheHDC, x, y, w, h, m_hdcBuf, m_GirlIndex * w, h, SRCAND);
	BitBlt(m_CacheHDC, x, y, w, h, m_hdcBuf, m_GirlIndex * w, 0, SRCPAINT);
	

	SelectObject(m_hdcBuf, m_bmpbird);
	for(i = 0; i < 3; i++)
	{
			if (m_p[i].y > (y - 16))
			{
				m_p[i].y -= 5;
			}
			else
			{
				m_p[i].y += 5;
			}
			if (m_p[i].x > (x - 25))
			{
				m_p[i].x -= 5;
			}
			else 
			{
				m_p[i].x += 5;
					 
			}
		if (m_p[i].x > (x -25))
		{
			BitBlt(m_CacheHDC, m_p[i].x, m_p[i].y, 61, 61, m_hdcBuf, 61, 61, SRCAND);
			BitBlt(m_CacheHDC, m_p[i].x, m_p[i].y, 61, 61, m_hdcBuf, 0, 61, SRCPAINT);
		}
		else
		{
			BitBlt(m_CacheHDC, m_p[i].x, m_p[i].y, 61, 61, m_hdcBuf, 61, 0, SRCAND);
			BitBlt(m_CacheHDC, m_p[i].x, m_p[i].y, 61, 61, m_hdcBuf, 0, 0, SRCPAINT);
		}
	}

	BitBlt(m_hdc, 0, 0, 640, 480, m_CacheHDC, 0, 0, SRCCOPY);
	tPre = GetTickCount();
	frame ++;
	frame = m_GirlIndex % 8;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)  
	 {  
		 case WM_KEYDOWN:         //���¼�����Ϣ  
			 //�жϰ������������  
			 switch (wParam)   
			 {  
				 case VK_ESCAPE:           //���¡�Esc����  
					 PostQuitMessage( 0 );  //��������  
					 break;  
				 case VK_UP:               //���¡�������  
					 //�Ȱ���Ŀǰ���ƶ�������������ͼ�������������������������ƶ�������ÿ�ΰ���һ�ΰ����ƶ�10����λ����������������ͼ�����X��Yֵ�������ж������Ƿ񳬳����������������ٴ�����  
					 switch(dir)  
					 {  
						 case 0:   
							 y -= 10;  
							 break;  
						 case 1:  
							 x -= 1;  
							 y -= 8;  
							 break;  
						 case 2:   
							 x += 2;  
							 y -= 10;  
							 break;  
						 case 3:  
							 x += 2;  
							 y -= 10;  
							 break;  
					 }  
					 if(y < 0)  
						 y = 0;  
					 dir = 0;  
					 break;  
				 case VK_DOWN:             //���¡�������  
					 switch(dir)  
					 {  
						 case 0:  
							 x += 1;  
							 y += 8;  
							 break;  
						 case 1:  
							 y += 10;  
							 break;  
						 case 2:  
							 x += 3;  
							 y += 6;  
							 break;  
						 case 3:  
							 x += 3;  
							 y += 6;  
							 break;  
					 }  

					 if(y > 375)  
						 y = 375;  
					 dir = 1;  
					 break;  
				 case VK_LEFT:             //���¡�������  
					 switch(dir)  
					 {  
						 case 0:  
							 x -= 12;  
							 break;  
						 case 1:  
							 x -= 13;  
							 y += 4;  
							 break;  
						 case 2:  
							 x -= 10;  
							 break;  
						 case 3:  
							 x -= 10;  
							 break;  
					 }  
					 if(x < 0)  
						 x = 0;  
					 dir = 2;  
					 break;  
				 case VK_RIGHT:             //���¡�������  
					 switch(dir)  
					 {  
						 case 0:  
							 x += 8;  
							 break;  
						 case 1:  
							 x += 7;  
							 y += 4;  
							 break;  
						 case 2:  
							 x += 10;  
							 break;  
						 case 3:  
							 x += 10;  
							 break;  
					 }  
					 if(x > 575)  
						 x = 575;  
					 dir = 3;  
					 break;  
			 }  
			 break;  
		 case WM_DESTROY:                    //���ڽ�����Ϣ  
			 int i;  

			 DeleteDC(m_CacheHDC);  
			 DeleteDC(m_hdcBuf);  
			 for(i=0;i<4;i++)  
				 DeleteObject(m_bmpGirls[i]);  
			 DeleteObject(m_bmgBg);  
			 ReleaseDC(hWnd,m_hdc);  

			 PostQuitMessage(0);  
			 break;  
		 default:                            //������Ϣ  
			 return DefWindowProc(hWnd, message, wParam, lParam);  
	}  
	return 0;  

}