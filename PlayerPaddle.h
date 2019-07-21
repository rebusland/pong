#pragma once
#include "VisibleGameObject.h"

class PlayerPaddle : public VisibleGameObject
{
public:
	PlayerPaddle();
	~PlayerPaddle();

	void Update() override;
	void Draw(sf::RenderWindow& rw) override;

private:
	// the fixed speed at which a paddle can move (right or left)
	static constexpr float PADDLE_SPEED = 600;
};
