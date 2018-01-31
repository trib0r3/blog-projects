#include "CollsionChecker.h"


bool CollsionChecker::IsCollision(sf::FloatRect * f1, sf::FloatRect * f2)
{
	if (
		f1->left >= f2->left + f2->width ||
		f1->left + f1->width <= f2->left ||
		f1->top >= f2->top + f2->width ||
		f1->top + f1->width <= f2->top
		)
		return false;

	else
		return true;
}
