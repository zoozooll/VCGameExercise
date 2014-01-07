#include "stdafx.h"
#pragma once

class MovableObject	// A type is an object that can move
{
public:
	MovableObject(char* name, char* imagPath);
	~MovableObject(void);


private :
	char *imagPath;
	

public:
	char *name;
	CImage image;
	int x, y; // the current site (x, y)
	float vx, vy; // The current speed in x, y arrow;
	float ax, ay; // The current acceleration speed in x ,y arrow

public:
	void InitializeSite(const int &x, const int &y, const float &vx, const float &vy, const float &ax, const float &ay);
	bool onMovie(const int &);
};

