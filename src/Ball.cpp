#include "pch.h"
#include "inc/Ball.h"
#include "inc/Game.h"

GameBall::GameBall() : SpriteGameObject(BALL_DEFAULT_IMAGE_PATH)
{
	// resize ball image so that at the end we get a ball with radius BALL_RADIUS
	SetSize(BALL_RADIUS , BALL_RADIUS);

	// origin for the ball will be its center (by default it is the top left corner of the enclosing rectangle
	SetOrigin(BALL_RADIUS / 2, BALL_RADIUS / 2);

	// initialize random seed:
	srand(time(NULL));

	// random angle at which the ball is first thrown (in the intervals [45, 135] and [225, 315] degrees) 
	_angle = 45 + rand() % 90;
	_angle = (rand() % 2 == 0) ? _angle : 180 + _angle;
}

GameMessage GameBall::Update()
{
	// std::cout << GetPosition().x << ", " << GetPosition().y << std::endl;

	// if the bottom border of the window is reached than the player on that side (user for the moment) lose the game
	if (IsWinBottomBorderTouched())
	{
		return GameMessage(GameMessage::message_type_t::PLAYER_MISS, "player paddle missed the ball!", false);
	}
	// top border of the window reached by the ball ==> computer miss
	if (IsWinTopBorderTouched())
	{
		return GameMessage(GameMessage::message_type_t::COMPUTER_MISS, "Computer paddle missed the ball!", false);
	}
	// reflection on the field left/right sides
	else if (IsWinLeftBorderTouched() ||
		IsWinRightBorderTouched())
	{
		_angle = 180 - _angle;
	}

	bool someCollisionWithPaddle { false };

	// get paddles bounds
	for (auto x : Game::GetPaddlesBounds())
	{
		// if ball collides with paddle bounds it bounces back according to the current paddle motion
		if (GetBounds().intersects(x))
		{
			std::cout << "Collision! \n";
			if (!_hasCollidedWithPaddle)
				_angle = ComputeBallPaddleAngle(_angle, x);

			someCollisionWithPaddle = true;
		}
	}

	_hasCollidedWithPaddle = someCollisionWithPaddle;

	// first of all, enforce ball to be in the field space
	// floor ball left side to zero and cap its right side to FIELD_WIDTH
	if (GetBounds().left < 0)
	{
		SetPosition(0, GetPosition().y);
	}
	else if (GetBounds().left + GetBounds().width > Game::FIELD_WIDTH) 
	{
		SetPosition(Game::FIELD_WIDTH - GetBounds().width, GetPosition().y);
	}

	float dx = BALL_SPEED * cos(_angle * PI / 180) * Game::WIN_UPDATE_TIME; // dx = v * cos(angle) * dt
	float dy = BALL_SPEED * sin(_angle * PI / 180) * Game::WIN_UPDATE_TIME; // dy = v * sin(angle) * dt

	Sprite::move(dx, dy);

	// if no problem occured an empty success message is sent
	return GameMessage::EmptySuccessMessage();
}

double GameBall::ComputeBallPaddleAngle(double upcomingAngle, const sf::FloatRect& paddleBounds) const
{
	double ballCenter = GetBounds().left + GetBounds().width / 2;
	double paddleCenterX = paddleBounds.left + paddleBounds.width / 2;

	std::cout << "ball left bound: " << GetBounds().left << ", ball width: " << GetBounds().width << "\n";
	std::cout << "paddle left bound: " << paddleBounds.left << ", paddle width: " << paddleBounds.width << "\n";
	std::cout << "ball center: " << ballCenter << ", paddleCenterX: " << paddleCenterX << "\n";

	// 270 (reverse direction) + angle spread (backhand or forehand)
	double emergingAngle = 270 + BALL_ANGLE_SPREAD * (ballCenter - paddleCenterX) / (paddleBounds.width / 2);

	emergingAngle = (std::sin(upcomingAngle * PI / 180) >= 0.0) ? emergingAngle : 360 - emergingAngle;

	std::cout << "upcoming angle: " << upcomingAngle << ", emergingAngle: " << emergingAngle << "\n";

	return emergingAngle;
}
