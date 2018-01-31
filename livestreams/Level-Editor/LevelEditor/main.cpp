#include <SFML/Graphics.hpp>
#include <cstdio>
#include <vector>
#include "MapLevel.h"

#define TILE_SIZE 64

int main(int argc, char **argv)
{
	if (argc != 1)
	{
		fputs("Invalid amount of args!\n", stderr);
		return 1;
	}

	int scrn_width = 1280;
	int scrn_height = 720;

	// -----------
	MapLevel level;
	if (!level.LoadFromFile("level.txt"))
		return 1;

	fprintf(stdout, "%d %d\n", level.width, level.height);

	// level view & resize
	std::vector < std::vector < sf::Sprite> > level_view;
	level_view.resize(level.height);
	for (int i = 0; i < level.height; ++i)
	{
		level_view[i].resize(level.width);
	}

	// textures
	sf::Texture textures[2];
	textures[0].loadFromFile("tiles.png", sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
	textures[1].loadFromFile("tiles.png", sf::IntRect(64, 0, TILE_SIZE, TILE_SIZE));


	// assign tiles
	for (int i = 0; i < level.height; ++i)
	{
		for (int j = 0; j < level.width; ++j)
		{
			fprintf(stdout, "%d ", level.level_data[i][j]);
			level_view[i][j].setPosition(j*TILE_SIZE, i*TILE_SIZE);
			level_view[i][j].setTexture(
				textures[
					level.level_data[i][j]
				]);
		}
		fputs("\n", stdout);
	}
	// -----------

	sf::RenderWindow window(sf::VideoMode(scrn_width, scrn_height), "Level Editor", sf::Style::Close);

	bool active_tile = 0;
	bool exit = false;
	while (!exit)
	{
		sf::Event evnt;

		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				exit = true;
				continue;
			}

			if (evnt.type == sf::Event::MouseButtonReleased)
			{
				sf::Vector2i mouse(sf::Mouse::getPosition(window));
				int idx = mouse.x / TILE_SIZE;
				int idy = mouse.y / TILE_SIZE;

				if (idx < level.width  && idy < level.height)
				{
					level.level_data[idy][idx] = active_tile;
					level_view[idy][idx].setTexture(textures[active_tile]);
				}
			}

			if (evnt.type == sf::Event::KeyReleased &&
				evnt.key.code == sf::Keyboard::Space)
			{
				active_tile = !active_tile;
			}
		}

		window.clear();

		for (int i = 0; i < level.height; ++i)
		{
			for (int j = 0; j < level.width; ++j)
			{
				window.draw(level_view[i][j]);
			}
		}

		window.display();
	}
	level.SaveToFile("saved.txt");
	return 0;
}
