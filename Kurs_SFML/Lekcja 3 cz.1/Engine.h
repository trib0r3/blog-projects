/*
Engine.h

Poradnik: Piszemy grê w SFML'u
Nazwa: Mechanized Techno Explorer

Autor: Szymon Siarkiewicz (sheadovas)
http://szymonsiarkiewicz.pl/

*/

#pragma once

#include "Player.h"
#include "Level.h"

class Engine
{
public:
	Engine(sf::RenderWindow &win);
	~Engine(void);

	void runEngine(sf::RenderWindow &window);

private:
	Player player;
	Level level; //poziom gry

	sf::Texture tekstura[Level::COUNT]; //tekstury kafli
	sf::Sprite sprite[Level::height][Level::width]; //poziom widziany przez gracza
};