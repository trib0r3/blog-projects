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

			if(rand()%2 == 0)
			{
				x = -5;
				y = rand()%720;
			}
			else
			{
				x = rand()%1280;
				y = -5;
			}

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

		if(vx==0) vx=1;
		if(vy==0) vy=-1;

		ast.speed = Vector2f(vx,vy);

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
	//wychodzenie poza krawedzie
	for(int i=0;i<m_asteroids.size();i++)
	{
		Vector2f pos = m_asteroids[i].shape.getPosition();
		
		//os x
		if(pos.x > 1295) //margines 15 pikseli
			m_asteroids[i].shape.setPosition(-10,pos.y);
		else if(pos.x < -15)
			m_asteroids[i].shape.setPosition(1290,pos.y);

		if(pos.y > 735)
			m_asteroids[i].shape.setPosition(pos.x,-10);
		else if(pos.y < -15)
			m_asteroids[i].shape.setPosition(pos.x,730);
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