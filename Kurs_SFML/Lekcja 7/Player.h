//Player.h
#pragma once

#include <SFML\Graphics.hpp>

class Player: public sf::Drawable,
	sf::Transformable
{
public:
	Player(void);
	~Player(void);

	enum Status {
		STATUS_ALIVE,
		STATUS_DEAD,
		STATUS_IMMORTAL,
		Status_Count};

	sf::Vector2f getPosition(size_t index);
	Status getStatus();

	void update();
	void playAnimation(bool play);

	void accelerate();
	void rotate(int angle);

	void setVelocity(int x,int y);
	sf::Vector2f getVelocity(){return sf::Vector2f(vx,vy);}
	sf::Vector2f getAngle();
	
	sf::Vector2f getNextPosition();

	void enemy_coll();

	int getLifes(){return lifes;}
	int getSpecialEffectTime();

	void immortal();
	void addLifes();

private:
	sf::ConvexShape shape;
	Status status;
	
	float speed;
	unsigned static const int max_speed = 3;
	
	float vx; 
	float vy;

	size_t lifes;
	
	sf::Clock *special_effect;
	sf::Time duration;

	
	virtual void draw(sf::RenderTarget &target,sf::RenderStates states) const;
};