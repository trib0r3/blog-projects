#include "Paddle.h"


Paddle::Paddle()
{
	if (colorIsStopped == Color())
		colorIsStopped = Color::Red;
	if (colorIsMoving == Color())
		colorIsMoving = Color::Green;

	m_paddle.setFillColor(Color::Transparent);
	m_paddle.setSize(Vector2f(150.f, 15.f));
	m_paddle.setOutlineThickness(-2.5f);
	m_paddle.setOutlineColor(colorIsStopped);
	m_paddle.setOrigin(75.f, 7.5f);

	m_velocity = Vector2f(0.f, 0.f);
	tag = "Player";
}


Paddle::~Paddle()
{
}


void Paddle::OnMoveButtonPressed(int direction)
{
	if (direction == 0)
		return OnMoveArrowsReleased();

	m_velocity.x = SPEED * direction;
	m_paddle.setOutlineColor(colorIsMoving);
}


void Paddle::OnMoveArrowsReleased()
{
	stopPaddle();
}


Vector2f Paddle::GetVelocity()
{
	return m_velocity;
}


FloatRect Paddle::GetCollider()
{
	return m_paddle.getGlobalBounds();
}


void Paddle::setPosition(float x, float y)
{
	m_paddle.setPosition(x, y);
}


void Paddle::Update(const float * deltaTime)
{
	if (m_velocity.x == 0) return;
	float x = m_velocity.x * (*deltaTime);

	m_paddle.move(x, 0);
}


void Paddle::OnCollisionEnter(Collisionable & collider)
{
	if (collider.tag == "Ball")
	{
		// TODO ball
		// do some crazy stuff
	}
	else
	{
		m_velocity = -1.5f* m_velocity;
	}
}


void Paddle::stopPaddle()
{
	m_velocity.x = 0;
	m_paddle.setOutlineColor(colorIsStopped);
}


void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_paddle);
}