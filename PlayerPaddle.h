#pragma once
#include "Paddle.h"
#include "VisibleGameObject.h"

class PlayerPaddle : public Paddle
{
public:
	~PlayerPaddle();

	void Update() override;
};
