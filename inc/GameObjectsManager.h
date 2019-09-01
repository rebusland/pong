#pragma once
#include "GameObject.h"
#include "GameMessage.h"
#include "Utilities.h"

/**
 * TODO Add singleton constraint! (this constraint must act on derived class as well)
 */
class GameObjectsManager
{
	public:
		/**
		 * Explicitly declare default move operations, since the default dtor was overloaded.
		 * Copy operations are disabled still.
		 */
		GameObjectsManager(GameObjectsManager&&) = default;
		GameObjectsManager& operator=(GameObjectsManager&&) = default;

		GameObjectsManager() { LOG(__func__) }
		virtual ~GameObjectsManager();

		/**
		 * Create a game object of type T, and stores its unique pointer into a map (the key is the objectTag)
		 */
		template<class T>
		void CreateGameObject(const std::string& objectTag)
		{
			// check that the object to create is derived from GameObject and sf::Transformable.
			// since we cannot use virtual inheritance from Transformable, thus ensuring that GameObject is also
			// a sf:Transformable object, we are forced to do this sanity check to avoid dynamic_cast-surprises
			// at runtime.
			static_assert(
				std::is_base_of<sf::Transformable, T>::value,
				"Object not inherited from sf::Transformable"
			);
			static_assert(
				std::is_base_of<GameObject, T>::value,
				"Object not inherited from GameObject"
			);

			std::unique_ptr<GameObject> gameObj = std::make_unique<T>(*this);

			_gameObjects.insert(
				std::make_pair(
					objectTag,
					std::move(gameObj)
				)
			);
		}

		/**
		 * Remove an object tagged by objTag. It removes it
		 * return bool: whether the element was found and successfully removed from the _gameObjects map
		 */
		virtual bool RemoveGameObject(const std::string& objTag);

		virtual void DrawAll(sf::RenderWindow& renderWindow);

		virtual GameMessage UpdateAll();

		virtual void SetGameObjectsDefaultPosition() = 0;

		virtual void CreateGameObjects() = 0;

	protected:
		// TODO implement specific getters for game objects (ball, playerPaddle and computerPaddle)
		GameObject* Get(const std::string& name) const;

	protected:
		std::map<const std::string, std::unique_ptr<GameObject>> _gameObjects;
};
