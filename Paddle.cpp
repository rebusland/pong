#include "pch.h"
#include "Game.h"
#include "Paddle.h"

// definition of the static variable PADDLE_WIDTH
float Paddle::PADDLE_WIDTH = 0;

Paddle::Paddle()
{
	Load("images/paddle.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getScale().x / 2, GetSprite().getScale().y / 2);
	Paddle::PADDLE_WIDTH = this->GetBounds().width;
}

Paddle::~Paddle()
{
	std::cout << __func__ << std::endl;
}

void Paddle::Draw(sf::RenderWindow & rw)
{
	VisibleGameObject::Draw(rw);
}

