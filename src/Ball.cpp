#include "pch.h"
#include "inc/Ball.h"
#include "inc/Game.h"

GameBall::GameBall() : SpriteWrapper(BALL_DEFAULT_IMAGE_PATH)
{
	// resize ball image so that at the end we get a ball with radius BALL_RADIUS
	SetSize(BALL_RADIUS , BALL_RADIUS);

	// origin for the ball will be its center (by default it is the top left corner of the enclosing rectangle)
	setOrigin(BALL_RADIUS / 2, BALL_RADIUS / 2);

	// initialize random seed:
	srand(time(NULL));

	// random angle at which the ball is first thrown (in the intervals [45, 135] and [225, 315] degrees) 
	_angle = 45 + rand() % 90;
	_angle = (rand() % 2 == 0) ? _angle : 180 + _angle;
}

GameMessage GameBall::Update()
{
	double startingPositionY = getPosition().y;

	// if the bottom border of the window is reached than the player on that side (user for the moment) lose the game
	// NB the y-coordinate is decreasing in the window object, i.e. y=0 corresponds to the top of the window,
	// while y=WIN_HEIGHT corresponds to the bottom
	if (startingPositionY >= Game::FIELD_HEIGHT - getGlobalBounds().height)
	{
		return GameMessage(GameMessage::message_type_t::PLAYER_MISS, "player paddle missed the ball!", false);
	}
	// top border of the window reached by the ball ==> computer miss
	if (startingPositionY <= 0)
	{
		return GameMessage(GameMessage::message_type_t::COMPUTER_MISS, "Computer paddle missed the ball!", false);
	}

	// TODO improve logic of collision detection between paddle and ball
	// enforce ball's y position so that it does not penetrate into the paddle object (?)
	bool collisionWithPaddle { false };

	// get bounds for both computer and player paddles, and check if ball collided with one of those
	for (auto x : Game::GetPaddlesBounds())
	{
		// if ball collides with paddle bounds it bounces back according to the current paddle motion
		if (getGlobalBounds().intersects(x))
		{
			LOG("Collision!");

			if (!_hasCollidedWithPaddle)
				_angle = ComputeBallPaddleAngle(_angle, x);

			collisionWithPaddle = true;
		}
	}

	_hasCollidedWithPaddle = collisionWithPaddle;

	float dx = BALL_SPEED * cos(_angle * PI / 180) * Game::WIN_UPDATE_TIME; // dx = v * cos(angle) * dt
	float dy = BALL_SPEED * sin(_angle * PI / 180) * Game::WIN_UPDATE_TIME; // dy = v * sin(angle) * dt

	Sprite::move(dx, dy);

	// in any case, enforce ball to be in the field space: 
	// floor ball left side to zero and cap its right side to FIELD_WIDTH.
	// in case of collision with a border, reflect ball's angle.
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

	// if no problem occured an empty success message is sent
	return GameMessage::EmptySuccessMessage();
}

double GameBall::ComputeBallPaddleAngle(double upcomingAngle, const sf::FloatRect& paddleBounds) const
{
	double ballCenter = getGlobalBounds().left + getGlobalBounds().width / 2;
	double paddleCenterX = paddleBounds.left + paddleBounds.width / 2;

	LOG("ball left bound: " << getGlobalBounds().left << ", ball width: " << getGlobalBounds().width);
	LOG("paddle left bound: " << paddleBounds.left << ", paddle width: " << paddleBounds.width);
	LOG("ball center: " << ballCenter << ", paddleCenterX: " << paddleCenterX);

	// 270 (reverse direction) + angle spread (backhand or forehand)
	double emergingAngle = 270 + BALL_ANGLE_SPREAD * (ballCenter - paddleCenterX) / (paddleBounds.width / 2);

	emergingAngle = (std::sin(upcomingAngle * PI / 180) >= 0.0) ? emergingAngle : 360 - emergingAngle;

	LOG("upcoming angle: " << upcomingAngle << ", emergingAngle: " << emergingAngle);

	return emergingAngle;
}
