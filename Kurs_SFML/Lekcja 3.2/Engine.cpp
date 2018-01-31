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
		
		check_collision();
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


void Engine::check_collision()
{
	if(player.getStatus() == Player::STOJ) return;

	//pobranie aktualnej wartoœci boxa
	FloatRect box1(player.getBoundingBox());

	//zaktualizowanie go do wartoœci gdyby gracz siê ruszy³
	box1.left += (player.getSpeed().x)/10; //dzielimy na 10 aby bardziej  zbli¿yæ siê do œciany
	box1.top += (player.getSpeed().y)/10;

	/*
	Schemat sprawdzania naszego boxa z ponumerowanymi wierzcholkami
	1 ___ 2
	|     |
	3 ___ 4
	*/

	//1
	int x = box1.left/level.tile_width;
	int y = box1.top/level.tile_height;

	if(level.poziom[y][x].isWall && box1.intersects(sprite[y][x].getGlobalBounds()))
	{
		player.stop();
	}
	
	//2
	x = (box1.left+level.tile_width)/level.tile_width;
	y = box1.top/level.tile_height;
	if(level.poziom[y][x].isWall && box1.intersects(sprite[y][x].getGlobalBounds()))
	{
		player.stop();
	}

	//3
	x = (box1.left)/level.tile_width;
	y = (box1.top+level.tile_height)/level.tile_height;
	if(level.poziom[y][x].isWall && box1.intersects(sprite[y][x].getGlobalBounds()))
	{
		player.stop();
	}

	//4
	x = (box1.left+level.tile_width)/level.tile_width;
	y = (box1.top+level.tile_height)/level.tile_height;
	if(level.poziom[y][x].isWall && box1.intersects(sprite[y][x].getGlobalBounds()))
	{
		player.stop();
	}
}