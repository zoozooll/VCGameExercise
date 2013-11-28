#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define WINDOW_CLASS "UGPDX"
#define WINDOW_NAME "Direct3D Exercise"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

LRESULT WINAPI MsgProc(HWND, UINT, WPARAM, LPARAM);
bool InitializeD3D(HWND hWnd, bool fullscreen);
void RenderScene();
void Shutdown();

LPDIRECT3D9 g_D3D;
LPDIRECT3DDEVICE9 g_D3DDevice;