#include "pch.h"
#include "inc/SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow& renderWindow)
{
	sf::Texture image;
	if (image.loadFromFile("images/PongIntroImg.png") != true)
	{
		return;
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
				return;
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(60));
	}
}