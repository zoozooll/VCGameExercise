#include "WinMain.h"

static void LoadImages()
{
	m_ImgBg.Load("bg.png");
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
	hWnd = CreateWindow("Game2DExercise", "�غ�����Ϸ", WS_OVERLAPPEDWINDOW,
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

	// Load all images;
	LoadImages();

	// initalize all charactors
	InitializeCharactors();

	txtNum = 0;
	SetBkMode(m_hdcCache, TRANSPARENT);
	
	MyPaint(m_hdc);

	return TRUE;
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
		//��ҶԹ�����й�����ʱ��
		damage = m_monster.UnderAccacked(m_player.Attacking());
		DrawImages(100, 160, false);
		sprintf(str, "�Թ��������%d���˺�", damage);
		MsgInsert(str);

		over = m_monster.isDead();
		break;
	case 26:
		DrawImages(480, 150, true);
		break;
	case 30:
		//�������ҽ��й�����ʱ��
		damage = m_player.UnderAccacked(m_monster.Attacking());
		DrawImages(480, 160, false);
		sprintf(str, "����������%d���˺�", damage);
		MsgInsert(str);
		over = m_player.isDead();
		break;
	}
}

static void Attricking(const int &millisSpan)
{
	
	static int beats = 0;   //����;
	static int preMillis;	//��һ������ʱ����millisΪ��λ
	f++;
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


void MyPaint(HDC hdc)
{
	//char log[100];
	int millisSpan = tNow - tPre; // ����frame֮���ʱ��
	//sprintf(log, "mypaint %d \n", millisSpan);
	//OutputDebugString(log);

	//m_ImgBg.Draw(m_hdcCache, 0, 0, 640, 510,0, 0, m_ImgBg.GetWidth(), m_ImgBg.GetHeight());
	DrawImage(m_ImgBg, m_hdcCache, 0, 0);

	//��ս��Ϣ
	for (int i = 0; i < txtNum; i++)
	{
		TextOut(m_hdcCache, 0, 360 + i *18, text[i], strlen(text[i]));
	}
	DrawMonster();
	DrawPlayer();
	DrawMagicSpell();

	if (over)	//��Ϸ����ʱ��Ķ���
	{
		//m_ImgGameover.Draw(m_hdcCache, 200, 200, m_ImgGameover.GetWidth(), m_ImgGameover.GetHeight(),0, 0, m_ImgGameover.GetWidth(), m_ImgGameover.GetHeight());
		DrawImage(m_ImgGameover, m_hdcCache, 200, 200);
	} 
	else if (!attack)	//��ѡ�񹥻�ʱ���״̬ ����ѡ���������ͼ��
	{
		//m_ImgSkill.Draw(m_hdcCache, 500, 350, m_ImgSkill.GetWidth(), m_ImgSkill.GetHeight(),0, 0, m_ImgSkill.GetWidth(), m_ImgSkill.GetHeight());
		//m_ImgSkillult.Draw(m_hdcCache, 430, 350, m_ImgSkillult.GetWidth(), m_ImgSkillult.GetHeight(),0, 0, m_ImgSkillult.GetWidth(), m_ImgSkillult.GetHeight());
		DrawImage(m_ImgSkill, m_hdcCache, 500, 350);
		DrawImage(m_ImgSkillult, m_hdcCache, 430, 350);
	}
	else	//��ѡ���˹���״̬֮�󣬻��Զ�����һЩ�����������Լ����ﻹ����
	{
		Attricking(millisSpan);
	}
	
	BitBlt(m_hdc, 0, 0, 640, 510, m_hdcCache, 0, 0, SRCCOPY);

	tPre = GetTickCount();
	
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

// WPARAM wParam ����Ϊ�ж��ĸ�����
static LRESULT CALLBACK OnKeyDown(HWND hWnd, WPARAM wParam) 
{
	//�жϰ������������  
	//switch (wParam)   
	//{  
	//	case VK_ESCAPE:           //���¡�Esc����  
	//		PostQuitMessage( 0 );  //��������  
	//		break;  
	//	case VK_UP:               //���¡�������  
	//		//�Ȱ���Ŀǰ���ƶ�������������ͼ�������������������������ƶ�������ÿ�ΰ���һ�ΰ����ƶ�10����λ����������������ͼ�����X��Yֵ�������ж������Ƿ񳬳����������������ٴ�����  
	//		switch(dir)  
	//		{  
	//			case 0:   
	//				y -= 10;  
	//				break;  
	//			case 1:  
	//				x -= 1;  
	//				y -= 8;  
	//				break;  
	//			case 2:   
	//				x += 2;  
	//				y -= 10;  
	//				break;  
	//			case 3:  
	//				x += 2;  
	//				y -= 10;  
	//				break;  
	//		}  
	//		if(y < 0)  
	//			y = 0;  
	//		dir = 0;  
	//		break;  
	//	case VK_DOWN:             //���¡�������  
	//		switch(dir)  
	//		{  
	//			case 0:  
	//				x += 1;  
	//				y += 8;  
	//				break;  
	//			case 1:  
	//				y += 10;  
	//				break;  
	//			case 2:  
	//				x += 3;  
	//				y += 6;  
	//				break;  
	//			case 3:  
	//				x += 3;  
	//				y += 6;  
	//				break;  
	//		}  

	//		if(y > 375)  
	//			y = 375;  
	//		dir = 1;  
	//		break;  
	//	case VK_LEFT:             //���¡�������  
	//		switch(dir)  
	//		{  
	//			case 0:  
	//				x -= 12;  
	//				break;  
	//			case 1:  
	//				x -= 13;  
	//				y += 4;  
	//				break;  
	//			case 2:  
	//				x -= 10;  
	//				break;  
	//			case 3:  
	//				x -= 10;  
	//				break;  
	//		}  
	//		if(x < 0)  
	//			x = 0;  
	//		dir = 2;  
	//		break;  
	//	case VK_RIGHT:             //���¡�������  
	//		switch(dir)  
	//		{  
	//			case 0:  
	//				x += 8;  
	//				break;  
	//			case 1:  
	//				x += 7;  
	//				y += 4;  
	//				break;  
	//			case 2:  
	//				x += 10;  
	//				break;  
	//			case 3:  
	//				x += 10;  
	//				break;  
	//		}  
	//		if(x > 575)  
	//			x = 575;  
	//		dir = 3;  
	//		break;  
	//}  

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)  
	 {  
		 case WM_KEYDOWN:         //���¼�����Ϣ  
			 return  OnKeyDown(hWnd, wParam);
		 case WM_LBUTTONDOWN:
			 if (!attack)
			 {
				 int x = LOWORD(lParam);
				 int y = HIWORD(lParam);
				 if (x >= 500 && x <= 550 && y >=350 && y <=440)
					 attack = true;
			 }
			 break;
		 case WM_DESTROY:                    //���ڽ�����Ϣ  
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
		 default:                            //������Ϣ  
			 return DefWindowProc(hWnd, message, wParam, lParam);  
	}  
	return 0;  

}