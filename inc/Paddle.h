#pragma once
#include "GameObject.h"
#include "Utilities.h"

class Paddle : 
	public GameObject,
	public sf::RectangleShape
{
	public:
		Paddle(const GameObjectsManager& manager);

		virtual ~Paddle() {	LOG(__func__) }

		// Inherited via VisibleGameObject
		virtual void Draw(sf::RenderWindow & window) override
		{
			window.draw(*this); // Paddle, as a RectangleShape, has a proper implementation of draw method
		}

		// this should be overriden still
		virtual GameMessage Update() = 0;

		/*
		 * Apply an horizontal dx movement to the paddle
		 */
		void MovePaddle(float dx) 
		{ 
			RectangleShape::move(dx, 0); // dy = 0 
		}

	public:
		// the fixed speed at which a paddle can move (right or left)
		static constexpr float PADDLE_SPEED = 600;

		// paddle width and height
		static constexpr float PADDLE_WIDTH = 90;
		static constexpr float PADDLE_HEIGHT = 10;
	
	protected:
		// paddle horizontal position is bounded within field borders
		virtual void EnforceValidPosition() override;

		bool _isLeftBorderTouched;
		bool _isRightBorderTouched;
};
