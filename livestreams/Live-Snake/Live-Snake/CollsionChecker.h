#pragma once
#include <SFML\Graphics\Rect.hpp>
class CollsionChecker
{
public:
	static bool IsCollision(sf::FloatRect* o1, sf::FloatRect* o2);
};

