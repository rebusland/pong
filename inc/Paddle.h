#pragma once
#include "VisibleGameObject.h"

class Paddle : 
	public VisibleGameObject,
	public sf::RectangleShape
{
	public:
		Paddle() :
			sf::RectangleShape(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT))
		{
			std::cout << __func__ << std::endl;
		}

		virtual ~Paddle() 
		{
			std::cout << __func__ << std::endl;
		}

		// Inherited via VisibleGameObject
		virtual void Draw(sf::RenderWindow & window) override;
		virtual GameMessage Update() = 0;

		virtual sf::FloatRect GetBounds() const override;
		virtual void SetScale(float sizeX, float sizeY) override;
		virtual void SetPosition(float x, float y) override;
		virtual sf::Vector2f GetPosition() const override;

		/*
		 * Apply an horizontal dx movement to the paddle
		 */
		void MovePaddle(float dx);

		/*
		virtual bool IsWinLeftBorderTouched() const override;
		virtual bool IsWinRightBorderTouched() const override;
		virtual bool IsWinTopBorderTouched() const override;
		virtual bool IsWinBottomBorderTouched() const override;
		*/
	
		// the fixed speed at which a paddle can move (right or left)
		static constexpr float PADDLE_SPEED = 600;

		// paddle width and height
		static constexpr float PADDLE_WIDTH = 100;
		static constexpr float PADDLE_HEIGHT = 20;
};
