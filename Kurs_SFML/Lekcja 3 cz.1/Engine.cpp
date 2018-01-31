/*
Engine.cpp

Poradnik: Piszemy grê w SFML'u
Nazwa: Mechanized Techno Explorer

Autor: Szymon Siarkiewicz (sheadovas)
http://szymonsiarkiewicz.pl/

*/

#include "Engine.h"
#include <iostream>
using namespace sf;

Engine::Engine(sf::RenderWindow &win)
{
	//wczytanie tekstur
	for(int i=1;i<Level::COUNT;i++)
	{
		tekstura[i].loadFromFile("data/images/tiles.png",IntRect((i-1)*level.tile_width,0,level.tile_width,level.tile_height));
	}

	//ustawienie kafli
	level.loadFromFile("map.level");
	for(int i=0;i<level.height;i++)
	{
		for(int j=0;j<level.width;j++)
		{
			if(level.poziom[i][j].type != Level::NONE)
			{
				sprite[i][j].setTexture(tekstura[level.poziom[i][j].type]);
				sprite[i][j].setPosition(j*level.tile_width,i*level.tile_height);
			}
		}
	}
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

		//rysowanie poziomu
		for(int i=0;i<level.height;i++)
			for(int j=0;j<level.width;j++)
				if(level.poziom[i][j].type != Level::NONE)
					window.draw(sprite[i][j]);

		window.draw(player);
		window.display();
	}
}