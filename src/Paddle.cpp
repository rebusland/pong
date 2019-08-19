#include "pch.h"
#include "inc/Paddle.h"
#include "inc/Game.h"

Paddle::Paddle():
	sf::RectangleShape(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT))
{
	std::cout << __func__ << std::endl;
}

void Paddle::EnforceValidPosition()
{
	auto currentPosition = getPosition();

	if (currentPosition.x < 0)
	{
		setPosition(0, currentPosition.y);
		_isLeftBorderTouched = true;
	}
	else if (currentPosition.x > Game::FIELD_WIDTH - PADDLE_WIDTH)
	{
		setPosition(Game::FIELD_WIDTH - PADDLE_WIDTH, currentPosition.y);
		_isRightBorderTouched = true;
	}
	else 
	{
		_isLeftBorderTouched = _isRightBorderTouched = false;
	}
}
