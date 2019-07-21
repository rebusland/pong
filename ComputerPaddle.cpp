#include "pch.h"
#include "ComputerPaddle.h"
#include "Game.h"

ComputerPaddle::~ComputerPaddle()
{
	std::cout << __func__ << std::endl;
}

void ComputerPaddle::Update()
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
}
