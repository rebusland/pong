#pragma once
#include "GameMessage.h"

/**
 * Interface for all game objects, which are either of types Sprite or Shape.
 */
class VisibleGameObject
{
public:
	virtual ~VisibleGameObject() 
	{
		std::cout << __func__ << std::endl;
	}

	virtual void Draw(sf::RenderWindow & window) = 0;
	virtual GameMessage Update() = 0;

	virtual sf::FloatRect GetBounds() const = 0;
	virtual void SetScale(float sizeX, float sizeY) = 0;
	virtual void SetPosition(float x, float y) = 0;
	virtual sf::Vector2f GetPosition() const = 0;

	//
	// There is a default implementation for all visible objects.
	// Otherwise, visible object type should implement the logic to check whether it is touching the field borders
	//
	virtual bool IsWinLeftBorderTouched() const;

	virtual bool IsWinRightBorderTouched() const;

	/**
	 * NB the y-coordinate is decreasing in the window object, i.e. y=0 corresponds to the top of the window,
	 * while y=WIN_HEIGHT corresponds to the bottom
	 */
	virtual bool IsWinTopBorderTouched() const;

	virtual bool IsWinBottomBorderTouched() const;
};
