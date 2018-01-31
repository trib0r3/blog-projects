#include "Snake.h"


const int BODY_SIZE = 32;
using namespace sf;

Snake::Snake()
{
	RectangleShape head;
	head.setFillColor(Color::Green);
	head.setOutlineThickness(-4.f);
	head.setOutlineColor(Color::Blue);
	head.setSize(Vector2f(BODY_SIZE, BODY_SIZE));
	head.setPosition(640 / 2 - BODY_SIZE / 2, 480 / 2 - BODY_SIZE / 2);

	m_snakeParts.push_back(head);
	m_direction = DIR_UP;
}


Snake::~Snake()
{
}


void Snake::Move()
{
	Vector2f dir(0.f, 0.f);

	switch (m_direction)
	{
	case DIR_LEFT:
		dir.x = -1;
		break;

	case DIR_RIGHT:
		dir.x = 1;
		break;

	case DIR_UP:
		dir.y = -1;
		break;

	case DIR_DOWN:
		dir.y = 1;
		break;

	default:
		exit(-1);
		break;
	}

	Vector2f prevPos = m_snakeParts[0].getPosition();
	Vector2f offset(dir.x * BODY_SIZE, dir.y * BODY_SIZE);
	m_snakeParts[0].move(offset);
	
	for (int i = 1;i < m_snakeParts.size(); i++)
	{
		Vector2f tmp = m_snakeParts[i].getPosition();
		m_snakeParts[i].setPosition(prevPos);
		prevPos = tmp;
	}
}


void Snake::ChangeDirection(Direction dir)
{
	if (std::abs(dir - m_direction) > 1)
	{
		m_direction = dir;
	}
}


void Snake::AddBodyPart()
{
	RectangleShape bodyPart(Vector2f(BODY_SIZE, BODY_SIZE));
	bodyPart.setFillColor(Color::Transparent);
	bodyPart.setOutlineThickness(-4.f);
	bodyPart.setOutlineColor(Color(123,321,132));
	bodyPart.setSize(Vector2f(BODY_SIZE, BODY_SIZE));
	bodyPart.setPosition(-100,-100);
	m_snakeParts.push_back(bodyPart);
}

bool Snake::IsSelfBitting()
{
	FloatRect *head = &m_snakeParts[0].getGlobalBounds();
	FloatRect *body;

	for (int i = 1;i < m_snakeParts.size();i++)
	{
		body = &m_snakeParts[i].getGlobalBounds();
		if (head->intersects(*body)) // CollsionChecker::IsCollsion(head, body)
		{
			return true;
		}
	}

	return false;
}

FloatRect& Snake::GetHeadFloatRect() const
{
	return m_snakeParts[0].getGlobalBounds();
}


void Snake::draw(RenderTarget & target, RenderStates states) const
{
	for (int i = 0;i < m_snakeParts.size(); i++)
	{
		target.draw(m_snakeParts[i]);
	}
}
