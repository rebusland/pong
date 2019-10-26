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
		 * Used to check whether collision between ball and paddles.
		 */
		std::vector<sf::FloatRect> GetPaddlesBounds() const;

		sf::FloatRect GetComputerPaddleBounds() const;
		sf::FloatRect GetPlayerPaddleBounds() const;

		sf::Vector2f GetBallPosition() const;
};
