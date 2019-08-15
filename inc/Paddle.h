#pragma once
#include "SpriteGameObject.h"

class Paddle : public SpriteGameObject
{
public:
	Paddle();
	~Paddle();

	sf::RectangleShape _paddleShape;

	// the fixed speed at which a paddle can move (right or left)
	static constexpr float PADDLE_SPEED = 600;

	// paddle width and height
	static constexpr float PADDLE_WIDTH = 90;
	static constexpr float PADDLE_HEIGHT = 10;
};
