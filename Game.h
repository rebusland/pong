#pragma once
#include "PlayerPaddle.h"
#include "Ball.h"
#include "GameObjectManager.h"

class Game
{

public:
	static void Start();
	static sf::RenderWindow& GetWindow();
	static std::vector<sf::FloatRect> GetPaddlesBounds();

	const static int SCREEN_WIDTH = 800;
	const static int SCREEN_HEIGHT = 480;
	// update time for the window (according to an avarage 30 fps)
	static constexpr float WIN_UPDATE_TIME = (float)1 / 30;

private:
	static bool IsExiting();
	static void GameLoop();

	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting
	};

	static void ShowSplashScreen();
	static void ShowMenu();

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	static GameObjectManager _gameObjectManager;
};
