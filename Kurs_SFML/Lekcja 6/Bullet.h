//Bullet.h
#pragma once
#include "entity.h"
#include <vector>
class Bullet: 
	public Entity,Transformable
{
public:
	Bullet(bool = true,int = 500,bool = true);
	~Bullet(void);

	void add(Vector2f,Vector2f);
	void remove(int it);

	void update();

	virtual void setColor(Color = Color::White);
	void addAmmunition(int ammo=50);

	bool isEmpty();
	
	int getSize();
	Vector2f getPoint(int index);

	int getAmmo(){return ammunition;}


private:
	VertexArray m_bullet;
	Color color;

	Clock timer;
	Time frequency;

	bool infinite;
	int ammunition;

	std::vector <Vector2f> factor;

	virtual void draw(sf::RenderTarget &target,sf::RenderStates states) const;
};