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

	status = STATUS_ALIVE;
	lifes = 3;

	special_effect = NULL;
}


Player::~Player(void)
{
	if(special_effect != NULL)
	{
		delete special_effect;
	}
}


sf::Vector2f Player::getPosition(size_t index)
{
	return shape.getTransform().transformPoint(shape.getPoint(index));
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

	if(shape.getPosition().x >= 1280 + 5)
		shape.setPosition(0,shape.getPosition().y);
	else if(shape.getPosition().x <= 0-5)
		shape.setPosition(1280,shape.getPosition().y);

	if(shape.getPosition().y >= 720 + 5)
		shape.setPosition(shape.getPosition().x,0);
	else if(shape.getPosition().y <= 0-5)
		shape.setPosition(shape.getPosition().x,720);

	//specjalny bonus
	if(status == STATUS_IMMORTAL && special_effect->getElapsedTime() >= duration)
	{
		delete special_effect;
		special_effect = NULL;

		status = STATUS_ALIVE;
		shape.setFillColor(Color::White);
	}
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


Vector2f Player::getAngle()
{
	float angle = shape.getRotation();

	float xN = static_cast<float>(sin((speed) * M_PI * (angle / 360)));
	float yN = static_cast<float>(cos((speed) * M_PI * (angle / 360)));

	return Vector2f(vx+xN,vy-yN);
}


sf::Vector2f Player::getNextPosition()
{
	return Vector2f(getPosition(2).x+vx,getPosition(2).y+vy);
}


void Player::enemy_coll()
{
	if(status == STATUS_ALIVE)
	{
		lifes--;
		
		if(lifes > 0)
		{
			duration = seconds(2.5f);
			special_effect = new Clock;
			
			status = STATUS_IMMORTAL;
			shape.setFillColor(Color::Red);
		}
		else
			status = STATUS_DEAD;
	}
}


int Player::getSpecialEffectTime()
{
	if(special_effect == NULL)
		return 0;
	
	Time t = duration - special_effect->getElapsedTime();
	return t.asSeconds();
}


void Player::immortal()
{
	status = STATUS_IMMORTAL;
	shape.setFillColor(Color::Green);

	if(special_effect == NULL)
		special_effect = new Clock;
	
	duration = seconds(3.5f);
	special_effect->restart();
}


void Player::addLifes()
{
	if(lifes < 5)
		lifes++;
}