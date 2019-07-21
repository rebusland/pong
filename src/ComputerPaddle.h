#pragma once
#include "Paddle.h"
#include "VisibleGameObject.h"

class ComputerPaddle : public Paddle
{
public:
	~ComputerPaddle();

	/*
 	 * Implements computer paddle movements logic.
	 * TODO change computer opposition ability according to a difficulty level.
	 */
	GameMessage Update() override;
};