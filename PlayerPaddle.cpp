#include "pch.h"
#include "PlayerPaddle.h"
#include "Game.h"

PlayerPaddle::PlayerPaddle() 
{
	Load("images/paddle.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getScale().x / 2, GetSprite().getScale().y / 2);
}

PlayerPaddle::~PlayerPaddle()
{
	std::cout << __func__ << std::endl;
}

void PlayerPaddle::Draw(sf::RenderWindow & rw)
{
	VisibleGameObject::Draw(rw);
}

void PlayerPaddle::Update()
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
	GetSprite().move(speed * Game::WIN_UPDATE_TIME, 0);
}
