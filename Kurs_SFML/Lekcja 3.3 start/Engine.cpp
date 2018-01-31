//Engine.cpp
#include "Engine.h"
#include <Windows.h>

using namespace sf;

Engine::Engine(sf::RenderWindow &win)
{
	window = &win;
}


Engine::~Engine(void)
{
}


void Engine::runEngine()
{
	bool menu = false;

	sf::Clock zegar;
	
	while(!menu)
	{
		Event event;
		Vector2f mouse(Mouse::getPosition());

		while(window->pollEvent(event))
		{
			if(Keyboard::isKeyPressed(Keyboard::Escape))
			{
				menu = true;
			}

			if(Keyboard::isKeyPressed(Keyboard::Left))
			{
				player.rotate(-5);
			}

			else if(Keyboard::isKeyPressed(Keyboard::Right))
			{
				player.rotate(5);
			}

			if(Keyboard::isKeyPressed(Keyboard::Up))
			{
				player.accelerate();
			}
		}
		
		update();
		draw();
	}
}


void Engine::update()
{
	player.update();
}


void Engine::draw()
{
	window->clear();	
	
	window->draw(player);
		
	window->display();
}