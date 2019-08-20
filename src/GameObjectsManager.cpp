#include "pch.h"
#include "inc/GameObjectsManager.h"
#include "inc/Paddle.h"
#include "inc/Ball.h"
#include "inc/Game.h"

GameObjectsManager::~GameObjectsManager()
{
	std::cout << __func__ << std::endl;

	// remove all entries in the gameObjects map, where objects unique_ptrs are stored.
	_gameObjects.clear();
}

bool GameObjectsManager::RemoveGameObject(const std::string& tag)
{
	auto objIterator = _gameObjects.find(tag);
	if (objIterator != _gameObjects.end())
	{
		_gameObjects.erase(objIterator);
		return true;
	}

	return false;
}

GameObject* GameObjectsManager::Get(const std::string& name) const
{
	auto results = _gameObjects.find(name);
	if (results == _gameObjects.end())
		return nullptr;
	return results->second.get();

}

void GameObjectsManager::DrawAll(sf::RenderWindow& renderWindow)
{
	auto itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->Draw(renderWindow);
		itr++;
	}
}

GameMessage GameObjectsManager::UpdateAll()
{
	GameMessage messageFromObjectsUpdate = GameMessage::EmptySuccessMessage();

	auto itr = _gameObjects.begin();

	while (itr != _gameObjects.end())
	{
		// update object state and if an error is found the message is returned by the objects manager
		GameMessage currentMessage = itr->second->Update();
		if (currentMessage.IsError() || currentMessage.IsBallMiss())
		{
			messageFromObjectsUpdate = currentMessage;
		}
		itr++;
	}

	return messageFromObjectsUpdate;
}

void GameObjectsManager::SetGameObjectsDefaultPosition()
{
	// ball default position is at the center of the window
	dynamic_cast<sf::Transformable*>(Get("Ball"))->setPosition((Game::FIELD_WIDTH / 2), (Game::FIELD_HEIGHT / 2) - GameBall::BALL_RADIUS * 0.5);

	// player and computer paddle are at the centered and in opposite sides of the field
	dynamic_cast<sf::Transformable*>(Get("PlayerPaddle"))->setPosition((Game::FIELD_WIDTH / 2) - Paddle::PADDLE_WIDTH * 0.5, Game::FIELD_HEIGHT - Game::PADDLE_VERTICAL_DISTANCE);
	dynamic_cast<sf::Transformable*>(Get("ComputerPaddle"))->setPosition((Game::FIELD_WIDTH / 2) - Paddle::PADDLE_WIDTH * 0.5, Game::PADDLE_VERTICAL_DISTANCE);
}

std::vector<sf::FloatRect> GameObjectsManager::GetPaddlesBounds() const
{
	std::vector<sf::FloatRect> boundsVec;
	for (auto const& x : _gameObjects)
	{
		// check if visible object from the map is a paddle object
		auto paddlePtr = dynamic_cast<Paddle*>(x.second.get());
		if (paddlePtr != nullptr)
		{
			boundsVec.push_back(paddlePtr->getGlobalBounds());
		}
	}
	return boundsVec;
}

sf::Vector2f GameObjectsManager::GetBallPosition() const
{
	for (auto const& x : _gameObjects)
	{
		// check if visible object from the map is a ball object
		auto ballPtr = dynamic_cast<GameBall*>(x.second.get());
		if (ballPtr != nullptr)
		{
			return ballPtr->getPosition();
		}
	}

	// if no ball is found return empty vector
	return sf::Vector2f();
}
