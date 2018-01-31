//SpecialEffects.h
#pragma once
#include <SFML\Graphics.hpp>
#include <queue>

using namespace sf;

class SpecialEffects:public Drawable
{
public:
	SpecialEffects(int width,int height);
	~SpecialEffects(void);

	enum TYPE {ROZJASNIJ,PRZYCIEMNIJ};//

	void przyciemnij();
	void rozjasnij();

	void update();

	void dodaj(TYPE type);

private:
	RectangleShape rect;
	
	int alpha;
	
	int mod;
	int granica;

	bool in_progress;

	std::queue <TYPE> kolejka;

	Clock clock;
	Time time;
	
	virtual void draw(sf::RenderTarget &target,sf::RenderStates states) const;
};