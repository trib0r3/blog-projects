#include "MapLevel.h"

MapLevel::MapLevel()
{
	width = height = 0;
}

bool MapLevel::LoadFromFile(std::string path)
{
	std::fstream file(path, std::ios::in);

	if (!file.is_open())
	{
		fprintf(stderr, "Cannot open level: %s\n", path.c_str());
		return false;
	}

	// load level width & height
	int w, h;
	file >> w >> h;

	if (w < 1 && h < 1)
	{
		fprintf(stderr, "Level width & height must be greater than 0\n");
		return false;
	}


	// resize level data
	level_data.clear();
	level_data.resize(h);
	for (int i = 0; i < h; ++i)
	{
		level_data[i].resize(w);
	}

	// load level data
	int data;
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			file >> data;
			if (data < 0)
			{
				fprintf(stderr, "Error during parsing level data\n");
				level_data.clear();
				width = height = 0;
				return false;
			}

			level_data[y][x] = data;
		}
	}

	width = w;
	height = h;
	return true;
}

bool MapLevel::SaveToFile(std::string path)
{
	std::fstream file(path, std::ios::out | std::ios::trunc);

	// save width & height
	file << width << " " << height << "\n";

	// save level data
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			file << level_data[y][x] << " ";
		}
		file << "\n";
	}

	return true;
}
