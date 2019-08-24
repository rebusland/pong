#pragma once
#include "Paddle.h"
#include "Utilities.h"

class PlayerPaddle : public Paddle
{
public:
	~PlayerPaddle() { LOG(__func__)	}

	GameMessage Update() override;
};
