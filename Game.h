#pragma once
#include "Referee.h"
#include "PlayerPaddle.h"
#include "ComputerPaddle.h"
#include "Ball.h"
#include "GameObjectManager.h"

class Game
{

public:
	static void Start();
	static sf::RenderWindow& GetMainWindow();
	// static sf::RenderWindow& GetGameoverWindow();
	static std::vector<sf::FloatRect> GetPaddlesBounds();
	static sf::Vector2f GetBallPosition();

	static constexpr int SCREEN_WIDTH = 800;
	static constexpr int SCREEN_HEIGHT = 480;
	// update time for the window (according to an avarage 30 fps)
	static constexpr float WIN_UPDATE_TIME = (float)1 / 30;

	static constexpr int PADDLE_VERTICAL_DISTANCE = 60;

private:
	static void SetGameObjectsDefaultPosition();
	static bool IsExiting();
	static void GameLoop();

	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting
	};

	static void ShowSplashScreen();
	static void ShowMenu();
	static void ShowGameoverPopup();

	static GameState _gameState;

	static sf::RenderWindow _mainWindow;
	// static sf::RenderWindow _gameoverWindow;

	static GameObjectManager _gameObjectManager;
	static std::unique_ptr<Referee> _referee;
};
