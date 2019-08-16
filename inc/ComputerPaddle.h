#pragma once
#include "Paddle.h"

class ComputerPaddle : public Paddle
{
public:
	~ComputerPaddle()
	{
		std::cout << __func__ << std::endl;
	}

	/*
 	 * Implements computer paddle movements logic.
	 * TODO change computer opposition ability according to a difficulty level.
	 */
	GameMessage Update() override;
};