#include "pch.h"
#include "inc/Paddle.h"

void Paddle::Draw(sf::RenderWindow & window)
{
	window.draw(*this); // Paddle, as a RectangleShape, has a proper implementation of draw method
}

void Paddle::MovePaddle(float dx)
{
	RectangleShape::move(dx, 0); // dy = 0
}
