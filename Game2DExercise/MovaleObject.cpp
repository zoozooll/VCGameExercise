#include "MovaleObject.h"


MovableObject::MovableObject(char* name, char* imagPath)
{
	this->name = name;
	this->imagPath = imagPath;
	
}


MovableObject::~MovableObject(void)
{
	image.Destroy();
}

void MovableObject::InitializeSite(const int &x, const int &y, const float &vx, const float &vy, const float &ax, const float &ay)
{
	image.Load(imagPath);
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	this->ax = ax;
	this->ay = ay;
}

bool MovableObject::onMovie(const int &deltaMillis)
{
	static float timespan;
	timespan += deltaMillis/1000.0f;
	if (timespan > 0.1f)
	{
		x += vx * timespan + (timespan * timespan * ax) * 0.5f;
		y += vy * timespan + (timespan * timespan * ay) * 0.5f;
		vx += ax * timespan;
		vy += ay * timespan;
		timespan = .0f;
		return true;
	}
	return false;
}