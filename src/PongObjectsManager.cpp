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
	GameMessage messageFromObjectsUpdate = GameMessage::EmptySuccessMessage();
	GameMessage currentMessage;

	// update object state and if an error is found the message is returned by the objects manager
	for (const auto& pair : _gameObjects)
	{
		currentMessage = pair.second->Update();
		if (currentMessage.IsBallMiss() || currentMessage.IsError())
		{
			messageFromObjectsUpdate = currentMessage;
		}
	}

	return messageFromObjectsUpdate;
}

void PongObjectsManager::CreateGameObjects()
{
	CreateGameObject<PlayerPaddle>(PLAYER_PADDLE_TAG);
	CreateGameObject<ComputerPaddle>(COMPUTER_PADDLE_TAG);
	CreateGameObject<GameBall>(BALL_TAG);
}

void PongObjectsManager::SetGameObjectsDefaultPosition()
{
	// ball default position is at the center of the window
	GetBall()->setPosition(
		Game::FIELD_WIDTH / 2,
		Game::FIELD_HEIGHT / 2 - GameBall::BALL_RADIUS / 2
	);

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

	Paddle* playerPaddlePtr = GetPlayerPaddle();
	if (playerPaddlePtr != nullptr)
	{
		boundsVec.push_back(playerPaddlePtr->getGlobalBounds());
	}

	Paddle* computerPaddlePtr = GetComputerPaddle();
	if (computerPaddlePtr != nullptr)
	{
		boundsVec.push_back(computerPaddlePtr->getGlobalBounds());
	}

	return boundsVec;
}

sf::Vector2f PongObjectsManager::GetBallPosition() const
{
	GameBall* ballPtr = GetBall();
	if (ballPtr != nullptr)
	{
		return ballPtr->getPosition();
	}

	// if no ball is found return empty vector
	return sf::Vector2f();
}
