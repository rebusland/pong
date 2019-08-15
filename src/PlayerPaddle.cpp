#include "pch.h"
#include "inc/PlayerPaddle.h"
#include "inc/Game.h"

PlayerPaddle::~PlayerPaddle()
{
	std::cout << __func__ << std::endl;
}

GameMessage PlayerPaddle::Update()
{
	float speed = 0.0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !IsWinLeftBorderTouched())
	{
		speed = - PADDLE_SPEED;
	} 
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !IsWinRightBorderTouched())
	{
		speed = PADDLE_SPEED;
	}

	// std::cout << "old position: " << this->GetPosition().x << std::endl;
	// std::cout << "Paddle bounds: " << GetSprite().getGlobalBounds().left << ", " << GetSprite().getGlobalBounds().width << std::endl;

	// increment current position by dx = v * dt
	Sprite::move(speed * Game::WIN_UPDATE_TIME, 0);

	// if no problem were encountered then an empty success message is returned
	return GameMessage::EmptySuccessMessage();
}
