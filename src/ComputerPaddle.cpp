#include "pch.h"
#include "inc/ComputerPaddle.h"
#include "inc/Game.h"

ComputerPaddle::~ComputerPaddle()
{
	std::cout << __func__ << std::endl;
}

GameMessage ComputerPaddle::Update()
{
	// get ball position, according to difficulty level the computer paddle should be able to keep up with ball movements
	float currentBallPositionX = Game::GetBallPosition().x;

	float speed = 0.0;
	if (this->GetBounds().left + PADDLE_WIDTH < currentBallPositionX)
	{
		speed = PADDLE_SPEED;
	}
	else if (this->GetBounds().left > currentBallPositionX + GameBall::BALL_WIDTH)
	{
		speed = -PADDLE_SPEED;
	}
		
	// increment current position by dx = v * dt
	GetSprite().move(speed * Game::WIN_UPDATE_TIME, 0);

	// if no error is encountered then an empty success message is returned
	return GameMessage::EmptySuccessMessage();
}
