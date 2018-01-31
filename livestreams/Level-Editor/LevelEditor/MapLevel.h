#pragma once
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>

class MapLevel
{
public:
	std::vector< std::vector < int > > level_data; // level_data[3][1]

	MapLevel();

	bool LoadFromFile(std::string path);
	bool SaveToFile(std::string path);

	int width, height;
};

