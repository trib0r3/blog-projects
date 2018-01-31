#include <SFML\Graphics.hpp>
#include "SpecialEffects.h"

using namespace sf;

const int WIDTH = 1280;
const int HEIGHT = 720;

int main()
{
	RenderWindow window(VideoMode(WIDTH,HEIGHT),"Efekty specjalne",Style::Close);
	window.setFramerateLimit(100);
	
	//wczytywanie tekstury
	Texture t;
	t.loadFromFile("picture.jpg");
	Sprite obraz(t);
	obraz.setOrigin(650,365.5);
	obraz.setPosition(640,360);
	
	//inne
	SpecialEffects special(WIDTH,HEIGHT);
	Mouse::setPosition(Vector2i(640,360));

	Vector2f d(640,360);

	//petla glowna programu
	while(window.isOpen())
	{
		Event event;

		while(window.pollEvent(event))
		{
			//zamykanie okna
			if(event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
			
			//----------------specjalne efekty----------------------
			//przyciemnianie
			if(Keyboard::isKeyPressed(Keyboard::Num1))
				special.przyciemnij();
			//rozjasnianie
			else if(Keyboard::isKeyPressed(Keyboard::Num2))
				special.rozjasnij();

			//wykorzystanie kolejki
			else if(event.type == Event::KeyReleased && event.key.code == Keyboard::Num3)
			{
				special.dodaj(special.PRZYCIEMNIJ);
				special.dodaj(special.ROZJASNIJ);
			}

			//poruszanie obrazem
			if(event.type == Event::MouseMoved)
			{
				Vector2f p(Mouse::getPosition(window));
				Vector2f s(obraz.getPosition());
				
				
				if(p.x > d.x && s.x + 630 < WIDTH)
					obraz.move(1,0);
				else if(p.x < d.x && s.x - 630 > 0)
					obraz.move(-1,0);
					
				if(p.y < d.y && s.y - 354.5 > 0)
					obraz.move(0,-0.5);
				else if(p.y > d.y && s.y + 354.5 < HEIGHT) 
					obraz.move(0,0.5);

				d.x = p.x;
				d.y = p.y;
			}

		}
		special.update();
		
		window.clear();

		window.draw(obraz);
		window.draw(special);

		window.display();
	}
}