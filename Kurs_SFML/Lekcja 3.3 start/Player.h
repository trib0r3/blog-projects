//Player.h
#pragma once

#include <SFML\Graphics.hpp>

class Player: public sf::Drawable,
	sf::Transformable
{
public:
	Player(void);
	~Player(void);

	//1
	enum Status {
		STATUS_ALIVE,
		STATUS_DEAD,
	Status_Count};

	bool shooting;

	//2
	sf::Vector2f getPosition(size_t index);
	Status getStatus();

	void update();
	void playAnimation(bool play);

	//3
	void accelerate();
	void rotate(int angle);

	void setVelocity(int x,int y);
	sf::Vector2f getVelocity(){return sf::Vector2f(vx,vy);}
	
	sf::Vector2f getNextPosition();

private:
	sf::ConvexShape shape; //4
	
	Status status;
	
	float speed;
	unsigned static const int max_speed = 4;

	float vx; 
	float vy; 
	
	virtual void draw(sf::RenderTarget &target,sf::RenderStates states) const;
};