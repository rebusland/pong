#include "pch.h"
#include "inc/ComputerPaddle.h"
#include "inc/Game.h"

GameMessage ComputerPaddle::Update()
{
	// get ball position, according to difficulty level the computer paddle should be able to keep up with ball movements
	float currentBallPositionX = Game::GetBallPosition().x;

	float speed = 0.0;
	if (this->GetBounds().left + PADDLE_WIDTH < currentBallPositionX)
	{
		speed = PADDLE_SPEED;
	}
	else if (this->GetBounds().left > currentBallPositionX + GameBall::BALL_RADIUS)
	{
		speed = -PADDLE_SPEED;
	}
		
	// increment current position by dx = v * dt
	MovePaddle(speed * Game::WIN_UPDATE_TIME);

	// if no error is encountered then an empty success message is returned
	return GameMessage::EmptySuccessMessage();
}
