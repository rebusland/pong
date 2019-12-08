#pragma once
#include "SpriteWrapper.h"
#include "GameObject.h"
#include "Utilities.h"

class GameBall : 
	public virtual GameObject,
	public virtual SpriteWrapper
{
	public:
		GameBall(const GameObjectsManager& manager);
		virtual ~GameBall() { LOG(__func__) }

		// TODO is it useful to move this somewhere else?
		enum class FieldSide
		{
			None,
			PlayerSide,
			ComputerSide
		};

		void SetupRandomStartingAngle(const FieldSide&);
		void SetupRandomStartingAngle();

		GameMessage Update() override;
		void Draw(sf::RenderWindow& rw) override 
		{ 
			rw.draw(*this); // Ball, inheriting from Sprite object, has a proper definition for draw method.
		}

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
		static constexpr float BALL_RADIUS = 20;

		// angle spread allowed for the ball after a paddle hit
		static constexpr float BALL_PADDLE_MAX_ANGLE_SPREAD = 45;

		// max (half-)angle spread when ball is first thrown at the beginning of the match
		// NB full spread is twice this value
		static constexpr int BALL_INITIAL_HALF_ANGLE_SPREAD = 30;

	protected:
		/**
		 * Floor ball left side to zero and cap its right side to FIELD_WIDTH.
		 * in case of collision with a border, reflect ball's angle.
		 * Also, ball must not penetrate inside paddles.
		 */
		virtual void EnforceValidPosition() override;

	private:
		/*
		 * Current angle at which the ball is moving.
		 * In case a paddle or the windows border are hit the angle is reflected
		 */
		double _angle;
};
