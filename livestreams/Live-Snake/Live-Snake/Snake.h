#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <cmath>
#include "CollsionChecker.h"

class Snake : public sf::Drawable
{
public:
	enum Direction {
		DIR_UP, DIR_DOWN, DIR_LEFT = 3, DIR_RIGHT
	};

	Snake();
	~Snake();
	
	void Move();
	void ChangeDirection(Direction dir);
	void AddBodyPart();
	bool IsSelfBitting();
	sf::FloatRect& GetHeadFloatRect() const;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	std::vector <sf::RectangleShape> m_snakeParts;
	Direction m_direction;
};

