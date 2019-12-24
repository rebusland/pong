#pragma once
#include "inc/Screen.h"
#include "inc/SelectionItem.h"
#include "inc/Game.h"

class OptionsScreen : public Screen
{
public:
	OptionsScreen(sf::RenderWindow& window, sf::Font& font);
	
	void Open();
};
