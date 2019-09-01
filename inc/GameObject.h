#pragma once
#include "GameMessage.h"
#include "Utilities.h"

// forward declare GameObjectManager (which in turn depends on GameObject) to avoid circular dependency
class GameObjectsManager;

/**
 * Generic interface for custom game objects, which can be either of types Sprite or Shape.
 * This interface should remain as general as possible so that it is reusable among different SFML projects.
 */
class GameObject
{
	public:
		/**
		 * Default move and copy operations are set, since we overloaded the default destructor.
		 */
		GameObject(GameObject&&) = default;
		GameObject& operator=(GameObject&&) = default;

		GameObject(GameObject&) = default;
		GameObject& operator=(const GameObject&) = default;

		// we implicitly enforce a game object to be handled by an objects manager
		GameObject(const GameObjectsManager& manager) : _objectManager{ manager } {}
		virtual ~GameObject() { LOG(__func__) }

		virtual void Draw(sf::RenderWindow & window) = 0;
		virtual GameMessage Update() = 0;

	protected:
		// const reference to the manager the object is spawned from
		const GameObjectsManager& _objectManager;
};
