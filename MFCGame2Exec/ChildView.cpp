
// ChildView.cpp : CChildView ���ʵ��
//

#include "stdafx.h"
#include "MFCGame2Exec.h"
#include "Utils.h"
#include "ChildView.h"
#include <windows.h>
#include <stdio.h>
#include <math.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMER_PAINT 1
#define TIMER_HEROMOVE 2

#define DOWN 0
#define LEFT 1
#define RIGHT 2
#define UP 3


static int GetScreenX(int xHero, int mapWidth) 
{
	if (xHero < mapWidth - WINDOW_WIDTH/2 && xHero > WINDOW_WIDTH/2)
	{
		return WINDOW_WIDTH/2;
	} 
	else if (xHero <= WINDOW_WIDTH/2) 
	{
		return xHero;
	}
	else
	{
		return WINDOW_WIDTH - mapWidth + xHero;
	}
}

static void monsterMoving(charcter *hero, charcter *monster)
{
	if (monster->x < hero->x)
	{
		monster->x ++;
		monster->direct = RIGHT;
	}
	else if (monster->x > hero->x)
	{
		monster->x --;
		monster->direct = LEFT;
	}
	if (monster->y < hero->y)
	{
		monster->y ++;
		monster->direct = DOWN;
	}
	else if (monster->y > hero->y) 
	{
		monster->y --;
		monster->direct = UP;
	}
}

static bool isHit(const charcter *hero, const charcter *monster)
{
	int xHeroCenter = hero->x + hero->width /2;
	int yHeroCenter = hero->y + hero->height /2;
	int xMonsterCenter = monster->x + monster->width/2;
	int yMonsterCenter = monster->y + monster->height/2;
	if (pow(xHeroCenter- xMonsterCenter, 2.0) + pow (yHeroCenter - yMonsterCenter, 2.0) < 500.0)
	{
		return TRUE;
	} 
	return FALSE;
}


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
	mciSendString("stop bgMusic ", NULL, 0, NULL);
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()



// CChildView ��Ϣ�������

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
    char str[250] = "Aaron lee PreCreateWindow";
    OutputDebugString(str);


	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	//����Ӣ�۳�ʼλ��  
    mHero.x =80;    //�����������80��λ��  
    mHero.y =400;  
	mHero.width = 80;
	mHero.height = 80;

	//���ù���;
	mMonster.width = 96;
	mMonster.height = 96;
	mMonster.direct = 96;
	mMonster.frame = 0;
	mMonster.x = 700;
	mMonster.y = 100;
	mMonster.image.Load("res\\monster.png");
	TransparentPNG(&mMonster.image);

	m_bgBitmap.Load("res\\bg.png");

	//mMapWidth = m_bgBitmap.GetWidth();

	mHero.frame = 0;
	mHero.direct = RIGHT;
	mHero.image.Load("res\\heroMove.png");
	TransparentPNG(&(mHero.image));

	// ����ѩ����ͼƬ��
	//char buf[20];
	//cimage *psnowimage = msnowmap;
	//for(int i = 0; i < 7; i ++) 
	//{ 
	//	sprintf(buf, "res/snow/%d.png", i);
	//	psnowimage->load(buf);
	//	transparentpng(psnowimage);
	//	psnowimage ++;
	//}

	//ssnow *psnowmodel = snow;
	//for (int i = 0; i < snow_number; i++)
	//{
	//	psnowmodel->x = rand() % window_width;
	//	psnowmodel->y = rand() % window_height;
	//	psnowmodel->number = rand() % 7;
	//	psnowmodel++;
	//}
	//mxmapstart = 0;
	m_snow = new Particle(100);
	m_snow->Init();
	// ���ű�������
	//mciSendString("open res\\background.mp3 alias bgMusic ", NULL, 0, NULL);
	//mciSendString("play bgMusic repeat", NULL, 0, NULL);
	return TRUE;
}

