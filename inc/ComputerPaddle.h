#pragma once
#include "Paddle.h"
#include "Utilities.h"

class ComputerPaddle : public Paddle
{
public:
	ComputerPaddle(const GameObjectsManager& manager) : Paddle(manager) {}
	~ComputerPaddle() { LOG(__func__) }

	/*
 	 * Implements computer paddle movements logic.
	 * TODO change computer opposition ability according to a difficulty level.
	 */
	GameMessage Update() override;
};