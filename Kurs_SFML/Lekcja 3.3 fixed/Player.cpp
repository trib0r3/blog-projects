//Player.cpp
#include <iostream>
#include "Player.h"
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

	speed = 2;

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


void Player::update() 
{
	shape.move(vx,vy);

	vx = vx - vx * 0.02f;
    vy = vy - vy * 0.02f;
}


void Player::playAnimation(bool play)
{

}


void Player::accelerate()
{
	float angle = shape.getRotation();
	
	float xN = static_cast<float>(sin(speed * M_PI * (angle / 360)));
	float yN = static_cast<float>(cos(speed * M_PI * (angle / 360)));
	
	vx += xN * 0.2f;
	vy -= yN * 0.2f;
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