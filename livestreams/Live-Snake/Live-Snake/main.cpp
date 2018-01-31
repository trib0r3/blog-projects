#include <SFML\Graphics.hpp>
#include "CollsionChecker.h"
#include <ctime>
#include <cstdlib>
#include "Snake.h"

using namespace sf;

const int SCRN_WIDTH = 640;
const int SCRN_HEIGHT = 480;
const int APPLE_SIZE = 16;

Vector2f GetRandomPosition()
{
	Vector2i max(SCRN_WIDTH - APPLE_SIZE, SCRN_HEIGHT - APPLE_SIZE);

	return Vector2f(rand() % max.x, rand() % max.y);
}



int main()
{
	srand(time(NULL));

	RenderWindow window(VideoMode(SCRN_WIDTH, SCRN_HEIGHT), "Snake", Style::Close);
	Snake snake;

	RectangleShape apple(Vector2f(APPLE_SIZE,APPLE_SIZE));
	apple.setFillColor(Color::Red);
	apple.setPosition(GetRandomPosition());

	sf::Clock clock;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape))
			{
				window.close();
			}

			else if (event.type == Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case Keyboard::Left:
					snake.ChangeDirection(Snake::DIR_LEFT);
					break;

				case Keyboard::Right:
					snake.ChangeDirection(Snake::DIR_RIGHT);
					break;

				case Keyboard::Up:
					snake.ChangeDirection(Snake::DIR_UP);
					break;

				case Keyboard::Down:
					snake.ChangeDirection(Snake::DIR_DOWN);
					break;
				}
			}
		}


		if (clock.getElapsedTime().asMilliseconds() > 500)
		{
			snake.Move();
			FloatRect *s = &snake.GetHeadFloatRect();
			FloatRect *f = &apple.getGlobalBounds();
			if (CollsionChecker::IsCollision(s, f))
			{
				apple.setPosition(GetRandomPosition());
				snake.AddBodyPart();
			}

			clock.restart();
		}

		if (snake.IsSelfBitting())
		{
			window.close();
			return 1;
		}
		
		window.clear();
		window.draw(apple);
		window.draw(snake);
		window.display();
	}
}