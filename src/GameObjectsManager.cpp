#include "pch.h"
#include "inc/GameObjectsManager.h"
#include "inc/Utilities.h"
#include "inc/Paddle.h"
#include "inc/Ball.h"
#include "inc/Game.h"

GameObjectsManager::~GameObjectsManager()
{
	LOG(__func__)

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
	{
		return nullptr;
	}
	return results->second.get();

}

void GameObjectsManager::DrawAll(sf::RenderWindow& renderWindow)
{
	std::for_each(
		_gameObjects.cbegin(),
		_gameObjects.cend(),
		[&renderWindow](const auto& pair) { pair.second->Draw(renderWindow); }
	);
}

GameMessage GameObjectsManager::UpdateAll()
{
	GameMessage messageFromObjectsUpdate = GameMessage::EmptySuccessMessage();
	GameMessage currentMessage;

	// update object state and if an error is found the message is returned by the objects manager
	for (const auto& pair : _gameObjects)
	{
		currentMessage = pair.second->Update();
		if (currentMessage.IsError())
		{
			messageFromObjectsUpdate = currentMessage;
		}
	}

	return messageFromObjectsUpdate;
}
