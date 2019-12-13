#pragma once

#include "pch.h"
#include "inc/SettingsScreen.h"

SettingsScreen::SettingsScreenResult SettingsScreen::Show(sf::RenderWindow& window)
{
	//Load menu image from file
	sf::Texture image;
	image.loadFromFile(SETTINGS_SCREEN_IMAGE_PATH);
	sf::Sprite sprite(image);

	window.draw(sprite);
	window.display();

	sf::Event settingsScreenEvent;
	while (true)
	{
		while (window.pollEvent(settingsScreenEvent))
		{
			if (settingsScreenEvent.type == sf::Event::MouseButtonPressed)
			{
				return BackToMenu;
			}
			if (settingsScreenEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}
