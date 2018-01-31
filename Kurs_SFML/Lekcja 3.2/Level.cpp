/*
Level.cpp

Poradnik: Piszemy grê w SFML'u
Nazwa: Mechanized Techno Explorer

Autor: Szymon Siarkiewicz (sheadovas)
http://szymonsiarkiewicz.pl/

*/

#include "Level.h"
#include <iostream>

using namespace std;

Level::Level(void)
{
	
}

Level::Level(std::string filename)
{
	loadFromFile(filename);
}


Level::~Level(void)
{
}

void Level::loadFromFile(std::string filename)
{
	fstream file;
	file.open("data/levels/"+filename, std::ios::in);

	if(!file.is_open()) 
		std::cout<<"Nie znaleziono poziomu: "+filename;
	else
	{
		for(int y=0;y<height;y++)
			for(int x=0;x<width;x++)
			{
				int tmp;
				file>>tmp;
				poziom[y][x].type = FieldType(tmp);
			
				if(tmp==0)
					poziom[y][x].isWall = false;
				else
					poziom[y][x].isWall = true;
			}
	}
	
	file.close();
}