void CChildView::OnPaint() 
{
	static long lastTime = timeGetTime();
	static long currentTime;
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	
	CDC *p_dc = this->GetDC();
	GetClientRect(&m_client);
	// ������
	mCacheDC.CreateCompatibleDC(NULL);
	mCacheCBitmap.CreateCompatibleBitmap(p_dc, m_client.Width(), m_client.Height());
	mCacheDC.SelectObject(&mCacheCBitmap);
	// ������������

	GetMapStartX();

	 //������  
	//m_bgBitmap.Draw(mCacheDC,0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, mXMapStart, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	m_bgBitmap.Draw(mCacheDC,0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	// ������
	/*MyHero.image.Draw(mCacheDC, GetScreenX(MyHero.x, mMapWidth), MyHero.y, 80, 80,
		MyHero.frame * 80, MyHero.direct*80, 80, 80);*/
	mHero.image.Draw(mCacheDC, mHero.x, mHero.y, 80, 80,
		mHero.frame * 80, mHero.direct*80, 80, 80);
	mMonster.image.Draw(mCacheDC, mMonster.x, mMonster.y, 96, 96,
		mMonster.frame * 96, mMonster.direct *96, 96, 96);

	mHero.xCenter = mHero.x + mHero.width / 2;
	mHero.yCenter = mHero.y + mHero.height /2;
	//��ѩ��;
	/*sSnow *pSnow = Snow;
	for (int i = 0; i < SNOW_NUMBER; i++)
	{
		mSnowMap[pSnow->number].Draw(mCacheDC, pSnow->x, pSnow->y, 32, 32);
		Snow[i].y ++;
		if (pSnow->y >= WINDOW_HEIGHT)
		{
			pSnow->y = 0;
		}
		pSnow ++;
	}*/
	m_snow->Draw(mCacheDC);
	currentTime = timeGetTime();
	m_snow->Update(currentTime - lastTime);
	lastTime = currentTime;


	monsterMoving(&mHero, &mMonster); 

	// �������֣�
	if (isHit(&mMonster, &mHero))
	{
		mCacheDC.SetBkMode(TRANSPARENT);
		mCacheDC.SetTextColor(RGB(255,0,0));
		mCacheDC.TextOutA(0, 0, "hiting");
	}

	p_dc->BitBlt(0, 0, m_client.Width(), m_client.Height(), &mCacheDC, 0, 0, SRCCOPY);
	
	// ����������ͼ���ͷţ�
	ValidateRect(&m_client);
	mCacheDC.DeleteDC();
	mCacheCBitmap.DeleteObject();
	ReleaseDC(p_dc);	//release the CDC object;
	
	// ��ҪΪ������Ϣ������ CWnd::OnPaint()
}



void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch(nChar)
	{
	case 'd':
	case 'D':
	{
		mHero.x += 10;
		mHero.direct = RIGHT;
		break;
	}
		
	case 'a':
	case 'A':
	{
		mHero.x -= 10;
		mHero.direct = LEFT;
		break;
	}
	case 'w':
	case 'W':
	{
		mHero.y -= 10;
		mHero.direct = UP;
		break;
	}
		
	case 's':
	case 'S':
	{
		mHero.y += 10;
		mHero.direct = DOWN;
		break;
	}
		
	default:
		break;
	}
}

void CChildView::OnTimer(UINT_PTR nIDEvent) 
{
	switch (nIDEvent)
	{
	case TIMER_PAINT:
		OnPaint();
		break;
	case TIMER_HEROMOVE:
		mHero.frame ++;
		mHero.frame = mHero.frame % 4;
		mMonster.frame ++;
		mMonster.frame = mHero.frame % 4;
		break;
	}
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	SetTimer(TIMER_PAINT, 10, NULL);
	SetTimer(TIMER_HEROMOVE, 100, NULL);
	return 0;
}

void CChildView::OnClose()
{
	KillTimer(TIMER_PAINT);
}



void CChildView::GetMapStartX()
{
	/*if(mHero.x < mMapWidth - WINDOW_WIDTH/2 && mHero.x >  WINDOW_WIDTH/2)
	{
		mXMapStart = MyHero.x - WINDOW_WIDTH/2;
	}*/
}