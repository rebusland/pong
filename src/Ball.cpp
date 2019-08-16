#include "pch.h"
#include "inc/Ball.h"
#include "inc/Game.h"

// definition of static variable BALL_WIDTH
float GameBall::BALL_WIDTH = 0;

GameBall::GameBall() : SpriteGameObject(BALL_DEFAULT_IMAGE_PATH)
{
	// TODO add SetOrigin method to SpriteGameObject
	Sprite::setOrigin(Sprite::getScale().x / 2, Sprite::getScale().y / 2);
	BALL_WIDTH = this->GetBounds().width;

	// initialize random seed:
	srand(time(NULL));

	// random angle at which the ball is first thrown (in the intervals [30, 150] and [210, 330] degrees) 
	_angle = 30 + rand() % 120;
	_angle = (rand() % 2 == 0) ? _angle : 180 + _angle;
}

GameBall::~GameBall()
{
	std::cout << __func__ << std::endl;
}

void GameBall::Draw(sf::RenderWindow& rw)
{
	SpriteGameObject::Draw(rw);
}

GameMessage GameBall::Update()
{
	// std::cout << GetPosition().x << ", " << GetPosition().y << std::endl;

	// if the bottom border of the window is reached than the player on that side (user for the moment) lose the game
	if (IsWinBottomBorderTouched())
	{
		// for testing purpose a popup for gameover and restarting the game is displayed
		return GameMessage(GameMessage::message_type_t::PLAYER_MISS, "player paddle missed the ball!", false);
	}
	// top border of the window reached by the ball ==> computer miss
	if (IsWinTopBorderTouched())
	{
		return GameMessage(GameMessage::message_type_t::COMPUTER_MISS, "Computer paddle missed the ball!", false);
		
		// reflection top (to be removed)
		// _angle = -_angle;
	}
	// reflection on window left/right sides
	else if (IsWinLeftBorderTouched() ||
		IsWinRightBorderTouched())
	{
		_angle = 180 - _angle;
	}

	bool someCollision = false;

	// get paddles bounds
	for (auto x : Game::GetPaddlesBounds())
	{
		// if ball collides with paddle bounds it bounces back according to the current paddle motion
		if (Sprite::getGlobalBounds().intersects(x))
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

	Sprite::move(dx, dy);

	// if no problem occured an empty success message is sent
	return GameMessage::EmptySuccessMessage();
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
