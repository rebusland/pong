#include "pch.h"
#include "inc/Game.h"
#include "inc/MenuScreen.h"

MenuScreen::MenuScreen(sf::RenderWindow& win, sf::Font& font) : Screen(win)
{
	_selectionItems.emplace_back(
		sf::Text("Play", font),
		[]() {
			std::cout << "Go to Play!" << std::endl;
			Game::ResetGame();
			// SetGameState(Game::State::Playing);
		}
	);

	_selectionItems.emplace_back(
		sf::Text("Options", font),
		[]() { SetGameState(Game::GameState::ChangingSettings); }
	);

	_selectionItems.emplace_back(
		sf::Text("Quit", font),
		[]() { SetGameState(Game::GameState::Exiting); }
	);

	// default: the first selection item in the list is selected
	_selectionItems[0].Select();

	alignMultiTextVertically(_selectionItems, sf::Vector2f(0, 0), sf::Vector2f(_win.getSize()));
}

void MenuScreen::Open()
{
	while (_win.isOpen() && Game::_gameState == Game::GameState::ShowingMenu) {
		sf::Event event;
		while (_win.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				_win.close();
			}

			HandleEvent(event);
		}

		_win.clear();
		for (const auto& item : _selectionItems)
		{
			_win.draw(item._text);
		}

		_win.display();

		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}
}
