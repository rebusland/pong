#include "pch.h"
#include "inc/Paddle.h"

Paddle::Paddle() : _paddleShape(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT))
{
	Load("images/paddle.png");
	assert(IsTextureLoaded());

	Sprite::setOrigin(_paddleShape.getScale().x / 2, _paddleShape.getScale().y / 2);
	// Paddle::PADDLE_WIDTH = this->GetBounds().width;
}

Paddle::~Paddle()
{
	std::cout << __func__ << std::endl;
}
