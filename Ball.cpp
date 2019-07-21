#include "pch.h"
#include "Ball.h"
#include "Game.h"

// definition of static variable BALL_WIDTH
float GameBall::BALL_WIDTH = 0;

GameBall::GameBall()
{
	Load("images/ball.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getScale().x / 2, GetSprite().getScale().y / 2);
	BALL_WIDTH = this->GetBounds().width;

	// initialize random seed:
	srand(time(NULL));

	// random angle at which the ball is first thrown (in the intervals [30, 150] and [210, 330] degrees) 
	_angle = 30 + rand() % 120;
	_angle = (rand() % 2 == 0) ? _angle : 180 + _angle
;
}

GameBall::~GameBall()
{
	std::cout << __func__ << std::endl;
}

void GameBall::Draw(sf::RenderWindow& rw)
{
	VisibleGameObject::Draw(rw);
}

void GameBall::Update()
{
	// std::cout << GetPosition().x << ", " << GetPosition().y << std::endl;

	// if the bottom border of the window is reached than the player on that side (user for the moment) lose the game
	if (IsWinBottomBorderTouched())
	{
		// std::cout << "User lost the game!!" << std::endl;
		return;
	}

	// reflection top (to be removed)
	if (IsWinTopBorderTouched())
	{
		_angle = -_angle;
	}

	// reflection on window left/right sides
	if (IsWinLeftBorderTouched() ||
		IsWinRightBorderTouched())
	{
		_angle = 180 - _angle;
	}

	bool someCollision = false;

	// get paddles bounds
	for (auto x : Game::GetPaddlesBounds())
	{
		// if ball collides with paddle bounds it bounces back according to the current paddle motion
		if (GetSprite().getGlobalBounds().intersects(x))
		{
			std::cout << "Collision! \n";
			if (!_hasCollided)
				_angle = ComputeBallPaddleAngle(_angle, x);

			someCollision = true;
		}
	}

	_hasCollided = someCollision;

	float dx = BALL_SPEED * cos(_angle * PI / 180) * Game::WIN_UPDATE_TIME; // dx = v * cos(angle) * dt
	float dy = BALL_SPEED * sin(_angle * PI / 180) * Game::WIN_UPDATE_TIME; // dy = v * sin(angle) * dt

	GetSprite().move(dx, dy);
}

double GameBall::ComputeBallPaddleAngle(double upcomingAngle, const sf::FloatRect& paddleBounds) const
{
	double ballCenter = this->GetBounds().left + this->GetBounds().width / 2;
	double paddleCenterX = paddleBounds.left + paddleBounds.width / 2;

	std::cout << "ball left bound: " << this->GetBounds().left << ", ball width: " << this->GetBounds().width << "\n";
	std::cout << "paddle left bound: " << paddleBounds.left << ", paddle width: " << paddleBounds.width << "\n";

	std::cout << "ball center: " << ballCenter << ", paddleCenterX: " << paddleCenterX << "\n";

	double emergingAngle = 270 + 60 * (ballCenter - paddleCenterX) / (paddleBounds.width / 2);

	std::cout << "upcoming angle: " << upcomingAngle << ", emergingAngle: " << emergingAngle << "\n";

	return (std::sin(upcomingAngle * PI / 180) >= 0.0) ? emergingAngle : 360 - emergingAngle;

	/*
	double paddleCenterX = paddleBounds.left + 0.5 * paddleBounds.width;

	double ballPositionToPaddleRatio = (this->GetPosition().x - paddleCenterX) / (paddleBounds.width * 0.5);
	// limit range to [-1, 1]
	// ballPositionToPaddleRatio = std::min(1.0, std::max(-1.0, ballPositionToPaddleRatio));

	// 0.7 scale factor to narrowing the range of emerging angles, excluding those angles which are too "horizontal"
	double emergingAngle = (180 / PI) * acos(0.7 * ballPositionToPaddleRatio);

	return (std::sin(upcomingAngle) <= 0) ? emergingAngle : -emergingAngle;
	*/
}
