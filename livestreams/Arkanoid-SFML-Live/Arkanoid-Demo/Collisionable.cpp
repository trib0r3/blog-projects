#include "Collisionable.h"

Collisionable::Collisionable()
{
	isTrigger = false;
}

/*
	Simple collision check
*/
bool Collisionable::IsCollision(Collisionable *other, Vector2f& offset)
{
	// TODO change later
	FloatRect *f1 = &this->GetCollider();
	FloatRect *f2 = &other->GetCollider();
	
	f1->left += offset.x;
	f1->top += offset.y;

	return !(f1->left > f2->left + f2->width || f1->left + f1->width < f2->left ||
		f1->top > f2->top + f2->height || f1->top + f1->height < f2->top);
}
