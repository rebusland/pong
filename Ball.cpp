#include "pch.h"
#include "Ball.h"
#include "Game.h"

GameBall::GameBall()
{
	Load("images/ball.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getScale().x / 2, GetSprite().getScale().y / 2);

	// initialize random seed:
	srand(time(NULL));

	// random angle at which the ball is first thrown (between 0 and 360) 
	_angle = rand() % 360;
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
	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !IsWinLeftBorderTouched())
	{
		GetSprite().move(-5, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !IsWinRightBorderTouched())
	{
		GetSprite().move(5, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
	{
		GetSprite().move(0, -5);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
	{
		GetSprite().move(0, 5);
	}

	if (GetSprite().getGlobalBounds().intersects(Game::GetPaddlesBounds().at(0))) 
	{
		std::cout << "Collision \n";
	}

	*/

	// std::cout << GetPosition().x << ", " << GetPosition().y << std::endl;

	// if the bottom border of the window is reached than the player on that side (user for the moment) lose the game
	if (IsWinBottomBorderTouched())
	{
		std::cout << "User lost the game!!" << std::endl;
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

	// get paddles bounds
	for (auto x : Game::GetPaddlesBounds())
	{
		// 	std::cout << "Paddle bounds: " << x.left << ", " << x.width << " ; " << x.top << " , " << x.height << std::endl; 
		// if ball collides with paddle bounds it bounces back according to the current paddle motion
		if (GetSprite().getGlobalBounds().intersects(Game::GetPaddlesBounds().at(0)))
		{
			std::cout << "Collision! \n";
			_angle = -_angle;
		}
	}

	float dx = BALL_SPEED * cos(_angle * PI / 180) * Game::WIN_UPDATE_TIME; // dx = v * cos(angle) * dt
	float dy = BALL_SPEED * sin(_angle * PI / 180) * Game::WIN_UPDATE_TIME; // dy = v * sin(angle) * dt

	GetSprite().move(dx, dy);
}

