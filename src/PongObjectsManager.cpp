#include "pch.h"
#include "inc/PongObjectsManager.h"

#include "inc/Game.h"

// paddle distance to the upper and lower borders
static constexpr int PADDLE_VERTICAL_DISTANCE = 60;

// tags for the Pong game objects
static const std::string BALL_TAG = "Ball";
static const std::string PLAYER_PADDLE_TAG = "PlayerPaddle";
static const std::string COMPUTER_PADDLE_TAG = "ComputerPaddle";

GameMessage PongObjectsManager::UpdateAll()
{
	// we ensure that paddles are updated BEFORE ball
	GameMessage playerPaddleMsg = GetPlayerPaddle()->Update();
	if (playerPaddleMsg.IsError())
	{
		return playerPaddleMsg;
	}

	GameMessage computerPaddleMsg = GetComputerPaddle()->Update();
	if (computerPaddleMsg.IsError()) 
	{
		return computerPaddleMsg;
	}

	GameMessage ballMsg = GetBall()->Update();
	if (ballMsg.IsError() || ballMsg.IsBallMiss())
	{
		return ballMsg;
	}

	return GameMessage::EmptySuccessMessage();
}

void PongObjectsManager::CreateGameObjects()
{
	CreateGameObject<PlayerPaddle>(PLAYER_PADDLE_TAG);
	CreateGameObject<ComputerPaddle>(COMPUTER_PADDLE_TAG);
	CreateGameObject<GameBall>(BALL_TAG);

	SetGameObjectsDefaultPosition();
}

void PongObjectsManager::SetGameObjectsDefaultPosition()
{
	// ball default position is at the center of the window
	GetBall()->setPosition(
		Game::FIELD_WIDTH / 2,
		Game::FIELD_HEIGHT / 2 - GameBall::BALL_RADIUS / 2
	);
	// also, the ball random starting angle is specified
	GetBall()->SetupRandomStartingAngle();

	// player and computer paddle are at the centered and in opposite sides of the field
	GetPlayerPaddle()->setPosition(
		Game::FIELD_WIDTH / 2 - Paddle::PADDLE_WIDTH / 2,
		Game::FIELD_HEIGHT - PADDLE_VERTICAL_DISTANCE
	);
	
	GetComputerPaddle()->setPosition(
		Game::FIELD_WIDTH / 2 - Paddle::PADDLE_WIDTH / 2,
		PADDLE_VERTICAL_DISTANCE
	);
}

GameBall* PongObjectsManager::GetBall() const
{
	return GetObject<GameBall>(BALL_TAG);
}

PlayerPaddle* PongObjectsManager::GetPlayerPaddle() const 
{
	return GetObject<PlayerPaddle>(PLAYER_PADDLE_TAG);
}

ComputerPaddle* PongObjectsManager::GetComputerPaddle() const 
{
	return GetObject<ComputerPaddle>(COMPUTER_PADDLE_TAG);
}

std::vector<sf::FloatRect> PongObjectsManager::GetPaddlesBounds() const
{
	std::vector<sf::FloatRect> boundsVec;
	boundsVec.push_back(GetPlayerPaddle()->getGlobalBounds());
	boundsVec.push_back(GetComputerPaddle()->getGlobalBounds());

	return boundsVec;
}

sf::FloatRect PongObjectsManager::GetComputerPaddleBounds() const 
{
	return GetComputerPaddle()->getGlobalBounds();
}

sf::FloatRect PongObjectsManager::GetPlayerPaddleBounds() const 
{
	return GetPlayerPaddle()->getGlobalBounds();
}

sf::Vector2f PongObjectsManager::GetBallPosition() const
{
	return GetBall()->getPosition();
}
