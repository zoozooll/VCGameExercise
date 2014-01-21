#include <d3d9.h>
#include <d3dx9.h>

#define WINDOW_CLASS "UGPDX"
#define WINDOW_NAME "Direct3D Exercise"
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800


#define D3DFVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define D3DFVF_VERTEX1 (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define D3DFVF_VERTEX2 (D3DFVF_XYZ | D3DFVF_NORMAL)

#define CUSTOMFVF D3DFVF_VERTEX2

struct Vertex
{
	FLOAT x, y, z;
	DWORD color;
} ;

struct VertexRHW
{
	FLOAT x, y, z, rhw;
	DWORD color;
};

struct VertexFlexible
{
	FLOAT x, y, z;
	D3DVECTOR normal;
};

LPDIRECT3D9 d3d;		// The pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;		// The pointer to device class
LPDIRECT3DVERTEXBUFFER9 v_buffer;    // The pointer to vertex buffer
LPDIRECT3DINDEXBUFFER9 i_buffer;	// the pointer to index buffer;

LRESULT WINAPI MsgProc(HWND, UINT, WPARAM, LPARAM);
bool InitializeD3D(HWND hWnd, bool fullscreen);
void RenderScene(void);
void init_graphics(void);
void init_light(void);
void Shutdown(void);

#define MYVERTEX VertexFlexible