#pragma once
#include "visiblegameobject.h"


class GameBall : public VisibleGameObject
{
public:
	GameBall();
	virtual ~GameBall();

	void Update() override;
	void Draw(sf::RenderWindow& rw) override;

	double ComputeBallPaddleAngle(double upcomingAngle, const sf::FloatRect& paddleBounds) const;
	
public:
	// ball velocity modulus (assumed constant among the shots from the two players)
	static constexpr float BALL_SPEED = 200;

	// ball width
	static float BALL_WIDTH;

private:
	/*
	 * Current angle at which the ball is moving.
	 * In case a paddle or the windows border are hit the angle is reflected (according to the paddle speed)
	 */
	double _angle;

	bool _hasCollided = false;

};
