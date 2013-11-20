
// ChildView.h : CChildView ��Ľӿ�
//
#define SNOW_NUMBER 100

#include "mmsystem.h"
#pragma comment(lib, "winmm.lib")

#pragma once

struct charcter
{
	CImage image;
	int x;
	int y;
	int direct;
	int frame;
	int width;
	int height;
	int xCenter;
	int yCenter;
	char* name;
};

struct sSnow
{
	int x;
	int y;
	int number;
};

// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:
	charcter mHero, mMonster;
	//sSnow Snow[SNOW_NUMBER];
	CRect m_client;
	
	CImage m_bgBitmap;
	//������
	CDC mCacheDC;
	CBitmap mCacheCBitmap;
	//������ end
	//CImage mSnowMap[7];
	//int mXMapStart;
	//int mMapWidth;

// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();

	void GetMapStartX();
};

