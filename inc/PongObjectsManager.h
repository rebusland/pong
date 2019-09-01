#pragma once
#include "GameObjectsManager.h"

class PongObjectsManager : public GameObjectsManager
{
	public:
		PongObjectsManager() { LOG(__func__) };
		~PongObjectsManager() { LOG(__func__) };

		void CreateGameObjects() override;

		void SetGameObjectsDefaultPosition() override;

		GameMessage UpdateAll() override;

		/**
		 * Used to retrieve all the visible objects bounds: useful in checking whether collision between objects occurs.
		 */
		std::vector<sf::FloatRect> GetPaddlesBounds() const;

		/**
		 * Getter for ball position.
		 */
		sf::Vector2f GetBallPosition() const;
};
