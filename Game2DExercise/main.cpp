#include "WinMain.h"

// 前面是回合制游戏的有关的函数
static void LoadImages();

static void InitializeCharactors();

static void DrawImage(const CImage &image, const HDC &hdc,const int &x, const int &y);

static void DrawMagicSpell();

static void DrawMonster();

static void DrawPlayer();

static void DrawImages(int atX, int atY, bool isShow);

static void DoingPerBeat(int &beats);

static void Attricking(const int &millisSpan);

static void MsgInsert(char* str);

// 下面是关于物体的移动以及碰撞相关的函数；
static void LoadObjects();

static void BeginMovie();

static void StopMovie();

static void DrawMovableObject();

static void UpdateMovingMsg(const int &);

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
			if (tNow - tPre >= 1)
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
	hWnd = CreateWindow("Game2DExercise", "可移动物体", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		return FALSE;

	}
	MoveWindow(hWnd, 10, 10, 1200, 800, true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	m_hdc =GetDC(hWnd);
	m_hdcCache = CreateCompatibleDC(m_hdc);
	m_hdcBuf = CreateCompatibleDC(m_hdc);
	
	bmp = CreateCompatibleBitmap(m_hdc, 1200, 800);	
	SelectObject(m_hdcCache, bmp);

	// Load all images;
	LoadImages();

	// initalize all charactors
	//InitializeCharactors();

	//txtNum = 0;

	LoadObjects();

	SetBkMode(m_hdcCache, TRANSPARENT);
	
	MyPaint(m_hdc);

	return TRUE;
}


void MyPaint(HDC hdc)
{
	//char log[100];
	const int deltaMillis = tNow - tPre; // 两个frame之间的时间差；
	//sprintf(log, "mypaint %d \n", millisSpan);
	//OutputDebugString(log);

	//m_ImgBg.Draw(m_hdcCache, 0, 0, 640, 510,0, 0, m_ImgBg.GetWidth(), m_ImgBg.GetHeight());
	DrawImage(m_ImgBg, m_hdcCache, 0, 0);

	//对战信息
	for (int i = 0; i < txtNum; i++)
	{
		TextOut(m_hdcCache, 0, 630 + i *18, text[i], strlen(text[i]));
	}
	//DrawMonster();
	//DrawPlayer();
	//DrawMagicSpell();

	//if (over)	//游戏结束时候的动画
	//{
	//	DrawImage(m_ImgGameover, m_hdcCache, 200, 200);
	//} 
	//else if (!attack)	//在选择攻击时候的状态 贴上选择技能命令的图标
	//{
	//	DrawImage(m_ImgSkill, m_hdcCache, 500, 350);
	//	DrawImage(m_ImgSkillult, m_hdcCache, 430, 350);
	//}
	//else	//在选择了攻击状态之后，会自动进行一些攻击动作，以及怪物还击。
	//{
	//	Attricking(deltaMillis);
	//}

	if (startedToMove)
	{
		if (object->onMovie(deltaMillis))
		{
			
		}

		UpdateMovingMsg(deltaMillis);
	}
	DrawMovableObject();
	//object->onMovie(deltaMillis);
	
	BitBlt(m_hdc, 0, 0, 1200, 800, m_hdcCache, 0, 0, SRCCOPY);

	tPre = GetTickCount();
	
}



