#include "stdafx.h"
#include <stdio.h>
#include "GameCharacter.h"
#include "MovaleObject.h"

HINSTANCE m_hInst;
HBITMAP m_BmpBg, m_BmpSheep, m_BmpGirl, m_BmpSkill, m_BmpSkillult, m_BmpSlash, m_BmpMagic, m_BmpRecover, m_BmpGame;
CImage m_ImgBg, m_ImgSkill, m_ImgSkillult, m_ImgSlash, m_ImgMagic, m_ImgRecover, m_ImgGameover;
HBITMAP mBmpCache;
HDC m_hdc, m_hdcCache, m_hdcBuf;
int fps, magicAtX, magicAtY;
HWND hWnd;
DWORD tPre, tNow;
int txtNum;
bool attack, over, magicShow, startedToMove;
GameCharacter m_player, m_monster;
char text[5][150];

MovableObject *object ;

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void MyPaint(HDC);
LRESULT CALLBACK OnKeyDown(HWND hWnd, WPARAM wParam) ;