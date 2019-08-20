#pragma once
#include "GameObject.h"
#include "GameMessage.h"

/**
 * TODO Add singleton constraint
 */
class GameObjectsManager
{
	public:
		GameObjectsManager() { std::cout << __func__ << std::endl; }
		~GameObjectsManager();

		/**
		 * Create a game object of type T, and stores its unique pointer into a map (the key is the objectTag)
		 */
		template<class T>
		void CreateGameObject(std::string&& objectTag) 
		{
			// check that the object to create is derived from GameObject and sf::Transformable.
			// since we cannot use virtual inheritance from Transformable, thus ensuring that GameObject is also
			// a sf:Transformable object, we are forced to do this sanity check to avoid dynamic_cast-surprises
			// at runtime
			static_assert(
				std::is_base_of<sf::Transformable, T>::value,
				"Object not inherited from sf::Transformable"
			);
			static_assert(
				std::is_base_of<GameObject, T>::value,
				"Object not inherited from GameObject"
			);

			std::unique_ptr<GameObject> gameObj = std::make_unique<T>();

			_gameObjects.insert(
				std::make_pair(
					std::move(objectTag),
					std::move(gameObj)
				)
			);

			// _gameObjects.insert(std::pair<const std::string, GameObject*>(name, gameObject));
		}

		/**
		 * Remove an object tagged by objTag. It removes it
		 * return bool: whether the element was found and successfully removed from the _gameObjects map
		 */
		bool RemoveGameObject(const std::string& objTag);

		void DrawAll(sf::RenderWindow& renderWindow);

		GameMessage UpdateAll();

		void SetGameObjectsDefaultPosition();

		// METHODS SPECIFIC TO PONG GAME BELOW //

		/**
		 * Used to retrieve all the visible objects bounds: useful in checking whether collision between objects occurs.
		 */
		std::vector<sf::FloatRect> GetPaddlesBounds() const;

		/**
		 * Getter for ball position.
		 */
		sf::Vector2f GetBallPosition() const;

	protected:
		// TODO implement specific getters for game objects (ball, playerPaddle and computerPaddle)
		GameObject* Get(const std::string& name) const;

	protected:
		std::map<const std::string, std::unique_ptr<GameObject>> _gameObjects;
};
