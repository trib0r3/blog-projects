#include "PhysicsEngine.h"
#include <iostream>


PhysicsEngine::PhysicsEngine()
{
	m_idMaker = 0;
}


PhysicsEngine::~PhysicsEngine()
{
}


void PhysicsEngine::AddObject(Collisionable * object, bool dynamic)
{
	object->id = m_idMaker++;

	if (dynamic)
		m_dynamicCollideableObjects.emplace(object->id, object);
	else
		m_CollideableObjects.emplace(object->id, object);
}


void PhysicsEngine::DelObject(uint64_t key, bool dynamic)
{
	if (dynamic)
		m_dynamicCollideableObjects.erase(key);
	else
		m_CollideableObjects.erase(key);
}


void PhysicsEngine::Update(const float * delta)
{
	// HACK checkCollisions(delta);
	updateAllObjects(delta);
}


void PhysicsEngine::checkCollisions(const float * time)
{
	std::map <uint64_t, Collisionable*>::iterator itStatic, itDynamic;

	for (itDynamic = m_dynamicCollideableObjects.begin(); itDynamic != m_dynamicCollideableObjects.end(); ++itDynamic)
	{
		Collisionable* dynObj = itDynamic->second;
		Vector2f offset = getNextPositionOffset(dynObj, time);


		// naive collision check
		for (itStatic = m_CollideableObjects.begin();itStatic != m_CollideableObjects.end(); ++itStatic)
		{
			Collisionable* stObj = itStatic->second;

			// collision detection
			if (dynObj->IsCollision(stObj, offset))
			{
				std::cout << "Koliza!\n";
				dynObj->OnCollisionEnter(*stObj);
				stObj->OnCollisionEnter(*dynObj);
			}
		}
	}
}


void PhysicsEngine::updateAllObjects(const float * time)
{
	std::map <uint64_t, Collisionable*>::iterator it;

	// dynamic objects update
	for (it = m_dynamicCollideableObjects.begin(); it != m_dynamicCollideableObjects.end(); ++it)
	{
		it->second->Update(time);
	}

	// static objects update
	for (it = m_CollideableObjects.begin(); it != m_CollideableObjects.end(); ++it)
	{
		it->second->Update(time);
	}
}


Vector2f PhysicsEngine::getNextPositionOffset(Collisionable * collider, const float* delta)
{
	Vector2f velocity = collider->GetVelocity();
	FloatRect rect = collider->GetCollider();

	Vector2f offset;
	offset.x = velocity.x * rect.left * (*delta);
	offset.y = velocity.y * rect.top * (*delta);

	return offset;
}
