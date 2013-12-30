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
	int atk; // attack ������
	int speed;
public:
	CImage image;	//ͼƬ
	RECT rect;   // λ���Լ����
public:
	void Initalize(const int &maxHP, const char* imagePath, const int &atkPoint, const int &x, const int &y, const int &width, const int &height, const int &speed);
	int Attacking(void);	//��������;����Ϊ����Ĺ�������
	int UnderAccacked(const int &);	//�ܵ�����,����Ϊ�ܵ���ԭʼ�����������������˺�Ӧ�ø��ݷ����Լ�״̬����Ϣ�ж���
	void Move(const int &millisSpan);	//�ƶ�
	bool isDead();
	void getHpString(char* destStr);
};

