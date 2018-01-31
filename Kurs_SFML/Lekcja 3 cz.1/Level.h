/*
Level.h

Poradnik: Piszemy grê w SFML'u
Nazwa: Mechanized Techno Explorer

Autor: Szymon Siarkiewicz (sheadovas)
http://szymonsiarkiewicz.pl/

*/

#pragma once
#include <fstream>
#include <string>

class Level
{
public:
	
	//funkcje skladowe klasy
	Level();
	Level(std::string filename);

	void loadFromFile(std::string filename);
	
	~Level(void);
	 
	//"podklasy"
	enum FieldType {
		NONE,
		STONE,
		DIRT,
		COUNT};
	
	struct Tile
	{
		FieldType type;
		bool isWall;
	};
	
	
	//zmienne
	const static int width = 32;
	const static int height = 18;

	const static int tile_width = 40;
	const static int tile_height = 40;

	Tile poziom[height][width];
};