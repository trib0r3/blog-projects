/*
Player.cpp

Poradnik: Piszemy grê w SFML'u
Nazwa: Mechanized Techno Explorer

Autor: Szymon Siarkiewicz (sheadovas)
http://szymonsiarkiewicz.pl/

*/

#include "Player.h"
#include <Windows.h>
#include <math.h>
#include <iostream>

#define M_PI 3.14159265358979323846

using namespace sf;

Player::Player(void)
{
	if(!texture.loadFromFile("data/images/player-move.png"))
	{
		MessageBox(NULL,"Textures not found!","ERROR",NULL);
		return;
	}

	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0,0,64,64));

	sprite.setOrigin(32,32);
	
	status = STOJ;

	frame = 0;
	speed = 2.5f;

	sprite.setPosition(400,400);
	anim_clock.restart();
}


Player::~Player(void)
{
}


void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(sprite);
}


void Player::update(sf::Vector2f mysz)
{
	Vector2f norm = mysz - sprite.getPosition();
	float rot = atan2(norm.y,norm.x);
	rot = rot * 180.f/M_PI;
	
	rot += 90;
	sprite.setRotation(rot);

	if(anim_clock.getElapsedTime() > sf::seconds(0.09f) )
	{
		if(status == STOJ) return;
		if(frame < 7 /*liczba klatek animacji*/)
			frame++;
		else
			frame = 0; //zapetlanie animacji
		
		sprite.setTextureRect(IntRect(frame*64,0,64,64));
								//x, y, szerokosc, wysokosc
		
		//poruszenie graczem
		sprite.move(getSpeed());
		
		anim_clock.restart();
	}
}


sf::Vector2f Player::getPosition()
{
	return sprite.getPosition();
}


Player::Status Player::getStatus()
{
	return status;
}


sf::FloatRect Player::getBoundingBox()
{
	sf::FloatRect f(sprite.getGlobalBounds());
	return f;
}


sf::Vector2f Player::getSpeed()
{
	float rotacja = sprite.getRotation();
	float vx = sin(( rotacja * M_PI ) / 180.0f );
	float vy = -cos(( rotacja * M_PI ) / 180.0f );
	
	return Vector2f(vx*speed,vy*speed);
}


void Player::stop()
{
	status = STOJ;
	frame = 0;
}


void Player::idz()
{
	status = IDZ;
}