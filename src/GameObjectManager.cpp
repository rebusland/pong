#include "pch.h"
#include "inc/GameObjectManager.h"
#include "inc/Paddle.h"
#include "inc/Ball.h"
#include "inc/Game.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}

void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject)
{
	_gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

void GameObjectManager::Remove(std::string name)
{
	std::map<std::string, VisibleGameObject*>::iterator results = _gameObjects.find(name);
	if (results != _gameObjects.end())
	{
		delete results->second;
		_gameObjects.erase(results);
	}
}

VisibleGameObject* GameObjectManager::Get(std::string name) const
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
	if (results == _gameObjects.end())
		return NULL;
	return results->second;

}

std::vector<sf::FloatRect> GameObjectManager::GetPaddlesBounds() const
{
	std::vector<sf::FloatRect> boundsVec;
	for (auto const& x : _gameObjects)
	{
		// check if visible object from the map is a paddle object
		if (dynamic_cast<Paddle*>(x.second) != nullptr)
		{
			boundsVec.push_back(x.second->GetBounds());
		}
	}
	return boundsVec;
}

sf::Vector2f GameObjectManager::GetBallPosition() const
{
	for (auto const& x : _gameObjects)
	{
		// check if visible object from the map is a ball object
		if (static_cast<GameBall*>(x.second) != nullptr)
		{
			return x.second->GetPosition();
		}
	}

	// if no ball is found return empty vector
	return sf::Vector2f();
}

int GameObjectManager::GetObjectCount() const
{
	return _gameObjects.size();
}


void GameObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->Draw(renderWindow);
		itr++;
	}
}

GameMessage GameObjectManager::UpdateAll()
{
	GameMessage messageFromObjectsUpdate = GameMessage::EmptySuccessMessage();

	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();

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

void GameObjectManager::SetGameObjectsDefaultPosition()
{
	// ball default position is at the center of the window
	Get("Ball")->SetPosition((Game::FIELD_WIDTH / 2), (Game::FIELD_HEIGHT / 2) - GameBall::BALL_RADIUS * 0.5);

	// player and computer paddle are at the centered and in opposite sides of the field
	Get("PaddlePlayer")->SetPosition((Game::FIELD_WIDTH / 2) - Paddle::PADDLE_WIDTH * 0.5, Game::FIELD_HEIGHT - Game::PADDLE_VERTICAL_DISTANCE);
	Get("ComputerPaddle")->SetPosition((Game::FIELD_WIDTH / 2) - Paddle::PADDLE_WIDTH * 0.5, Game::PADDLE_VERTICAL_DISTANCE);
}
