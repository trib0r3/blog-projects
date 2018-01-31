//Engine.cpp
#include "Engine.h"
#include <Windows.h>
#include <iostream>

using namespace sf;

void getInterval(const Vector2f *axVertices,int numVert, const Vector2f &xAxis,
	float &min, float &max)
{
	min = max = (axVertices[0].x * xAxis.x + axVertices[0].y * xAxis.y);

	for(int i=1;i<numVert;i++)
	{
		float d=(axVertices[i].x * xAxis.x + axVertices[i].y * xAxis.y);
		
		if(d<min) min = d;
		else if(d>max) max = d;
	}
}


bool IntervalIntersect(const Vector2f *A,int Anum,const Vector2f *B,int Bnum,
	const Vector2f &xAxis, const Vector2f &offset)
{
	float min0,max0;
	float min1,max1;

	getInterval(A,Anum,xAxis,min0,max0);
	getInterval(B,Bnum,xAxis,min1,max1);

	float h = offset.x * xAxis.x + offset.y*xAxis.y;
	min0 += h;
	max0 += h;

	float d0 = min0 - max1;
	float d1 = min1 - max0;

	if(d0 > 0.0f || d1 > 0.0f)
		return false;
	else
		return true;
}


bool pointInside(Vector2f point, Vector2f *vertices, int size)
{
	int i, j = 0;
	bool oddNODES = false;
	for (i = 0; i < size; i++)
	{
		j++;
		if (j == size)
			j = 0;
		if (vertices[i].y < point.y && vertices[j].y >= point.y || vertices[j].y < point.y && vertices[i].y >= point.y)
		{
			if (vertices[i].x + (point.y - vertices[i].y) / (vertices[j].y - vertices[i].y) *
				(vertices[j].x - vertices[i].x) < point.x)
			{
				oddNODES = !oddNODES;
			}
		}
	}
	return oddNODES;
}

//---------------------------------------

Engine::Engine(sf::RenderWindow &win)
{
	window = &win;
	window->setMouseCursorVisible(false);

	bullets_player = Bullet(false);
}


Engine::~Engine(void)
{
	window->setMouseCursorVisible(true);
}


void Engine::runEngine()
{
	bool menu = false;

	sf::Clock zegar;
	asteroids.generate(1,500,500);
	
	while(!menu)
	{
		Event event;
		Vector2f mouse(Mouse::getPosition());
		if(Keyboard::isKeyPressed(Keyboard::Left))
		{
				player.rotate(-5);
		}

		else if(Keyboard::isKeyPressed(Keyboard::Right))
		{
			player.rotate(5);
		}

		else if(Keyboard::isKeyPressed(Keyboard::Up))
		{
			player.accelerate();
		}

		if(Keyboard::isKeyPressed(Keyboard::LControl))
		{
			bullets_player.add(player.getAngle(),player.getPosition(2));
		}
		
		while(window->pollEvent(event))
		{
			if(Keyboard::isKeyPressed(Keyboard::Escape))
			{
				menu = true;
			}
		}
		
		update();
		draw();
	}
}


void Engine::update()
{
	player.update();
	bullets_player.update();
	asteroids.update();

	//sprawdzenie asteroid
	if(!asteroids.isEmpty())
	{
		Vector2f A[3] = {player.getPosition(1),player.getPosition(2),player.getPosition(3)};
		
		int numAsteroid = 0;
		while(numAsteroid < asteroids.getSize())
		{
			Vector2f *B = new Vector2f[asteroids.getSize(numAsteroid)];

			for(int i=0;i<asteroids.getSize(numAsteroid);i++)
				B[i] = asteroids.getPoint(numAsteroid,i);
	
			bool collision;
		
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<asteroids.getSize(numAsteroid);j++)
				{
					collision=(check_collision(A,3,B,asteroids.getSize(numAsteroid),A[i]-B[j]));
					if(collision)
					{
						break;
					}
				}
				if(collision)
				{
					asteroids.del(numAsteroid); 
					break;
				}
			}

			delete []B;
			numAsteroid++;
		}
	}
	//sprawdzenie pocisków
	if(!bullets_player.isEmpty())
	{
		for(int i=0;i<bullets_player.getSize();i++)
		{
			for(int j=0;j<asteroids.getSize();j++)
			{
				Vector2f *vert = new Vector2f[asteroids.getSize(j)];
				for(int k=0;k<asteroids.getSize(j);k++)
				{
					vert[k] = asteroids.getPoint(j,k);
				}
				
				bool czy_w_polygonie = pointInside(bullets_player.getPoint(i),vert,asteroids.getSize(j));

				if(czy_w_polygonie)
				{
					asteroids.del(j);
					bullets_player.remove(i);
				}
				delete []vert;
			}//for
		}//for
	}//if
}


void Engine::draw()
{
	window->clear();	
	
	window->draw(player);
	window->draw(bullets_player);
	window->draw(asteroids);
		
	window->display();
}


bool Engine::check_collision(Vector2f *A,int sizeA,
	Vector2f *B, int sizeB, Vector2f &offset)
{
	if(!A || !B) return false;

	Vector2f xAxis[64];
	int iNumAxes = 0;

	//test dla A
	for(int j=sizeA-1,i=0;i<sizeA;j=i,i++)
	{
		Vector2f E0 = A[j];
		Vector2f E1 = A[i];
		Vector2f E = E1-E0;

		xAxis[iNumAxes] = Vector2f(-E.y,E.x);

		if(!IntervalIntersect(A,sizeA,B,sizeB,xAxis[iNumAxes],offset))
			return false;

		iNumAxes++;
	}

	//test dla B
	for(int j=sizeB-1,i=0;i<sizeB;j=i,i++)
	{
		Vector2f E0 = B[j];
		Vector2f E1 = B[i];
		Vector2f E = E1-E0;
		xAxis[iNumAxes] = Vector2f(-E.y,E.x);

		if(!IntervalIntersect(A,sizeA,B,sizeB,xAxis[iNumAxes],offset))
			return false;

		iNumAxes++;
	}

	return true;
}