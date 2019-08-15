#pragma once
#include "Paddle.h"

class PlayerPaddle : public Paddle
{
public:
	~PlayerPaddle();

	GameMessage Update() override;
};
