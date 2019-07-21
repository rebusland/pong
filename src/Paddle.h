#pragma once
#include "VisibleGameObject.h"

class Paddle : public VisibleGameObject
{
public:
	Paddle();
	~Paddle();

	void Draw(sf::RenderWindow& rw) override;

	// the fixed speed at which a paddle can move (right or left)
	static constexpr float PADDLE_SPEED = 600;

	// paddle width
	static float PADDLE_WIDTH;
};
