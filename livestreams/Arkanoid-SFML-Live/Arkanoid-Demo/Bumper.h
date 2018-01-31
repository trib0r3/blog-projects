#pragma once
#include "Collisionable.h"
#include <SFML\Graphics\Rect.hpp>

class Bumper : public Collisionable
{
public:
	Bumper(Vector2f pos, Vector2f size, bool isTrigger = false);
	~Bumper();

	virtual Vector2f GetVelocity() override;
	virtual FloatRect GetCollider() override;
	virtual void Update(const float * deltaTime) override;
	virtual void OnCollisionEnter(Collisionable & collider) override;

private:
	sf::FloatRect m_collider;
};

