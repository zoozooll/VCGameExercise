
// ChildView.h : CChildView 类的接口
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

// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 特性
public:
	charcter mHero, mMonster;
	//sSnow Snow[SNOW_NUMBER];
	CRect m_client;
	
	CImage m_bgBitmap;
	//缓存区
	CDC mCacheDC;
	CBitmap mCacheCBitmap;
	//缓存区 end
	//CImage mSnowMap[7];
	//int mXMapStart;
	//int mMapWidth;

// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
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

