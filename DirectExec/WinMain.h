#include <d3d9.h>

#define WINDOW_CLASS "UGPDX"
#define WINDOW_NAME "Direct3D Exercise"
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

#define D3DFVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

struct Vertex
{
	float x, y, z, rhw;
	unsigned long color;
};

LRESULT WINAPI MsgProc(HWND, UINT, WPARAM, LPARAM);
bool InitializeD3D(HWND hWnd, bool fullscreen);
void RenderScene(void);
void init_graphics(void);
void Shutdown(void);

LPDIRECT3D9 d3d;		// The pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;		// The pointer to device class
LPDIRECT3DVERTEXBUFFER9 v_buffer;    // The pointer to vertex buffer

struct CUSTOMVERTEX
{
	FLOAT x, y, z, rhw;
	DWORD color;
};
