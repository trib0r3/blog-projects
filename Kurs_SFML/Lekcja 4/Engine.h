//Engine.h
#pragma once

#include "Player.h"
#include "Bullet.h"
#include "Asteroids.h"

class Engine
{
public:
	Engine(sf::RenderWindow &win);
	~Engine(void);

	void runEngine();

private:
	sf::RenderWindow *window;
	
	Player player;
	Bullet bullets_player;
	Asteroids asteroids;

	void update();
	void draw();

	bool check_collision(Vector2f *A,int sizeA,
		Vector2f *B, int SizeB, Vector2f &offset);
};

