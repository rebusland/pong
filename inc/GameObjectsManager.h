#pragma once
#include "GameObject.h"
#include "GameMessage.h"

class GameObjectsManager
{
public:
	GameObjectsManager() { std::cout << __func__ << std::endl; }
	~GameObjectsManager();

	void Add(std::string name, GameObject* gameObject);
	void Remove(std::string name);
	int GetObjectCount() const;

	// TODO implement specific getters for game objects (ball, playerPaddle and computerPaddle)
	GameObject* Get(std::string name) const;

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

	void SetGameObjectsDefaultPosition();

private:
	std::map<const std::string, GameObject*> _gameObjects;

	struct GameObjectDeallocator
	{
		void operator()(const std::pair<const std::string, GameObject*> & p) const
		{
			delete p.second;
		}
	};
};
