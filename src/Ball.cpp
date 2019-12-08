#include "pch.h"
#include "inc/Ball.h"
#include "inc/Game.h"

GameBall::GameBall(const GameObjectsManager& manager) :
	GameObject(manager),
	SpriteWrapper(BALL_DEFAULT_IMAGE_PATH)
{
	// resize ball image so that at the end we get a ball with radius BALL_RADIUS
	SetSize(BALL_RADIUS , BALL_RADIUS);

	// origin for the ball will be its center (by default it is the top left corner of the enclosing rectangle)
	setOrigin(BALL_RADIUS / 2, BALL_RADIUS / 2);

	SetupRandomStartingAngle();
}

void GameBall::SetupRandomStartingAngle()
{
	SetupRandomStartingAngle(FieldSide::None);
}

void GameBall::SetupRandomStartingAngle(const FieldSide& fieldSide)
{
	// initialize random seed:
	srand(time(NULL));

	// random angle at which the ball is first thrown
	// (in the intervals [45, 135] and/or [225, 315] degrees depending on specification on fieldSide) 
	int rnd = rand();
	
	// generate angle in the interval (90 - HALF_SPREAD, 90 + HALF_SPREAD)
	_angle = 90 + (rnd % 2) * (rnd % BALL_INITIAL_HALF_ANGLE_SPREAD);
	
	switch (fieldSide)
	{
		case FieldSide::ComputerSide:
			_angle += 180;
			break;
		case FieldSide::PlayerSide:
			break;
		default: // None => random side
			_angle += (rnd % 2) * 180;
			break;
	}
}

GameMessage GameBall::Update()
{
	// if the BOTTOM border of the window is reached (NB y coordinate is decreasing) than the player on lose the game
	if (getPosition().y >= Game::FIELD_HEIGHT - getGlobalBounds().height)
	{
		return GameMessage(GameMessage::message_type_t::PLAYER_MISS, "player paddle missed the ball!", false);
	}
	// TOP border of the window reached by the ball ==> computer miss
	if (getPosition().y <= 0)
	{
		return GameMessage(GameMessage::message_type_t::COMPUTER_MISS, "Computer paddle missed the ball!", false);
	}

	// Update position
	float dx = BALL_SPEED * cos(_angle * PI / 180) * Game::WIN_UPDATE_TIME; // dx = v * cos(angle) * dt
	float dy = BALL_SPEED * sin(_angle * PI / 180) * Game::WIN_UPDATE_TIME; // dy = v * sin(angle) * dt

	Sprite::move(dx, dy);

	/*
	 * Check for collision with paddles to compute the new angle for ball's motion
	 */
	const auto& pongObjManager = static_cast<const PongObjectsManager&>(_objectManager);

	// get bounds for both computer and player paddles, and check if ball collided with one of those
	for (auto x : pongObjManager.GetPaddlesBounds())
	{
		// if ball collides with paddle bounds it bounces back according to the current paddle motion
		if (getGlobalBounds().intersects(x))
		{
			LOG("Collision!");
			_angle = ComputeBallPaddleAngle(_angle, x);
		}
	}

	/*
	 * In any case, enforce ball to be in the field space, handling possible ball reflection
	 */
	EnforceValidPosition();

	// if no problem occured an empty success message is sent
	return GameMessage::EmptySuccessMessage();
}

void GameBall::EnforceValidPosition()
{
	const auto& pongObjManager = static_cast<const PongObjectsManager&>(_objectManager);

	// do not penetrate in paddle if now ball is within computer or player paddles borders
	auto computerBounds = pongObjManager.GetComputerPaddleBounds();
	auto playerBounds = pongObjManager.GetPlayerPaddleBounds();

	if (getGlobalBounds().intersects(computerBounds))
	{
		setPosition(getPosition().x, computerBounds.top + Paddle::PADDLE_HEIGHT);
	}
	else if (getGlobalBounds().intersects(playerBounds))
	{
		setPosition(getPosition().x, playerBounds.top - BALL_RADIUS);
	}

	// enforce field position
	if (getGlobalBounds().left <= 0)
	{
		setPosition(0, getPosition().y);
		_angle = 180 - _angle;
	}
	else if (getGlobalBounds().left >= Game::FIELD_WIDTH - getGlobalBounds().width)
	{
		setPosition(Game::FIELD_WIDTH - getGlobalBounds().width, getPosition().y);
		_angle = 180 - _angle;
	}
}

double GameBall::ComputeBallPaddleAngle(double upcomingAngle, const sf::FloatRect& paddleBounds) const
{
	double ballCenter = getGlobalBounds().left + getGlobalBounds().width / 2;
	double paddleCenterX = paddleBounds.left + paddleBounds.width / 2;

	LOG("ball left bound: " << getGlobalBounds().left << ", ball width: " << getGlobalBounds().width);
	LOG("paddle left bound: " << paddleBounds.left << ", paddle width: " << paddleBounds.width);
	LOG("ball center: " << ballCenter << ", paddleCenterX: " << paddleCenterX);

	// 270 (reverse direction) + angle spread (backhand or forehand)
	double emergingAngle = 270 + BALL_PADDLE_MAX_ANGLE_SPREAD * (ballCenter - paddleCenterX) / (paddleBounds.width / 2);

	emergingAngle = (std::sin(upcomingAngle * PI / 180) >= 0.0) ? emergingAngle : 360 - emergingAngle;

	LOG("upcoming angle: " << upcomingAngle << ", emergingAngle: " << emergingAngle);

	return emergingAngle;
}
