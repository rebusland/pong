#pragma once
#include "GameObjectsManager.h"
#include "inc/Paddle.h"
#include "inc/PlayerPaddle.h"
#include "inc/ComputerPaddle.h"
#include "inc/Ball.h"

class PongObjectsManager : public GameObjectsManager
{
	public:
		PongObjectsManager() { LOG(__func__) };
		~PongObjectsManager() { LOG(__func__) };

		void CreateGameObjects() override;

		void SetGameObjectsDefaultPosition() override;

		GameMessage UpdateAll() override;

		GameBall* GetBall() const;
		PlayerPaddle* GetPlayerPaddle() const;
		ComputerPaddle* GetComputerPaddle() const;

		/**
		 * Used to retrieve all the visible objects bounds: useful in checking whether collision between objects occurs.
		 */
		std::vector<sf::FloatRect> GetPaddlesBounds() const;

		/**
		 * Getter for ball position.
		 */
		sf::Vector2f GetBallPosition() const;
};
