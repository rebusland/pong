#include "pch.h"
#include "inc/PlayerPaddle.h"
#include "inc/Game.h"

GameMessage PlayerPaddle::Update()
{
	float speed{ 0.0 };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !_isLeftBorderTouched)
	{
		speed = - PADDLE_SPEED;
	} 
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !_isRightBorderTouched)
	{
		speed = PADDLE_SPEED;
	}

	// increment current position by dx = v * dt
	MovePaddle(speed * Game::WIN_UPDATE_TIME);

	// in any case, enforce a valid paddle position (bounded to game field)
	EnforceValidPosition();

	// if no problem encountered, then an empty success message is returned
	return GameMessage::EmptySuccessMessage();
}
