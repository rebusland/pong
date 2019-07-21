#include "pch.h"
#include "Game.h"
#include "GameObjectManager.h"

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
	GameMessage messageFromObjectsUpdate("", false);

	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();

	while (itr != _gameObjects.end())
	{
		// update object state and if an error is found the message is returned by the objects manager
		GameMessage currentMessage = itr->second->Update();
		if (currentMessage.IsError())
		{
			messageFromObjectsUpdate = currentMessage;
		}
		itr++;
	}

	return messageFromObjectsUpdate;
}
