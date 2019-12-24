#include "pch.h"
#include "inc/OptionsScreen.h"

OptionsScreen::OptionsScreen(sf::RenderWindow& win, sf::Font& font) : Screen(win)
{
	_selectionItems.emplace_back(
		sf::Text("OptionItem1", font),
		[]() {std::cout << "OptionItem1 selected" << std::endl; }
	);

	_selectionItems.emplace_back(
		sf::Text("OptionItem2", font),
		[]() {std::cout << "OptionItem2 selected" << std::endl; }
	);

	_selectionItems.emplace_back(
		sf::Text("Back to Menu", font),
		[]() { SetGameState(Game::GameState::ShowingMenu); }
	);

	// default: the first selection item in the list is selected
	_selectionItems[0].Select();

	alignMultiTextVertically(_selectionItems, sf::Vector2f(0, 0), sf::Vector2f(_win.getSize()));
}

void OptionsScreen::Open()
{
	while (_win.isOpen() && Game::_gameState == Game::GameState::ChangingSettings) {
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
