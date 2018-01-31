//SpecialEffects.cpp
#include "SpecialEffects.h"


SpecialEffects::SpecialEffects(int width,int height)
{
	rect.setSize(Vector2f(width,height));
	rect.setFillColor(Color(0,0,0,0));

	alpha = 0;
	mod = 0;
	granica = 0;
	in_progress = false;
}


SpecialEffects::~SpecialEffects(void)
{
}


void SpecialEffects::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(rect);
}


void SpecialEffects::przyciemnij()
{
	in_progress = true;
	mod = 5;
	granica = 255;
}


void SpecialEffects::rozjasnij()
{
	in_progress = true;
	mod = -5;
	granica = 0;
}


void SpecialEffects::update()
{
	if(!kolejka.empty() && !in_progress)
	{
		switch(kolejka.front())
		{
		case ROZJASNIJ:
			rozjasnij();
			kolejka.pop();
			break;
		case PRZYCIEMNIJ:
			przyciemnij();
			kolejka.pop();
			break;
		}
	}
	
	if(in_progress)
	{
		if(alpha != granica)
			alpha+=mod;
		
		if(alpha==granica)
			in_progress = false;

		rect.setFillColor(Color(0,0,0,alpha));
	}
}


void SpecialEffects::dodaj(TYPE type)
{
	kolejka.push(type);
}