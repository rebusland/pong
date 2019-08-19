#pragma once
#include "GameObject.h"

class Paddle : 
	public GameObject,
	public sf::RectangleShape
{
	public:
		Paddle();

		virtual ~Paddle() {	std::cout << __func__ << std::endl; }

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

		// paddle horizontal position is bounded within field borders
		void EnforceValidPosition();

	public:
		// the fixed speed at which a paddle can move (right or left)
		static constexpr float PADDLE_SPEED = 600;

		// paddle width and height
		static constexpr float PADDLE_WIDTH = 90;
		static constexpr float PADDLE_HEIGHT = 10;
	
	protected:
		bool _isLeftBorderTouched;
		bool _isRightBorderTouched;
};
