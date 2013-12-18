#ifndef _PARTICLE_H
#define _PARTICLE_H

#include "stdafx.h" 

struct Snow
{
	float x;
	float y;
	float speed;
	int number;
};
class Particle
{
private:
	int m_number;
	struct Snow *m_pSnow;
	CImage m_snowMap[7];
public:
	Particle(int number);
	~Particle();
public:
	void Init();
	void Draw(CDC &);
	bool Update(float time);
};

#endif