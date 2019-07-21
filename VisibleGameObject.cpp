#include "pch.h"
#include "VisibleGameObject.h"
#include "Game.h"

VisibleGameObject::VisibleGameObject() :
	_isLoaded(false)
{
	std::cout << __func__ << std::endl;
}


VisibleGameObject::~VisibleGameObject()
{
	std::cout << __func__ << std::endl;
}

void VisibleGameObject::Load(std::string filename)
{
	if (_image.loadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;
		_sprite.setTexture(_image);
		_isLoaded = true;
	}
}

void VisibleGameObject::Draw(sf::RenderWindow & renderWindow)
{
	if (_isLoaded)
	{
		renderWindow.draw(_sprite);
	}
}


GameMessage VisibleGameObject::Update()
{
	return GameMessage::EmptySuccessMessage();
}

sf::FloatRect VisibleGameObject::GetBounds() const
{
	return _sprite.getGlobalBounds();
}

void VisibleGameObject::SetScale(float sizeX, float sizeY) 
{
	if (_isLoaded) 
	{
		_sprite.setScale(sizeX, sizeY);
	}
}

void VisibleGameObject::SetPosition(float x, float y)
{
	if (_isLoaded)
	{
		_sprite.setPosition(x, y);
	}
}

sf::Vector2f VisibleGameObject::GetPosition() const
{
	if (_isLoaded)
	{
		return _sprite.getPosition();
	}
	return sf::Vector2f();
}

bool VisibleGameObject::IsWinLeftBorderTouched() const
{
	return this->GetPosition().x <= 0;
}

bool VisibleGameObject::IsWinRightBorderTouched() const
{
	return (this->GetPosition().x >= Game::SCREEN_WIDTH - GetBounds().width);
}

/**
 * NB the y-coordinate is decreasing in the window object, i.e. y=0 corresponds to the top of the window,
 * while y=WIN_HEIGHT corresponds to the bottom 
 */
bool VisibleGameObject::IsWinTopBorderTouched() const
{
	return this->GetPosition().y <= 0;
}

bool VisibleGameObject::IsWinBottomBorderTouched() const
{
	return (this->GetPosition().y >= Game::SCREEN_HEIGHT - GetBounds().height);
}

sf::Sprite& VisibleGameObject::GetSprite()
{
	return _sprite;
}

bool VisibleGameObject::IsLoaded() const
{
	return _isLoaded;
}
