#include "pch.h"
#include "inc/ComputerPaddle.h"
#include "inc/Game.h"

GameMessage ComputerPaddle::Update()
{
	// let's assume no exception is caugth: Pong objects will be always created by PongObjectManager
	const auto& pongObjManager = dynamic_cast<const PongObjectsManager&>(_objectManager);

	// get ball position, according to difficulty level the computer paddle should be able to keep up with ball movements
	float currentBallPositionX = pongObjManager.GetBallPosition().x;

	float speed = 0.0;
	if (getGlobalBounds().left + PADDLE_WIDTH < currentBallPositionX)
	{
		speed = PADDLE_SPEED;
	}
	else if (getGlobalBounds().left > currentBallPositionX + GameBall::BALL_RADIUS)
	{
		speed = -PADDLE_SPEED;
	}
		
	// increment current position by dx = v * dt
	MovePaddle(speed * Game::WIN_UPDATE_TIME);

	// in any case, enforce a valid paddle position (bounded to game field)
	EnforceValidPosition();

	// if no error is encountered then an empty success message is returned
	return GameMessage::EmptySuccessMessage();
}
