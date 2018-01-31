/*
Player.h

Poradnik: Piszemy grê w SFML'u
Nazwa: Mechanized Techno Explorer

Autor: Szymon Siarkiewicz (sheadovas)
http://szymonsiarkiewicz.pl/

*/

#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

class Player: public sf::Drawable,
	sf::Transformable
{
public:
	Player(void);
	~Player(void);

	enum Status {
	IDZ,
	STOJ
	};

	sf::Vector2f getPosition();
	Status getStatus();

	sf::FloatRect getBoundingBox();
	sf::Vector2f getSpeed();

	void update(sf::Vector2f mysz);

	void stop();
	void idz();

private:
	sf::Sprite sprite;
	sf::Texture texture;

	Status status;

	float speed;
	size_t frame;

	sf::Clock anim_clock;
	
	virtual void draw(sf::RenderTarget &target,sf::RenderStates states) const;
};