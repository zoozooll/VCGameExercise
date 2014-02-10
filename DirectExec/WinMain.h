#include <d3d9.h>
#include <d3dx9.h>

#define WINDOW_CLASS "UGPDX"
#define WINDOW_NAME "Direct3D Exercise"
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define LIGHT_EXER



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


LRESULT WINAPI MsgProc(HWND, UINT, WPARAM, LPARAM);
bool InitializeD3D(HWND hWnd, bool fullscreen);
void RenderScene(void);
void init_graphics(void);
void init_light(void);
void Shutdown(void);

#define MYVERTEX VertexFlexible