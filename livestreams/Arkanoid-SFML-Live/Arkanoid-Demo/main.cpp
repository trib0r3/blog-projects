#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "PhysicsEngine.h"
#include "Bumper.h"

// klawisze do poruszania
sf::Keyboard::Key keyMoveLeft = sf::Keyboard::Key::Left;
sf::Keyboard::Key keyMoveRight = sf::Keyboard::Key::Right;


const int SCRN_WIDTH = 480;
const int SCRN_HEIGHT = 600;


int main()
{
	sf::RenderWindow window(sf::VideoMode(SCRN_WIDTH, SCRN_HEIGHT), "Arkanoid (Live Demo)", sf::Style::Close);
	
	// tworzenie obiektów na scenie
	Paddle paddle;
	paddle.setPosition(SCRN_WIDTH / 2, SCRN_HEIGHT - 10);

	Bumper bLeft = Bumper(Vector2f(-1, 0), Vector2f(1.f, SCRN_HEIGHT));
	Bumper bRight = Bumper(Vector2f(SCRN_WIDTH, 0), Vector2f(1.f, SCRN_HEIGHT));
	Bumper bTop = Bumper(Vector2f(0, 0), Vector2f(SCRN_WIDTH, 1.f));


	// 'główne' obiekty
	sf::Clock clock;
	float delta = 0.f;

	// stworzenie silnika fizyki i dodanie tworzonych elementów
	PhysicsEngine physicsEngine;
	physicsEngine.AddObject(&paddle, true);
	physicsEngine.AddObject(&bLeft);
	//physicsEngine.AddObject(&bTop); // HACK me
	physicsEngine.AddObject(&bRight);


	// TODO delete later
	RectangleShape shape;
	shape.setSize(Vector2f(1.f, SCRN_HEIGHT));
	shape.setPosition(Vector2f(SCRN_WIDTH, 0));

	// main loop
	while (window.isOpen())
	{
		sf::Event event;
		// exit check
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		// key event 'loop'
		if (event.type == sf::Event::KeyPressed)
		{
			sf::Keyboard::Key keyCode = event.key.code;

			if (keyCode == keyMoveLeft)
				paddle.OnMoveButtonPressed(-1);
			else if (keyCode == keyMoveRight)
				paddle.OnMoveButtonPressed(1);
		}


		else if (event.type == sf::Event::KeyReleased)
		{
			sf::Keyboard::Key keyCode = event.key.code;

			if (keyCode == keyMoveLeft || keyCode == keyMoveRight)
				paddle.OnMoveArrowsReleased();
		}


		// update & drawing
		physicsEngine.Update(&delta);

		window.clear();
		window.draw(paddle);
		window.draw(shape);
		window.display();

		delta = clock.getElapsedTime().asSeconds();
		clock.restart();
	}

	return 0;
}