//Engine.h
#pragma once

#include "Player.h"

class Engine
{
public:
	Engine(sf::RenderWindow &win);
	~Engine(void);

	void runEngine();

private:
	sf::RenderWindow *window;
	
	Player player;

	void update();
	void draw();
};

