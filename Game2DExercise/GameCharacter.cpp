#include "GameCharacter.h"


GameCharacter::GameCharacter(void)
{
}


GameCharacter::~GameCharacter(void)
{
	//image.ReleaseDC();
}

void GameCharacter::Initalize(const int &maxHP, const char* imagePath, const int &atkPoint, const int &x, const int &y, const int &width, const int &height, const int &speed)
{
	nHp = maxHP;
	fHp = maxHP;
	image.Load(imagePath);
	atk = atkPoint;
	rect.left = x;
	rect.top = y;
	if (width > 0)
	{
		rect.right = x + width;
	}
	else
	{
		rect.right = x + image.GetWidth();
	}
	if (height > 0)
	{
		rect.bottom = y + height;
	}
	else 
	{
		rect.bottom = y + image.GetHeight();
	}
	this->speed = speed;
}

int GameCharacter::Attacking(void)
{
	if (!rand()%4)
	{
		return atk * 2;
	} else {
		return atk;
	}
}

int GameCharacter::UnderAccacked(const int &begingATK)
{
	int flag;
	if (!rand()%4)
	{
		flag = begingATK /  2;
	} else {
		flag = begingATK;
	}
	nHp -= flag;
	return flag;
}

bool GameCharacter::isDead()
{
	return nHp <= 0;
}

void GameCharacter::getHpString(char* destStr)
{
	sprintf(destStr, "%d/%d", nHp, fHp);
}
