#pragma once
#include "Paddle.h"
#include "Utilities.h"

class ComputerPaddle : public Paddle
{
	public:
		ComputerPaddle(const GameObjectsManager& manager) : 
			Paddle(manager),
			_responsiveness{Normal} // TODO initialized according to game difficulty level
		{
			srand(time(NULL));
		}

		~ComputerPaddle() { LOG(__func__) }

		/**
		 * The computer ability is synthetized by its "responsiveness" (i.e. reflexes) to ball movement.
		 * The value is expressed in percentage term.
		 */
		enum Responsiveness {
			Slow = 60,
			Normal = 70,
			Quick = 85,
			Perfect = 100
		};

		/*
 		 * Implements computer paddle movements logic.
		 * The ability of the computer is set by the game difficulty level.
		 */
		GameMessage Update() override;

	private:
		Responsiveness _responsiveness;
};