//Entity.h
#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

class Entity:
	public Drawable
{
public:
	Entity(bool = true);
	~Entity(void);

	virtual void setColor(Color)=0;

protected:
	bool can_hurt_player;
};