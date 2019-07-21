#include "pch.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"

void Game::Start(void)
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16), "Pang!");
	_mainWindow.setFramerateLimit(30); // limit frame rate

	PlayerPaddle *player1 = new PlayerPaddle();
	player1->SetPosition((SCREEN_WIDTH / 2) - 45, SCREEN_HEIGHT - 60);

	// TODO create a computer paddle, opposing to the user: not easy!

	GameBall *ball = new GameBall();
	ball->SetPosition((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) - 15);

	_gameObjectManager.Add("PaddlePlayer", player1);
	_gameObjectManager.Add("Ball", ball);

	_gameState = Game::ShowingSplash;

	// here is where the game flow logic and event handling is encapsulated
	while (!IsExiting()) {
		GameLoop();
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	_mainWindow.close();
}

bool Game::IsExiting()
{
	return _gameState == Game::Exiting;
}

sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

std::vector<sf::FloatRect> Game::GetPaddlesBounds() 
{
	return _gameObjectManager.GetPaddlesBounds();
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	while (_mainWindow.pollEvent(currentEvent))
	{
		// if closing was requested then we exit from the game loop immediatly
		if (currentEvent.type == sf::Event::Closed) {
			_gameState = Game::Exiting;
			return;
		}
	}

	switch (_gameState) {
	case Game::ShowingMenu:
		ShowMenu();
		break;

	case Game::ShowingSplash:
		ShowSplashScreen();
		break;

	case Game::Playing:
		_mainWindow.clear(sf::Color(0, 0, 0));

		_gameObjectManager.UpdateAll();
		_gameObjectManager.DrawAll(_mainWindow);
		_mainWindow.display();
		break;
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch (result) {
	case MainMenu::Exit:
		_gameState = Game::Exiting;
		break;
	case MainMenu::Play:
		_gameState = Game::Playing;
		break;
	}
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;