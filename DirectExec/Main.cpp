#include "WinMain.h"


 
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE prevhInst, LPSTR cmdLine, int show)  
{  
	// Register the window class  
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,  
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,  
		WINDOW_CLASS, NULL };  
	RegisterClassEx(&wc);  
	// Create the application's window  
	HWND hWnd = CreateWindow(WINDOW_CLASS, WINDOW_NAME, WS_OVERLAPPEDWINDOW,  
		100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, GetDesktopWindow(), NULL,  
		wc.hInstance, NULL);  
	// Initialize Direct3D  
	if(InitializeD3D(hWnd, false))  
	{  
		// Show the window  
		ShowWindow(hWnd, SW_SHOWDEFAULT);  
		UpdateWindow(hWnd);  
		// Enter the message loop  
		MSG msg;  
		ZeroMemory(&msg, sizeof(msg));  
		while(msg.message != WM_QUIT)  
		{  
			if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))  
			{  
				TranslateMessage(&msg);  
				DispatchMessage(&msg);  
			}  
			else  
				RenderScene();  
		}  
	}  
	// Release any and all resources.  
	Shutdown();  
	// Unregister our window.  
	UnregisterClass(WINDOW_CLASS, wc.hInstance);  
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
	g_D3D = Direct3DCreate9(D3D_SDK_VERSION);  
	if(g_D3D == NULL) return false;  
	// Get the desktop display mode.  
	if(FAILED(g_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))  
		return false;  
	// Set up the structure used to create the D3DDevice  
	D3DPRESENT_PARAMETERS d3dpp;  
	ZeroMemory(&d3dpp, sizeof(d3dpp));  
	if(fullscreen)  
	{  
		d3dpp.Windowed = FALSE;  
		d3dpp.BackBufferWidth = WINDOW_WIDTH;  
		d3dpp.BackBufferHeight = WINDOW_HEIGHT;  
	}  
	else  
	{
		d3dpp.Windowed = TRUE;
	}
		  
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;  
	d3dpp.BackBufferFormat = displayMode.Format;  
	// Create the D3DDevice  
	if(FAILED(g_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,  
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_D3DDevice)))  
	{  
		return false;  
	}  
	if (!InitializeObjects()) 
	{
		return false;
	}
 	return true;  
}  

bool InitializeObjects()
{
	unsigned long col[3] = 
	{
		D3DCOLOR_XRGB(255, 0, 0),
		D3DCOLOR_XRGB(0, 255, 0),
		D3DCOLOR_XRGB(0, 0, 255)
	};

	Vertex objData[] = 
	{
		{ 420.f, 150.f, 0.5f, 1.f, col[0] },
		{ 420.f, 350.f, 0.5f, 1.f, col[1] },
		{ 220.f, 150.f, 0.5f, 1.f, col[2] },
		{ 220.f, 350.f, 0.5f, 1.f, col[0]+col[1] }
	};

	// Create the vertex buffer.  
   if(FAILED(g_D3DDevice->CreateVertexBuffer(sizeof(objData), 0,  
             D3DFVF_VERTEX, D3DPOOL_DEFAULT, &g_D3DVertexBuffer,  
             NULL))) return false;  
  
   // Fill the vertex buffer.  
   void *ptr;  
  
   if(FAILED(g_D3DVertexBuffer->Lock(0, sizeof(objData),  
      &ptr, 0))) return false;  
  
   memcpy(ptr, objData, sizeof(objData));  
    
  
   g_D3DVertexBuffer->Unlock();  
  
   return true; 
}

void RenderScene()  
{  
	// Clear the backbuffer.  
	g_D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);  
	// Begin the scene. Start rendering.  
	g_D3DDevice->BeginScene();  

	// Render object.  
    g_D3DDevice->SetStreamSource(0, g_D3DVertexBuffer, 0,  
                                  sizeof(Vertex));  
    g_D3DDevice->SetFVF(D3DFVF_VERTEX);  
    g_D3DDevice->DrawPrimitive(D3DPT_LINELIST, 0, 2);  
	
	  
	// End the scene. Stop rendering.  
	g_D3DDevice->EndScene();  
	// Display the scene.  
	g_D3DDevice->Present(NULL, NULL, NULL, NULL);  
}  
void Shutdown()  
{  
	if(g_D3DDevice != NULL)
	{
		g_D3DDevice->Release(); 
	}  
	if(g_D3D != NULL)
	{
		g_D3D->Release(); 
	} 
} 