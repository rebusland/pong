#pragma once
#include "Paddle.h"
#include "Utilities.h"

class PlayerPaddle : public Paddle
{
public:
	PlayerPaddle(const GameObjectsManager& manager) : Paddle(manager) {};
	~PlayerPaddle() { LOG(__func__)	}

	GameMessage Update() override;
};
