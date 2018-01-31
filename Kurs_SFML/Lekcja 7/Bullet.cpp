#include "Bullet.h"
#include <algorithm>

/* TODO LIST
- metoda zmieniaj¹ca kolor WSZYSTKICH pocisków
- metoda zmieniaj¹ca prêdkoœæ wystrzeliwania pocisków (czêstotliwoœæ)
*/

Bullet::Bullet(bool can, int f,bool inf)
{
	can_hurt_player = can;

	color = Color::White;
	frequency = milliseconds(f);

	infinite = inf;
	ammunition = 500;
}


Bullet::~Bullet(void)
{
}


void Bullet::add(Vector2f f,Vector2f pos)
{
	//
	CircleShape c;
	c.setPosition(pos);
	c.setFillColor(color);
	c.setRadius(2);
	
	if(timer.getElapsedTime() >= frequency && (ammunition > 0 || infinite))
	{
		m_bullet.push_back(c);
		factor.push_back(f);

		timer.restart();
		ammunition--;
	}
}


void Bullet::remove(int it)
{
	for(int i=it;i<factor.size()-1;i++)
	{
		std::swap(factor[i],factor[i+1]);
		std::swap(m_bullet[i],m_bullet[i+1]);
	}

	factor.resize(factor.size()-1);
	m_bullet.resize(factor.size());
}


void Bullet::update()
{
	for(int i=0;i<factor.size();i++)
	{
		m_bullet[i].move(Vector2f(factor[i].x*2,factor[i].y*2));//
		Vector2f position(m_bullet[i].getPosition());

		if(position.x >= 1280 || position.x <= 0 ||
			position.y >= 720 || position.y <= 0) //
		{
			remove(i);
		}
	}
}


void Bullet::setColor(Color c)
{
	color = c;
}


void Bullet::draw(RenderTarget &target, RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = NULL;
	
	for(int i=0;i<m_bullet.size();i++)//
		target.draw(m_bullet[i],states);
}


void Bullet::addAmmunition(int ammo)
{
	ammunition+=ammo;
}


bool Bullet::isEmpty()
{
	if(m_bullet.size() <= 0)//
		return true;
	else
		return false;
}


Vector2f Bullet::getPoint(int index)
{
	Vector2f p = m_bullet[index].getPosition();//
	return p;
}


int Bullet::getSize()
{
	return m_bullet.size();//
}