// WPARAM wParam 参数为判断哪个按键
LRESULT CALLBACK OnKeyDown(HWND hWnd, WPARAM wParam) 
{
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)  
	 {  
		 case WM_KEYDOWN:         //按下键盘消息  
			 return  OnKeyDown(hWnd, wParam);
		 case WM_LBUTTONDOWN:
			/* if (!attack)
			 {
				 int x = LOWORD(lParam);
				 int y = HIWORD(lParam);
				 if (x >= 500 && x <= 550 && y >=350 && y <=440)
					 attack = true;
			 }*/
			 BeginMovie();
			 break;
		 case WM_RBUTTONDOWN:
			 StopMovie();
			 break;
		 case WM_DESTROY:                    //窗口结束消息  
			 delete object;
			 DeleteDC(m_hdcCache);  
			 DeleteDC(m_hdcBuf);  
			 m_ImgBg      .Destroy();
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

static void LoadImages()
{
	m_ImgBg.Load("bg_big.png");
	m_ImgSkill.Load("skill.png");
	m_ImgSkillult.Load("skillult.png");
	m_ImgSlash.Load("slash.png");
	m_ImgMagic.Load("magic.png");
	m_ImgRecover.Load("recover.png");
	m_ImgGameover.Load("gameover.png");
}

static void InitializeCharactors()
{
	//m_player.nHp = 500;
	//m_player.fHp = 500;
	//m_player.lv = 2;
	//m_player.w = 4;
	m_player.Initalize(500, "girl.png", 20, 500, 100, 0, 0, 20);

	/*m_monster.nHp = 500;
	m_monster.fHp = 500;
	m_monster.lv = 1;
	m_monster.w = 1;*/
	m_monster.Initalize(400, "sheep.png", 22, 70, 120, 0, 0, 20);
}

static void DrawImage(const CImage &image, const HDC &hdc,const int &x, const int &y)
{
	image.Draw(hdc, x, y, image.GetWidth(), image.GetHeight(),0, 0, image.GetWidth(), image.GetHeight());
}

static void DrawMagicSpell()
{
	//m_ImgSlash.Draw(m_hdcCache, 100, 160, m_ImgSlash.GetWidth(), m_ImgSlash.GetHeight(),0, 0, m_ImgSlash.GetWidth(), m_ImgSlash.GetHeight());
	//m_ImgSlash.Draw(m_hdcCache, 480, 150, m_ImgSlash.GetWidth(), m_ImgSlash.GetHeight(),0, 0, m_ImgSlash.GetWidth(), m_ImgSlash.GetHeight());
	if (magicShow) 
	{
		//m_ImgSlash.Draw(m_hdcCache, magicAtX, magicAtY, m_ImgSlash.GetWidth(), m_ImgSlash.GetHeight(),0, 0, m_ImgSlash.GetWidth(), m_ImgSlash.GetHeight());
		DrawImage(m_ImgSlash, m_hdcCache, magicAtX, magicAtY);
	}
	
}

static void DrawMonster()
{
	char str[100];
	if (!m_monster.isDead()) 
	{
		//m_monster.image.Draw(m_hdcCache, 70, 180, m_ImgSheep.GetWidth(), m_ImgSheep.GetHeight(),0, 0, m_ImgSheep.GetWidth(), m_ImgSheep.GetHeight());
		DrawImage(m_monster.image, m_hdcCache, 70, 180);
		m_monster.getHpString(str);
		TextOut(m_hdcCache, 100, 320, str, strlen(str));
	}
}

static void DrawPlayer()
{
	char str[100];
	if (!m_player.isDead())
	{
		//m_ImgGirl.Draw(m_hdcCache, 500, 200, m_ImgGirl.GetWidth(), m_ImgGirl.GetHeight(),0, 0, m_ImgGirl.GetWidth(), m_ImgGirl.GetHeight());
		DrawImage(m_player.image, m_hdcCache, 500, 200);
		m_player.getHpString(str);
		TextOut(m_hdcCache, 510, 320, str, strlen(str));
	}
}

static void DrawImages(int atX, int atY, bool isShow)
{
	if (isShow)
	{
		magicAtX = atX;
		magicAtY = atY;
		magicShow = isShow;
	} 
	else
	{
		magicShow = false;
	}
}

static void DoingPerBeat(int &beats)
{
	int damage;
	char str[100];
	

	switch(beats)
	{
	case 6:
		DrawImages(100, 160, true);
		break;
	case 10:
		//玩家对怪物进行攻击的时候
		damage = m_monster.UnderAccacked(m_player.Attacking());
		DrawImages(100, 160, false);
		sprintf(str, "对怪物造成了%d点伤害", damage);
		MsgInsert(str);

		over = m_monster.isDead();
		break;
	case 26:
		DrawImages(480, 150, true);
		break;
	case 30:
		//怪物对玩家进行攻击的时候
		damage = m_player.UnderAccacked(m_monster.Attacking());
		DrawImages(480, 160, false);
		sprintf(str, "对玩家造成了%d点伤害", damage);
		MsgInsert(str);
		over = m_player.isDead();
		break;
	}
}

static void Attricking(const int &millisSpan)
{
	
	static int beats = 0;   //节拍;
	static int preMillis;	//上一个节拍时间以millis为单位
	
	preMillis += millisSpan;
	if (preMillis > 100) 
	{
		beats++;
		preMillis = 0;
		DoingPerBeat(beats);
	}
	if (beats == 30)
	{
		attack = false;
		beats = 0;
		
	}
}

static void MsgInsert(char* str)
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

static void LoadObjects()
{
	object = new MovableObject("可移动物体","onion.png");
	object->InitializeSite(50, 50, 50,40, -10, -5);
}

static void DrawMovableObject()
{
	DrawImage(object->image, m_hdcCache, object->x, object->y);
}

static void BeginMovie()
{
	startedToMove = true;
}

static void StopMovie()
{
	startedToMove = false;
}

static void UpdateMovingMsg(const int &deltaTime)
{
	static int timeSpan;
	timeSpan += deltaTime;
	if (timeSpan > 1500) 
	{
		char str[150];
		sprintf(str, "%s is at : (%d, %d), speed is (%f, %f), acceleration is (%f, %f)\n", 
			object->name, object->x, object->y, object->vx, object->vy, object->ax, object->ay);
		MsgInsert(str);
		timeSpan = 0;
	}
}