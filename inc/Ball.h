#pragma once
#include "SpriteGameObject.h"

class GameBall : public SpriteGameObject
{
	public:
		GameBall();
		virtual ~GameBall() { std::cout << __func__ << std::endl; }

		GameMessage Update() override;
		void Draw(sf::RenderWindow& rw) override { SpriteGameObject::Draw(rw); }

		/**
		 * Algorithm to calculate the ball emerging angle after a collision with a paddle.
		 * This emerging angle depends from the part of the paddle which hits the ball: it should somehow
		 * simulates the player hitting forehand of backhand.
		 */
		double ComputeBallPaddleAngle(double upcomingAngle, const sf::FloatRect& paddleBounds) const;
	
	public:
		// ball velocity modulus (assumed constant among the shots from the two players)
		static constexpr float BALL_SPEED = 600;

		// ball radius in pixels, used when a resize of a ball image for the sprite is required
		static constexpr float BALL_RADIUS = 30;

		// angle spread allowed for the ball after a paddle hit
		static constexpr float BALL_ANGLE_SPREAD = 45;

	private:
		/*
		 * Current angle at which the ball is moving.
		 * In case a paddle or the windows border are hit the angle is reflected (according to the paddle speed)
		 */
		double _angle;

		bool _hasCollidedWithPaddle = false;
};
