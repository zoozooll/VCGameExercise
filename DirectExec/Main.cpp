#include "WinMain.h"

static void SetTransform();
static void SetTransform2();

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
	// add depth;
	// Auto matically run the z-buffer for us
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

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
	// turn of the 3d light
	d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);  
	// both sides of triangle
	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	d3ddev->SetRenderState(D3DRS_ZENABLE, true);
	return true;  
}

void init_graphics(void)
{
	MYVERTEX vertices[] = 
	{
		{3.0f, -3.f, .0f, D3DCOLOR_XRGB(0, 0, 255)},
		{0.f, 3.f, .0f, D3DCOLOR_XRGB(0, 255, 0)},
		{-3.f, -3.f, .0f, D3DCOLOR_XRGB(255, 0, 0)}
	};
	//MYVERTEX vertices[] = 
	//{
	//	{400.f, 62.5f, 500.0f, 1.f, D3DCOLOR_XRGB(0, 0, 255)},
	//	{650.f, 500.f, 500.0f, 1.f, D3DCOLOR_XRGB(0, 255, 0)},
	//	{150.f, 500.f, 500.0f, 1.f, D3DCOLOR_XRGB(255, 0, 0)}
	//};
	d3ddev->CreateVertexBuffer(3 * sizeof(MYVERTEX),
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
	// Clear the back buffer.  
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0); 
	d3ddev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0F, 0);
	// Begin the scene. Start rendering.  
	d3ddev->BeginScene();  

	d3ddev->SetFVF(CUSTOMFVF);

	SetTransform(); // set the transform for exercise;
	d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(MYVERTEX));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	SetTransform2();
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

static void SetTransform()
{
	D3DXMATRIX matRotate;
	static float index = .0f;
	index += .05f;
	/*D3DXMatrixRotationX(&matRotate,
		index);
	d3ddev->SetTransform(D3DTS_WORLD, &matRotate);*/


	D3DXMATRIX matView;    // the view transform matrix
    D3DXMatrixLookAtLH(&matView,
                       &D3DXVECTOR3 (0.0f, 0.0f, 10.0f),    // the camera position
                       &D3DXVECTOR3 (0.0f, 0.0f, 0.0f),    // the look-at position
                       &D3DXVECTOR3 (0.0f, 1.0f, 0.0f));    // the up direction

    d3ddev->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView

    D3DXMATRIX matProjection;     // the projection transform matrix

    D3DXMatrixPerspectiveFovLH(&matProjection,
                               D3DXToRadian(45),    // the horizontal field of view
                               (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, // aspect ratio
                               1.0f,    // the near view-plane
                               100.0f);    // the far view-plane

    d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection

	D3DXMATRIX matTranglationA;
	D3DXMatrixTranslation(&matTranglationA, 0.0f, 0.0f, 2.0f);
	D3DXMatrixRotationY(&matRotate,	index);
	d3ddev->SetTransform(D3DTS_WORLD, &(matTranglationA * matRotate));
}

static void SetTransform2()
{
	D3DXMATRIX matRotate;
	D3DXMATRIX matTranglationB;
	D3DXMatrixTranslation(&matTranglationB, 0.0f, 0.0f, -2.0f);
	static float index = .0f;
	index += .05f;
	D3DXMatrixRotationY(&matRotate,	index);
	d3ddev->SetTransform(D3DTS_WORLD, &(matTranglationB * matRotate));
}
