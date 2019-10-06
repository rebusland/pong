#include "pch.h"
#include "inc/ComputerPaddle.h"
#include "inc/Game.h"

GameMessage ComputerPaddle::Update()
{
	// let's assume no exception is caugth: Pong objects will be always created by PongObjectManager
	const auto& pongObjManager = dynamic_cast<const PongObjectsManager&>(_objectManager);

	float currentBallX = pongObjManager.GetBallPosition().x;

	/* 
	 * TODO
	 * Trying to "tune" in some way the computer mistakes rate brings to a very interesting question:
	 * what causes an actual human player to miss? 
	 * Is the cause the same at all ball speeds and incoming angles?
	 * How can we translate a simple model of human error in code for the computer paddle?
	 *
	 * For the moment a simple heuristic has been implemented:
	 * computer paddle is allowed to have "oversights" sometimes; in such cases the paddle
	 * is not moved. The rate of oversights is related to _responsiveness value, which is 
	 * compared against random numbers in the interval [0, 100]; if the rand number is greater than
	 * responsiveness an oversight occurs.
	 * TODO improve the computer "fallability" process to make it more similar to a human user one.
	 */
	float speed = 0.f;

	bool isOversight = (_responsiveness != Responsiveness::Perfect  && rand() % 100 > _responsiveness);

	if (isOversight) 
	{
		LOG("Computer oversight!"); // TODO remove
	}
	else
	{
	
		if (getGlobalBounds().left + PADDLE_WIDTH < currentBallX)
		{
			speed = PADDLE_SPEED;
		}
		else if (getGlobalBounds().left > currentBallX + GameBall::BALL_RADIUS)
		{
			speed = -PADDLE_SPEED;
		}

		MovePaddle(speed * Game::WIN_UPDATE_TIME); // dx = v * dt
	}

	// in any case, enforce a valid paddle position
	EnforceValidPosition();

	return GameMessage::EmptySuccessMessage();
}
