//Engine.h
#pragma once

#include <string>

#include "Player.h"
#include "Bullet.h"
#include "Asteroids.h"
#include "Audio.h"

class Engine
{
public:
	Engine(sf::RenderWindow &win,bool b);
	~Engine(void);

	void runEngine();

private:
	sf::RenderWindow *window;
	
	Player player;
	Bullet bullets_player;
	Asteroids asteroids;
	Audio audio;

	void update();
	void draw();

	void collision();
	bool check_collision(Vector2f *A,int sizeA,
		Vector2f *B, int SizeB, Vector2f &offset);

	size_t nr_fali;
	size_t liczba_asteroid;
	
	sf::Clock czas_fali;
	sf::Clock czas_gry;

	//[0]zycia,[1]czas gry,[2]ammo,[3]czas bonusu
	sf::Text napis[4];
	sf::Font font;

	std::string str_napis[4];
};

