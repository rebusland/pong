#pragma once

#define SETTINGS_SCREEN_IMAGE_PATH "images/SettingsScreenImg.png"

/**
 * TODO This screen should allow to change any type of settings: game difficulty level, 
 * audio on/off, player vs computer or computer vs computer and so forth.
 */
class SettingsScreen 
{
public:
	enum SettingsScreenResult { BackToMenu, Exit };

	SettingsScreenResult Show(sf::RenderWindow& window);
};
