#include "pch.h"
#include "inc/Screen.h"

Screen::Screen(sf::RenderWindow& win) : _win{ win }
{}

void Screen::SetGameState(const Game::GameState& state)
{
	Game::_gameState = state;
}

void Screen::HandleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::Down)
	{
		SelectNextItem();
	}
	else if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::Up)
	{
		SelectPreviousItem();
	}
	else if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::Enter)
	{
		ConfirmSelectedItem();
	}
}

void Screen::SelectNextItem()
{
	if (_currentlySelectedItem < _selectionItems.size() - 1)
	{
		_selectionItems[_currentlySelectedItem].UnMark();
		_selectionItems[++_currentlySelectedItem].Select();
	}
}

void Screen::SelectPreviousItem()
{
	if (_currentlySelectedItem > 0)
	{
		_selectionItems[_currentlySelectedItem].UnMark();
		_selectionItems[--_currentlySelectedItem].Select();
	}
}

void Screen::ConfirmSelectedItem()
{
	_selectionItems[_currentlySelectedItem].Confirm();
}

void Screen::alignMultiTextVertically(std::vector<SelectionItem>& menuSelections, const sf::Vector2f& containerPosition, const sf::Vector2f& containerSizes)
{
	// TODO add constraint check:
	// sum of the heights of all Text objects must be lower than the available height in the container.
	const int nDivisions = menuSelections.size() + 1;
	for (int i = 0; i < nDivisions - 1; ++i)
	{
		/**
		 * From SFML forum (not written in documentation):
		 * "The text is not aligned on top, it is aligned on its baseline.
		 * So unless your text contains the highest character of the font(most likely accentuated capitals),
		 * it will always be slightly below the top.
		 * The offset should be text.getLocalBounds().top."
		 */
		auto& text = menuSelections[i]._text; // NB we get the reference!
		text.setPosition(
			containerPosition.x + (containerSizes.x - text.getLocalBounds().width) / 2,
			containerPosition.y + (i + 1) * (containerSizes.y / nDivisions) - text.getLocalBounds().height / 2 - text.getLocalBounds().top
		);
	}
}
