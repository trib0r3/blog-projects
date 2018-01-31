//Asteroids.h
#pragma once
#include "entity.h"
#include <vector>

using namespace std;

class Asteroids :
	public Entity,Transformable
{
public:
	Asteroids(bool = true);
	~Asteroids(void);

	virtual void setColor(Color=Color::White);

	void generate(int ile, int = 0,int y=0);
	void del(int index);

	void update();
	Vector2f getPoint(int index,int it);
	
	int getSize();
	int getSize(int index);


	bool isEmpty();

private:
	Color m_color;

	struct Asteroid
	{
		Vector2f speed;
		ConvexShape shape;
		bool big;
	};

	vector <Asteroid> m_asteroids;
	virtual void draw(sf::RenderTarget &target,sf::RenderStates states) const;
};