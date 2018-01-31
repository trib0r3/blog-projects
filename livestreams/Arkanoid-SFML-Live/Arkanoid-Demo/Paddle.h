#pragma once
#include <SFML\Graphics.hpp>
#include "Collisionable.h"

using namespace sf;

class Paddle : public Drawable, public Collisionable
{
public:
	Color colorIsMoving;
	Color colorIsStopped;


	Paddle();
	~Paddle();

	void OnMoveButtonPressed(int direction);
	void OnMoveArrowsReleased();

	virtual Vector2f GetVelocity();
	virtual FloatRect GetCollider();

	void setPosition(float x, float y);



protected:
	virtual void Update(const float *deltaTime) override;
	virtual void OnCollisionEnter(Collisionable& collider) override;


private:
	RectangleShape m_paddle;
	const float SPEED = 700.f;

	void stopPaddle();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

