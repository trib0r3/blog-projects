//Asteroids.cpp
#define M_PI 3.14159265358979323846
#include "Asteroids.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

Asteroids::Asteroids(bool can)
{
	can_hurt_player = can;
}


Asteroids::~Asteroids(void)
{
}


void Asteroids::setColor(Color c)
{
	m_color = c;
}


void Asteroids::draw(RenderTarget &target, RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = NULL;
	
	for(int i=0;i<m_asteroids.size();i++)
	{
		target.draw(m_asteroids[i].shape,states);
	}
}


void Asteroids::generate(int ile,int x, int y)
{
	srand(time(NULL));

	for(int i=0;i<ile;i++)
	{
		Asteroid ast;
		ast.big = false;

		if(x==0 && y==0)
		{
			if(rand()%10>4)ast.big=true; else ast.big=false;

			x = rand()%1280+5;
			y = rand()%720+5;
		}
		int radius = 40;
		if(ast.big) radius*=1.5;

		//generowanie figury
		ConvexShape shape;
		shape.setPointCount((rand()%3)+5);

		int size = shape.getPointCount();
		
		for(int j=0;j<size;j++)
		{
			float alpha = rand()%(360/size)+j*(360/size);
			alpha=(alpha*M_PI)/180;
			shape.setPoint(j,Vector2f(x+cos(alpha)*radius,y+sin(alpha)*radius));
		}
		shape.setOrigin(shape.getPoint(0));
		
		shape.setOutlineColor(Color::White);
		shape.setFillColor(Color::Transparent);
		
		shape.setOutlineThickness(1);
		shape.setPosition(x,y);

		ast.shape = shape;
		
		//ustawianie prêdkoœci
		float vx,vy;

		vx = (rand()%4-2)/2.f;
		vy = (rand()%4-2)/2.f;

		//
		ast.speed = Vector2f(0,0);////////////////////

		m_asteroids.push_back(ast);
	}
}


void Asteroids::del(int it)
{
	for(int i=it;i<m_asteroids.size()-1;i++)
	{
		std::swap(m_asteroids[i],m_asteroids[i+1]);
	}

	m_asteroids.resize(m_asteroids.size()-1);
}


void Asteroids::update()
{
	//usuwanie
	for(int i=0;i<m_asteroids.size();i++)
	{
		Vector2f pos = m_asteroids[i].shape.getPosition();
		if(pos.x > 1290 || pos.x < -10 || pos.y > 730 || pos.y < -10)
			del(i);
	}

	//ruch jednostajny
	for(int i=0;i<m_asteroids.size();i++)
	{
		m_asteroids[i].shape.move(m_asteroids[i].speed);
	}
}


Vector2f Asteroids::getPoint(int i,int it)
{
	return m_asteroids[i].shape.getTransform().transformPoint(m_asteroids[i].shape.getPoint(it));
}


int Asteroids::getSize()
{
	return m_asteroids.size();
}


int Asteroids::getSize(int index)
{
	return m_asteroids[index].shape.getPointCount();
}


bool Asteroids::isEmpty()
{
	return m_asteroids.empty();
}