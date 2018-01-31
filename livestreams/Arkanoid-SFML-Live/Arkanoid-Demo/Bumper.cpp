#include "Bumper.h"

using namespace sf;

Bumper::Bumper(Vector2f pos, Vector2f size, bool isTrigger)
{
	tag = "Bumper";
	this->isTrigger = isTrigger;

	m_collider.left = pos.x;
	m_collider.top = pos.y;
	m_collider.width = size.x;
	m_collider.height = size.y;
}


Bumper::~Bumper()
{
}


Vector2f Bumper::GetVelocity()
{
	return Vector2f(0, 0);
}

FloatRect Bumper::GetCollider()
{
	return m_collider;
}

void Bumper::Update(const float * deltaTime)
{
	// do nothing
}

void Bumper::OnCollisionEnter(Collisionable & collider)
{
	// do nothing
}
