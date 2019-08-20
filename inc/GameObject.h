#pragma once
#include "GameMessage.h"

/**
 * Generic interface for custom game objects, which can be either of types Sprite or Shape.
 * This interface should remain as general as possible so that it is reusable among different SFML projects.
 */
class GameObject
{
	public:
		virtual ~GameObject() { std::cout << __func__ << std::endl; }

		virtual void Draw(sf::RenderWindow & window) = 0;
		virtual GameMessage Update() = 0;
};