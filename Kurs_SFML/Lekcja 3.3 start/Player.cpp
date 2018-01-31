//Player.cpp
#include "Player.h"
#include <Windows.h>
#define M_PI 3.14159265358979323846

using namespace sf;

Player::Player(void)
{
	shape.setPointCount(4);

	shape.setPoint(0, sf::Vector2f(30, 40));
	shape.setPoint(1, sf::Vector2f(40, 60));
	shape.setPoint(2, sf::Vector2f(30, 30));
	shape.setPoint(3, sf::Vector2f(20, 60));

	shape.setOrigin(30,40);
	shape.setPosition(50,100);

	speed = 0;

	vx = 0;
	vy = 0;

	shooting = false;
}


Player::~Player(void)
{
}


sf::Vector2f Player::getPosition(size_t index)
{
	return shape.getPoint(index);
}


Player::Status Player::getStatus()
{
	return status;
}


void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(shape);
}


void Player::update() //5
{
	float angle = shape.getRotation();
	
	vx = sin(( angle * M_PI ) / 180.0f );
	vy = cos(( angle * M_PI ) / 180.0f );
	
	shape.move(vx*speed,vy*(-speed));
}


void Player::playAnimation(bool play)
{

}


void Player::accelerate()
{
	if(speed < max_speed)
	{
		speed += 0.5;
	}
}


void Player::rotate(int angle)
{
	shape.rotate(angle);
}


void Player::setVelocity(int x,int y)
{
	vx = x;
	vy = y;
}


sf::Vector2f Player::getNextPosition()
{
	return Vector2f(getPosition(2).x+vx,getPosition(2).y+vy);
}