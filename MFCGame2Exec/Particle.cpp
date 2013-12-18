
#include"stdafx.h"
#include "Particle.h"
#include "Utils.h"

Particle::Particle(int number)
{
	m_number = number;
	m_pSnow = new struct Snow[number];
}

Particle::~Particle()
{
	delete[] m_pSnow;
}

void Particle::Init()
{
	char buf[20];
	for (int i = 0; i < 7; i++)
	{
		sprintf(buf, "res\\Snow\\%d.png", i);
		m_snowMap[i].Load(buf);
		TransparentPNG(&m_snowMap[i]);
	}

	for(int i = 0; i < m_number; i++)
	{
		m_pSnow[i].x = rand() % WINDOW_WIDTH;
		m_pSnow[i].y = rand() % WINDOW_HEIGHT;
		m_pSnow[i].number = rand() % 7;
		m_pSnow[i].speed = (rand() % 5 + 1)/20.f;
	}
}

void Particle::Draw(CDC &cDC)
{
	for (int i = 0; i < m_number; i++)
	{
		m_snowMap[m_pSnow[i].number].Draw(cDC, m_pSnow[i].x, m_pSnow[i].y, 32, 32);
	}
}

bool Particle::Update(float time)
{
	for(int i = 0; i < m_number; i++)
	{
		m_pSnow[i].y += time * m_pSnow[i].speed;
		if (m_pSnow[i].y > WINDOW_HEIGHT)
		{
			m_pSnow[i].y = -32;
		}
	}
	return true;
}