#pragma once
#include "Paddle.h"

class PlayerPaddle : public Paddle
{
public:
	~PlayerPaddle() 
	{
		std::cout << __func__ << std::endl;
	}

	GameMessage Update() override;
};
