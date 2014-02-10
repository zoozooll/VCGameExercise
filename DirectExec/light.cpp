#include "WinMain.h"

#ifdef LIGHT_EXER

#define D3DFVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define D3DFVF_VERTEX1 (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define D3DFVF_VERTEX2 (D3DFVF_XYZ | D3DFVF_NORMAL)

#define CUSTOMFVF D3DFVF_VERTEX2

LPDIRECT3D9 d3d;		// The pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;		// The pointer to device class
LPDIRECT3DVERTEXBUFFER9 v_buffer;    // The pointer to vertex buffer
LPDIRECT3DINDEXBUFFER9 i_buffer;	// the pointer to index buffer;


static void SetTransform();
static void SetTransform2();

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
	init_light();
	// turn of the 3d light
	d3ddev->SetRenderState(D3DRS_LIGHTING, TRUE);  
	// both sides of triangle
	//d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	d3ddev->SetRenderState(D3DRS_ZENABLE, true);
	//d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50)); //环境光
	d3ddev->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	d3ddev->SetRenderState(D3DRS_SPECULARENABLE,TRUE);
	return true;  
}

void init_graphics(void)
{
	static float index = 0.1f;
	MYVERTEX vertices[] = 
	{
		{ -3.0f, -3.0f, 3.0f, 0.0f, 0.0f, index, },    // side 1
		{ 3.0f, -3.0f, 3.0f, 0.0f, 0.0f, index, },
		{ -3.0f, 3.0f, 3.0f, 0.0f, 0.0f, index, },
		{ 3.0f, 3.0f, 3.0f, 0.0f, 0.0f, index, },

		{ -3.0f, -3.0f, -3.0f, 0.0f, 0.0f, -index, },    // side 2
		{ -3.0f, 3.0f, -3.0f, 0.0f, 0.0f, -index, },
		{ 3.0f, -3.0f, -3.0f, 0.0f, 0.0f, -index, },
		{ 3.0f, 3.0f, -3.0f, 0.0f, 0.0f, -index, },

		{ -3.0f, 3.0f, -3.0f, 0.0f, index, 0.0f, },    // side 3
		{ -3.0f, 3.0f, 3.0f, 0.0f, index, 0.0f, },
		{ 3.0f, 3.0f, -3.0f, 0.0f, index, 0.0f, },
		{ 3.0f, 3.0f, 3.0f, 0.0f, index, 0.0f, },

		{ -3.0f, -3.0f, -3.0f, 0.0f, -index, 0.0f, },    // side 4
		{ 3.0f, -3.0f, -3.0f, 0.0f, -index, 0.0f, },
		{ -3.0f, -3.0f, 3.0f, 0.0f, -index, 0.0f, },
		{ 3.0f, -3.0f, 3.0f, 0.0f, -index, 0.0f, },

		{ 3.0f, -3.0f, -3.0f, index, 0.0f, 0.0f, },    // side 5
		{ 3.0f, 3.0f, -3.0f, index, 0.0f, 0.0f, },
		{ 3.0f, -3.0f, 3.0f, index, 0.0f, 0.0f, },
		{ 3.0f, 3.0f, 3.0f, index, 0.0f, 0.0f, },

		{ -3.0f, -3.0f, -3.0f, -index, 0.0f, 0.0f, },    // side 6
		{ -3.0f, -3.0f, 3.0f, -index, 0.0f, 0.0f, },
		{ -3.0f, 3.0f, -3.0f, -index, 0.0f, 0.0f, },
		{ -3.0f, 3.0f, 3.0f, -index, 0.0f, 0.0f, },
	};
	/*以上变量便是顶点，以及顶点法线。前面三个表示 x, y，z坐标，跟之前的一样。
	后面三个数字是指顶点法线，顶点法线跟所在的平面法线一致。因此在画图的时候，
	有时候顶点坐标一样，但是顶点法线不一样，需要用两套表示。
	一个正方体6面，即会有6个顶点法线值。
	*/
	//MYVERTEX vertices[] = 
	//{
	//	{400.f, 62.5f, 500.0f, 1.f, D3DCOLOR_XRGB(0, 0, 255)},
	//	{650.f, 500.f, 500.0f, 1.f, D3DCOLOR_XRGB(0, 255, 0)},
	//	{150.f, 500.f, 500.0f, 1.f, D3DCOLOR_XRGB(255, 0, 0)}
	//};
	d3ddev->CreateVertexBuffer(24* sizeof(MYVERTEX),
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&v_buffer,
		NULL);
	VOID *pVoid;
	v_buffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	v_buffer->Unlock();
	short indices[] = 
	{
		0, 1, 2,    // side 1
		2, 1, 3,
		4, 5, 6,    // side 2
		6, 5, 7,
		8, 9, 10,    // side 3
		10, 9, 11,
		12, 13, 14,    // side 4
		14, 13, 15,
		16, 17, 18,    // side 5
		18, 17, 19,
		20, 21, 22,    // side 6
		22, 21, 23,

	};
	// create an index buffer interface called i_buffer
	d3ddev->CreateIndexBuffer(36*sizeof(short),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&i_buffer,
		NULL);
	i_buffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, indices, sizeof(indices));
	i_buffer->Unlock();
}

void init_light(void)
{
	D3DLIGHT9 light;	//光
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;	
	// 光的类型，可以设定directional(平行光源), point(点光源), spot(聚光灯)；
	//light.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//光的颜色（散射）
	light.Direction = D3DXVECTOR3(0.0f, 0.0f, -1.0f);	// 光的方向
	d3ddev->SetLight(0, &light);
	d3ddev->LightEnable(0, TRUE);

	D3DMATERIAL9 material;	// 反光材质
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	d3ddev->SetMaterial(&material);
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
	//d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	//SetTransform2();
	//d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	// End the scene. Stop rendering. 
	// select the vertex and index buffers to use
	d3ddev->SetIndices(i_buffer);

	// draw the cube
	d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);
	d3ddev->EndScene();  
	// Display the scene.  
	d3ddev->Present(NULL, NULL, NULL, NULL);  
}  

void Shutdown()
{
	if(v_buffer != NULL) v_buffer->Release();
	if(i_buffer != NULL) i_buffer->Release();
	if(d3ddev != NULL) d3ddev->Release();  
	if(d3d != NULL) d3d->Release();  
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
                       &D3DXVECTOR3 (0.0f, 0.0f, 100.0f),    // the camera position
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
	D3DXMatrixRotationX(&matRotate,	index);
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

#endif