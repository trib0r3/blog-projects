#pragma once

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <string>
#include <map>
#include <algorithm>
#include "Collisionable.h"

using namespace std;
using namespace sf;


class PhysicsEngine
{
public:
	//static PhysicsEngine* singleton;

	PhysicsEngine();
	~PhysicsEngine();

	void AddObject(Collisionable* object, bool dynamic = false);
	void DelObject(uint64_t id, bool dynamic);
	void Update(const float* delta);

private:
	uint64_t m_idMaker;
	std::map <uint64_t, Collisionable*> m_CollideableObjects;
	std::map <uint64_t, Collisionable*> m_dynamicCollideableObjects;

	void checkCollisions(const float* time);
	void updateAllObjects(const float* time);

	Vector2f getNextPositionOffset(Collisionable* collider,const float* delta);
};

