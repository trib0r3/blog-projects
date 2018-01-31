/*
Engine.cpp

Poradnik: Piszemy grê w SFML'u
Nazwa: Mechanized Techno Explorer

Autor: Szymon Siarkiewicz (sheadovas)
http://szymonsiarkiewicz.pl/

*/

#include "Engine.h"
using namespace sf;

Engine::Engine(sf::RenderWindow &win)
{
	runEngine(win);
}


Engine::~Engine(void)
{
}

void Engine::runEngine(sf::RenderWindow &window)
{
	bool menu = false;
	
	while(!menu)
	{
		Event event;
		sf::Vector2f mysz(Mouse::getPosition(window));

		while(window.pollEvent(event))
		{
			if(event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
				menu = true;
			
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::W)
			{
				player.idz();
			}
			
			else if(event.type == Event::KeyReleased)
			{
				if(event.key.code == Keyboard::W)
					player.stop();
			}
		}
		
		player.update(mysz);
		
		window.clear();
		window.draw(player);
		window.display();
	}
}