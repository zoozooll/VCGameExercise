#include "WinMain.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	GetMessage(&msg, NULL, 0, 0);
	while (msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			tNow = GetTickCount();
			if (tNow - tPre >= 100)
				MyPaint(m_hdc);
		}
	}
	return msg.wParam;
}

ATOM MyRegisterClass (HINSTANCE hInstance)
{
	WNDCLASSEX wClassEx;
	wClassEx.cbSize = sizeof(WNDCLASSEX);
	wClassEx.style = CS_HREDRAW | CS_VREDRAW;
	wClassEx.lpfnWndProc = (WNDPROC)WndProc;
	wClassEx.cbClsExtra = 0;
	wClassEx.cbWndExtra = 0;
	wClassEx.hInstance = hInstance;
	wClassEx.hIcon = NULL;
	wClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClassEx.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wClassEx.lpszMenuName = NULL;
	wClassEx.lpszClassName = "Game2DExercise";
	wClassEx.hIconSm = NULL;
	return RegisterClassEx(&wClassEx);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HBITMAP bmp;
	m_hInst = hInstance;
	hWnd = CreateWindow("Game2DExercise", "回合制游戏", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		return FALSE;

	}
	MoveWindow(hWnd, 10, 10, 640, 510, true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	m_hdc =GetDC(hWnd);
	m_hdcCache = CreateCompatibleDC(m_hdc);
	m_hdcBuf = CreateCompatibleDC(m_hdc);
	
	bmp = CreateCompatibleBitmap(m_hdc, 640, 510);	
	SelectObject(m_hdcCache, bmp);
	//m_BmpBg = (HBITMAP)LoadImage(NULL, "bg.bmp", IMAGE_BITMAP, 640, 510, LR_LOADFROMFILE);
	//m_BmpSheep = (HBITMAP)LoadImage(NULL, "sheep.bmp", IMAGE_BITMAP, 133, 220, LR_LOADFROMFILE);
	//m_BmpGirl = (HBITMAP)LoadImage(NULL, "girl.bmp", IMAGE_BITMAP, 480, 148, LR_LOADFROMFILE);
	//m_BmpSkill = (HBITMAP)LoadImage(NULL, "skill.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	//m_BmpSkillult = (HBITMAP)LoadImage(NULL, "skillult.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	//m_BmpSlash = (HBITMAP)LoadImage(NULL, "slash.bmp", IMAGE_BITMAP, 192, 162, LR_LOADFROMFILE);
	//m_BmpMagic = (HBITMAP)LoadImage(NULL, "magic.bmp", IMAGE_BITMAP, 200, 100, LR_LOADFROMFILE);
	//m_BmpRecover = (HBITMAP)LoadImage(NULL, "recover.bmp", IMAGE_BITMAP, 300, 150, LR_LOADFROMFILE);
	//m_BmpGame = (HBITMAP)LoadImage(NULL, "over.bmp", IMAGE_BITMAP, 189, 74, LR_LOADFROMFILE);

	m_ImgBg.Load("bg.png");
	m_ImgSheep.Load("sheep.png");
	m_ImgGirl.Load("girl.png");
	m_ImgSkill.Load("skill.png");
	m_ImgSkillult.Load("skillult.png");
	m_ImgSlash.Load("slash.png");
	m_ImgMagic.Load("magic.png");
	m_ImgRecover.Load("recover.png");
	m_ImgGameover.Load("gameover.png");

	m_player.nHp = 500;
	m_player.fHp = 500;
	m_player.lv = 2;
	m_player.w = 4;

	m_monster.nHp = 500;
	m_monster.fHp = 500;
	m_monster.lv = 1;
	m_monster.w = 1;

	txtNum = 0;
	SetBkMode(m_hdcCache, TRANSPARENT);

	MyPaint(m_hdc);
	return TRUE;
}


void MyPaint(HDC hdc)
{
	char str[100];
	int damage;

	/*SelectObject(m_hdcBuf, m_BmpBg);
	BitBlt(m_CacheHDC, 0, 0, 640, 510, m_hdcBuf, 0, 0, SRCCOPY);*/
	m_ImgBg.Draw(m_hdcCache, 0, 0, 640, 510,0, 0, m_ImgBg.GetWidth(), m_ImgBg.GetHeight());

	//对战信息
	for (int i = 0; i < txtNum; i++)
	{
		TextOut(m_hdcCache, 0, 360 + i *18, text[i], strlen(text[i]));
	}
	if (m_monster.nHp > 0) 
	{
		/*SelectObject(m_hdcBuf, m_BmpSheep);
		BitBlt(m_CacheHDC, 70, 180, 133, 110,m_hdcBuf, 0, 110, SRCAND);
		BitBlt(m_CacheHDC, 70, 180, 133, 110,m_hdcBuf, 0, 0, SRCPAINT);*/
		m_ImgSheep.Draw(m_hdcCache, 70, 180, m_ImgSheep.GetWidth(), m_ImgSheep.GetHeight(),0, 0, m_ImgSheep.GetWidth(), m_ImgSheep.GetHeight());

		sprintf(str, "%d/%d", m_monster.nHp, m_monster.fHp);
		TextOut(m_hdcCache, 100, 320, str, strlen(str));
	}

	if (m_player.nHp > 0)
	{
		/*SelectObject(m_hdcBuf, m_BmpGirl);
		BitBlt(m_CacheHDC, 500, 200, 60, 74, m_hdcBuf, pNum * 60, 74, SRCAND);
		BitBlt(m_CacheHDC, 500, 200, 60, 74, m_hdcBuf, pNum * 60, 0, SRCPAINT);*/
		m_ImgGirl.Draw(m_hdcCache, 500, 200, m_ImgGirl.GetWidth(), m_ImgGirl.GetHeight(),0, 0, m_ImgGirl.GetWidth(), m_ImgGirl.GetHeight());

		sprintf(str, "%d/%d", m_player.nHp,m_player.fHp);
		TextOut(m_hdcCache, 510, 320, str, strlen(str));
	}

	if (over)	//游戏结束时候的动画
	{
		/*SelectObject(m_hdcBuf, m_BmpGame);
		BitBlt(m_CacheHDC,200,200,289,37,m_hdcBuf,0,37,SRCAND);  
		BitBlt(m_CacheHDC,200,200,289,37,m_hdcBuf,0,0,SRCPAINT);  */
		m_ImgGameover.Draw(m_hdcCache, 200, 200, m_ImgGameover.GetWidth(), m_ImgGameover.GetHeight(),0, 0, m_ImgGameover.GetWidth(), m_ImgGameover.GetHeight());

	} 
	else if (!attack)	//在选择攻击时候的状态 贴上选择技能命令的图标
	{
		/*SelectObject(m_hdcBuf, m_BmpSkill);
		BitBlt(m_CacheHDC, 500, 350, 50, 50, m_hdcBuf, 0, 0, SRCAND);
		SelectObject(m_hdcBuf,m_BmpSkillult);  
		BitBlt(m_CacheHDC,430,350,50,50,m_hdcBuf,0,0,SRCCOPY); */
		m_ImgSkill.Draw(m_hdcCache, 500, 350, m_ImgSkill.GetWidth(), m_ImgSkill.GetHeight(),0, 0, m_ImgSkill.GetWidth(), m_ImgSkill.GetHeight());
		m_ImgSkillult.Draw(m_hdcCache, 430, 350, m_ImgSkillult.GetWidth(), m_ImgSkillult.GetHeight(),0, 0, m_ImgSkillult.GetWidth(), m_ImgSkillult.GetHeight());

	}
	else
	{
		f++;

		if (f > 5 && f <= 10)
		{
			/*SelectObject(m_hdcBuf, m_BmpSlash);

			BitBlt(m_CacheHDC,100,160,98,162,m_hdcBuf,98,0,SRCAND);  
            BitBlt(m_CacheHDC,100,160,98,162,m_hdcBuf,0,0,SRCPAINT);*/

			m_ImgSlash.Draw(m_hdcCache, 100, 160, m_ImgSlash.GetWidth(), m_ImgSlash.GetHeight(),0, 0, m_ImgSlash.GetWidth(), m_ImgSlash.GetHeight());

			if (f == 10) 
			{
				if (rand()%5 == 4) 
				{
					damage = 4*(rand() % 10 + m_player.lv * m_player.w);
					m_monster.nHp -= damage;
					sprintf(str, "触发了大招，对怪物造成了%d点伤害", damage);
				}
				else 
				{
					damage = rand() %10 + m_player.lv * m_player.w;
					m_monster.nHp -= damage;
					sprintf(str, "对怪物造成了%d点伤害", damage);
				}

				MsgInsert(str);
				CheckDie(m_monster.nHp, false);
			}

		}
		else if (f == 15)
		{
			if (m_monster.nHp > 50)
			{
				if (rand() % 5 != 1)
					m_monster.kind = 0;
				else
					m_monster.kind = 1;
			}
			else 
			{
				switch(rand()%5)
				{
				case 0:
					m_monster.kind = 0;
					break;
				case 1:
					m_monster.kind = 1;
					break;
				case 2:
					m_monster.kind = 2;
					break;
				case 3:
					m_monster.kind = 3;
					break;
				case 4:
					m_monster.kind = 4;
					break;

				}
			}
		}
		else if (f >= 26 && f <= 30)
		{
			switch(m_monster.kind)
			{
			case 0:
				/*SelectObject(m_hdcBuf, m_BmpSlash);
				BitBlt(m_CacheHDC, 480, 150, 98, 162, m_hdcBuf, 98, 0, SRCAND);
				BitBlt(m_CacheHDC, 480, 150, 98, 162, m_hdcBuf, 0, 0, SRCPAINT);*/
				m_ImgSlash.Draw(m_hdcCache, 480, 150, m_ImgSlash.GetWidth(), m_ImgSlash.GetHeight(),0, 0, m_ImgSlash.GetWidth(), m_ImgSlash.GetHeight());
				if (f == 30)
				{
					damage = rand() % 20 + m_monster.lv * m_monster.w;
					m_player.nHp -= damage;
					sprintf(str, "怪物利爪攻击...对玩家照成 %d 点伤害", damage);
					MsgInsert(str);
					CheckDie(m_player.nHp, true);
				}
				break;
			case 1:
				/*SelectObject(m_hdcBuf, m_BmpSlash);
				BitBlt(m_CacheHDC, 480, 150, 98, 162, m_hdcBuf, 98, 0, SRCAND);
				BitBlt(m_CacheHDC, 480, 150, 98, 162, m_hdcBuf, 0, 0, SRCPAINT);*/
				m_ImgSlash.Draw(m_hdcCache, 480, 150, m_ImgSlash.GetWidth(), m_ImgSlash.GetHeight(),0, 0, m_ImgSlash.GetWidth(), m_ImgSlash.GetHeight());
				if (f == 30)
				{
					damage = rand() % 10 + m_monster.lv * m_monster.w * 5;
					m_player.nHp -= damage;
					sprintf(str, "怪物释放闪电连...对玩家照成 %d 点伤害", damage);
					MsgInsert(str);
					CheckDie(m_player.nHp, true);
				}
				break;
			case 2:
				/*SelectObject(m_hdcBuf, m_BmpSlash);
				BitBlt(m_CacheHDC, 480, 150, 98, 162, m_hdcBuf, 98, 0, SRCAND);
				BitBlt(m_CacheHDC, 480, 150, 98, 162, m_hdcBuf, 0, 0, SRCPAINT);*/
				m_ImgSlash.Draw(m_hdcCache, 480, 150, m_ImgSlash.GetWidth(), m_ImgSlash.GetHeight(),0, 0, m_ImgSlash.GetWidth(), m_ImgSlash.GetHeight());
				if (f == 30)
				{
					damage = rand() % 30 + m_monster.lv * m_monster.w * 10;
					m_player.nHp -= damage;
					sprintf(str, "怪物致命一击...对玩家照成 %d 点伤害", damage);
					MsgInsert(str);
					CheckDie(m_player.nHp, true);
				}
				break;
			case 3:
				/*SelectObject(m_hdcBuf, m_BmpRecover);
				BitBlt(m_CacheHDC, 480, 150, 98, 162, m_hdcBuf, 98, 0, SRCAND);
				BitBlt(m_CacheHDC, 480, 150, 98, 162, m_hdcBuf, 0, 0, SRCPAINT);*/
				m_ImgSlash.Draw(m_hdcCache, 480, 150, m_ImgSlash.GetWidth(), m_ImgSlash.GetHeight(),0, 0, m_ImgSlash.GetWidth(), m_ImgSlash.GetHeight());
				if (f == 30)
				{
					damage = rand() % 10 + m_monster.lv * m_monster.w / 2;
					m_monster.nHp += damage;
					sprintf(str, "怪物回复生命值...对自身和回复 %d 点生命值", damage);
					MsgInsert(str);
					CheckDie(m_player.nHp, true);
				}
				break;
			case 4:
				if (f == 30)
				{
					if (rand() %3 ==1) 
					{
						over = true;
						m_monster.nHp = 0;
						sprintf(str, "怪物逃跑 成功");
					} 
					else 
					{
						sprintf(str, "怪物逃跑，失败");
					}
					MsgInsert(str);
					CheckDie(m_player.nHp, true);
				}
				break;
			}
		}
		if (f == 30)
		{
			attack = false;
			f = 0;
		}
	}

	BitBlt(m_hdc, 0, 0, 640, 510, m_hdcCache, 0, 0, SRCCOPY);

	tPre = GetTickCount();
	pNum ++;
	if (pNum == 8)
		pNum = 0;
}

void MsgInsert(char* str)
{
	if (txtNum < 5)
	{
		sprintf(text[txtNum], str);
		txtNum++;
	}
	else
	{
		for (int i = 0; i < txtNum; i++)
			sprintf(text[i], text[i + 1]);
		sprintf(text[4], str);
	}
}

void CheckDie(int hp, bool player)
{
	char str[100];
	if (hp <= 0)
	{
		over = true;
		if (player)
		{
			sprintf(str, "GAME OVER");
			MsgInsert(str);
		}
		else
		{
			sprintf(str, "Win");
			MsgInsert(str);
		}
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)  
	 {  
		 case WM_KEYDOWN:         //按下键盘消息  
			 //判断按键的虚拟键码  
			 switch (wParam)   
			 {  
				 case VK_ESCAPE:           //按下【Esc】键  
					 PostQuitMessage( 0 );  //结束程序  
					 break;  
				 case VK_UP:               //按下【↑】键  
					 //先按照目前的移动方向来进行贴图坐标修正，并加入人物往上移动的量（每次按下一次按键移动10个单位），来决定人物贴图坐标的X与Y值，接着判断坐标是否超出窗口区域，若有则再次修正  
					 switch(dir)  
					 {  
						 case 0:   
							 y -= 10;  
							 break;  
						 case 1:  
							 x -= 1;  
							 y -= 8;  
							 break;  
						 case 2:   
							 x += 2;  
							 y -= 10;  
							 break;  
						 case 3:  
							 x += 2;  
							 y -= 10;  
							 break;  
					 }  
					 if(y < 0)  
						 y = 0;  
					 dir = 0;  
					 break;  
				 case VK_DOWN:             //按下【↓】键  
					 switch(dir)  
					 {  
						 case 0:  
							 x += 1;  
							 y += 8;  
							 break;  
						 case 1:  
							 y += 10;  
							 break;  
						 case 2:  
							 x += 3;  
							 y += 6;  
							 break;  
						 case 3:  
							 x += 3;  
							 y += 6;  
							 break;  
					 }  

					 if(y > 375)  
						 y = 375;  
					 dir = 1;  
					 break;  
				 case VK_LEFT:             //按下【←】键  
					 switch(dir)  
					 {  
						 case 0:  
							 x -= 12;  
							 break;  
						 case 1:  
							 x -= 13;  
							 y += 4;  
							 break;  
						 case 2:  
							 x -= 10;  
							 break;  
						 case 3:  
							 x -= 10;  
							 break;  
					 }  
					 if(x < 0)  
						 x = 0;  
					 dir = 2;  
					 break;  
				 case VK_RIGHT:             //按下【→】键  
					 switch(dir)  
					 {  
						 case 0:  
							 x += 8;  
							 break;  
						 case 1:  
							 x += 7;  
							 y += 4;  
							 break;  
						 case 2:  
							 x += 10;  
							 break;  
						 case 3:  
							 x += 10;  
							 break;  
					 }  
					 if(x > 575)  
						 x = 575;  
					 dir = 3;  
					 break;  
			 }  
			 break;  
		 case WM_LBUTTONDOWN:
			 if (!attack)
			 {
				 x = LOWORD(lParam);
				 y = HIWORD(lParam);
				 if (x >= 500 && x <= 550 && y >=350 && y <=440)
					 attack = true;
			 }
			 break;
		 case WM_DESTROY:                    //窗口结束消息  
			 DeleteDC(m_hdcCache);  
			 DeleteDC(m_hdcBuf);  
			 m_ImgBg      .Destroy();
			m_ImgSheep   .Destroy();
			m_ImgGirl    .Destroy();
			m_ImgSkill   .Destroy();
			m_ImgSkillult.Destroy(); 
			m_ImgSlash   .Destroy();
			m_ImgMagic   .Destroy();
			m_ImgRecover .Destroy();
			m_ImgGameover    .Destroy();
  
			 ReleaseDC(hWnd,m_hdc); 
 

			 PostQuitMessage(0);  
			 break;  
		 default:                            //其他消息  
			 return DefWindowProc(hWnd, message, wParam, lParam);  
	}  
	return 0;  

}