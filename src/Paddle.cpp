#include "pch.h"
#include "inc/Paddle.h"

void Paddle::Draw(sf::RenderWindow & window)
{
	window.draw(*this); // Paddle, as a RectangleShape, has a proper implementation of draw method
}

sf::FloatRect Paddle::GetBounds() const
{
	return sf::RectangleShape::getGlobalBounds();
}

void Paddle::SetScale(float sizeX, float sizeY)
{
	sf::RectangleShape::setScale(sizeX, sizeY);
}

void Paddle::SetPosition(float x, float y)
{
	sf::RectangleShape::setPosition(x, y);
}

sf::Vector2f Paddle::GetPosition() const
{
	return sf::RectangleShape::getPosition();
}

void Paddle::MovePaddle(float dx)
{
	RectangleShape::move(dx, 0); // dy = 0
}

/*
bool Paddle::IsWinLeftBorderTouched() const
{
	return false;
}

bool Paddle::IsWinRightBorderTouched() const
{
	return false;
}

bool Paddle::IsWinTopBorderTouched() const
{
	return false;
}

bool Paddle::IsWinBottomBorderTouched() const
{
	return false;
}
*/
