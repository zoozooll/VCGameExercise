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
		// use the getmessage for loop
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

bool InitializeD3D(HWND hWnd, bool fullscreen)  
{  
	D3DDISPLAYMODE displayMode;  
	// Create the D3D object.  
	d3d = Direct3DCreate9(D3D_SDK_VERSION);  
	if(d3d == NULL) return false;  
	// Get the desktop display mode.  
	if(FAILED(d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))  
		return false;  
	// Set up the structure used to create the D3DDevice  
	D3DPRESENT_PARAMETERS d3dpp;  
	ZeroMemory(&d3dpp, sizeof(d3dpp));  
	if(fullscreen)  
	{  
		d3dpp.Windowed = FALSE;  
		
	}  
	else 
	{
		d3dpp.Windowed = TRUE; 
	}
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;  
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = displayMode.Format;
	d3dpp.BackBufferWidth = WINDOW_WIDTH;  
	d3dpp.BackBufferHeight = WINDOW_HEIGHT;  

	// Create the D3DDevice  
	if(FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL, 
		hWnd,  
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
		&d3dpp, 
		&d3ddev)))  
	{  
		return false;  
	}
	init_graphics();
	return true;  
}

void init_graphics(void)
{
	CUSTOMVERTEX vertices[] = 
	{
		{400.f, 62.5f, 500.0f, 1.f, D3DCOLOR_XRGB(0, 0, 255)},
		{650.f, 500.f, 500.0f, 1.f, D3DCOLOR_XRGB(0, 255, 0)},
		{150.f, 500.f, 500.0f, 1.f, D3DCOLOR_XRGB(255, 0, 0)}
	};
	d3ddev->CreateVertexBuffer(3 * sizeof(CUSTOMVERTEX),
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&v_buffer,
		NULL);
	VOID *pVoid;

	v_buffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	v_buffer->Unlock();
}

void RenderScene()  
{  
	// Clear the backbuffer.  
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);  
	// Begin the scene. Start rendering.  
	d3ddev->BeginScene();  

	d3ddev->SetFVF(CUSTOMFVF);
	d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	// End the scene. Stop rendering.  
	d3ddev->EndScene();  
	// Display the scene.  
	d3ddev->Present(NULL, NULL, NULL, NULL);  
}  

void Shutdown()  
{  
	if(d3ddev != NULL) d3ddev->Release();  
	if(d3d != NULL) d3d->Release();  
	if(v_buffer != NULL) v_buffer->Release();
}  
