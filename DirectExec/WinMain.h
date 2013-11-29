#include <d3d9.h>

#define WINDOW_CLASS "UGPDX"
#define WINDOW_NAME "Direct3D Exercise"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define D3DFVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

struct Vertex
{
	float x, y, z, rhw;
	unsigned long color;
};

LRESULT WINAPI MsgProc(HWND, UINT, WPARAM, LPARAM);
bool InitializeD3D(HWND hWnd, bool fullscreen);
bool InitializeObjects();
void RenderScene();
void Shutdown();

LPDIRECT3D9 g_D3D;
LPDIRECT3DDEVICE9 g_D3DDevice;
LPDIRECT3DVERTEXBUFFER9 g_D3DVertexBuffer;