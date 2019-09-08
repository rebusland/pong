#include "pch.h"
#include "inc/SplashScreen.h"

#define INTRO_IMAGE "images/PongIntroImg.png"

GameMessage SplashScreen::Show(sf::RenderWindow& renderWindow)
{
	sf::Texture image;
	if (image.loadFromFile(INTRO_IMAGE) != true)
	{
		return GameMessage(
			GameMessage::ERROR,
			"Impossible to laod Intro image: " + std::string(INTRO_IMAGE),
			true
		);
	}

	sf::Sprite sprite(image);

	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;

	while (true) {
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed
				|| event.type == sf::Event::EventType::MouseButtonPressed
				|| event.type == sf::Event::EventType::Closed)
			{
				return GameMessage::EmptySuccessMessage();
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}