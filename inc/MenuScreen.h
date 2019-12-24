#pragma once

#pragma once
#include "inc/SelectionItem.h"
#include "inc/Screen.h"

class MenuScreen : public Screen
{
public:
	MenuScreen(sf::RenderWindow& window, sf::Font& font);
	
	virtual void Open() override;
};

