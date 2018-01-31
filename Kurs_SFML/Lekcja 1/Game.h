#pragma once

#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>

using namespace std;
using namespace sf;

class Game
{
public:
	Game(void);
	~Game(void);

	void runGame();

protected:
	enum GameState {MENU,GAME,GAME_OVER,END};
	GameState state;

private:
	Font font;
	
	
	void menu();
};

