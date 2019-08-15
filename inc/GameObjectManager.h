#pragma once
#include "VisibleGameObject.h"
#include "GameMessage.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Add(std::string name, VisibleGameObject* gameObject);
	void Remove(std::string name);
	int GetObjectCount() const;

	// TODO implement specific getters for game objects (ball, playerPaddle and computerPaddle)
	VisibleGameObject* Get(std::string name) const;

	/**
	 * Used to retrieve all the visible objects bounds: useful in checking whether collision between objects occurs.
	 */
	std::vector<sf::FloatRect> GetPaddlesBounds() const;

	/**
	 * Getter for ball position.
	 */
	sf::Vector2f GetBallPosition() const;

	void DrawAll(sf::RenderWindow& renderWindow);

	GameMessage UpdateAll();

private:
	std::map<std::string, VisibleGameObject*> _gameObjects;

	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string, VisibleGameObject*> & p) const
		{
			delete p.second;
		}
	};
};
