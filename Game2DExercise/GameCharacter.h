#include "stdafx.h";
#pragma once

class GameCharacter
{

public:
	GameCharacter(void);
	~GameCharacter(void);
private:
	int nHp;
	int fHp;
	int lv;
	int atk; // attack 攻击力
	int speed;
public:
	CImage image;	//图片
	RECT rect;   // 位置以及宽高
public:
	void Initalize(const int &maxHP, const char* imagePath, const int &atkPoint, const int &x, const int &y, const int &width, const int &height, const int &speed);
	int Attacking(void);	//发动攻击;参数为输出的攻击参数
	int UnderAccacked(const int &);	//受到攻击,参数为受到的原始攻击参数，真正的伤害应该根据防御以及状态等信息判定；
	void Move(const int &millisSpan);	//移动
	bool isDead();
	void getHpString(char* destStr);
};

