#pragma once
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <string>
#include <cinttypes>

class PhysicsEngine;


using namespace sf;

class Collisionable
{
	friend class PhysicsEngine;

public:
	Collisionable();

	std::string tag;
	uint64_t id;
	bool isTrigger;

	virtual Vector2f GetVelocity() = 0;
	virtual FloatRect GetCollider() = 0;

	bool IsCollision(Collisionable* other, Vector2f& offset = Vector2f(0.f,0.f));

protected:
	Vector2f m_velocity;

	virtual void Update(const float* deltaTime) = 0;
	virtual void OnCollisionEnter(Collisionable& collider) = 0;
};

