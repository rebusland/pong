#pragma once

#include "inc/SelectionItem.h"
#include "inc/Game.h"

class Screen
{
public:
	Screen(sf::RenderWindow& window);
	virtual ~Screen() {	std::cout << "Screen Destructor called\n"; }

	virtual void Open() = 0;
	virtual void HandleEvent(const sf::Event&);

	static void SetGameState(const Game::GameState&);
	/**
	 * This method centers Text objects horizontally, while properly aligning those vertically.
	 */
	static void alignMultiTextVertically(std::vector<SelectionItem>& menuSelections, const sf::Vector2f& containerPosition, const sf::Vector2f& containerSizes);

protected:
	virtual void SelectNextItem();
	virtual void SelectPreviousItem();
	virtual void ConfirmSelectedItem();

	// reference to the window object to draw the screen on
	sf::RenderWindow& _win;

	// the list of options to choose from
	std::vector<SelectionItem> _selectionItems;

	// SelectionItem currently selected from _selectionItems array
	unsigned short int _currentlySelectedItem = 0;
};
