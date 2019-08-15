#include "pch.h"
#include "inc/SpriteGameObject.h"
#include "inc/Game.h"

void SpriteGameObject::Load(std::string fileName) 
{
	if (_image.loadFromFile(fileName) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = fileName;
		setTexture(_image);
		_isLoaded = true;
	}
}

bool SpriteGameObject::IsTextureLoaded() const
{
	return _isLoaded;
}

void SpriteGameObject::Draw(sf::RenderWindow & renderWindow)
{
	if (_isLoaded)
	{
		// cast the current object to <const Sprite&> in order for it to be passed to the window draw function 
		const Sprite &spriteCast = static_cast<const Sprite &>(*this);
		renderWindow.draw(spriteCast);
	}
}

void SpriteGameObject::SetScale(float sizeX, float sizeY)
{
	if (_isLoaded)
	{
		Sprite::setScale(sizeX, sizeY);
	}
}

void SpriteGameObject::SetPosition(float x, float y)
{
	if (_isLoaded)
	{
		Sprite::setPosition(x, y);
	}
}

sf::Vector2f SpriteGameObject::GetPosition() const
{
	if (_isLoaded)
	{
		return Sprite::getPosition();
	}
	return sf::Vector2f();
}

sf::FloatRect SpriteGameObject::GetBounds() const
{
	return Sprite::getGlobalBounds();
}

bool SpriteGameObject::IsWinLeftBorderTouched() const
{
	return GetPosition().x <= 0;
}

bool SpriteGameObject::IsWinRightBorderTouched() const
{
	return (GetPosition().x >= Game::FIELD_WIDTH - GetBounds().width);
}

/**
 * NB the y-coordinate is decreasing in the window object, i.e. y=0 corresponds to the top of the window,
 * while y=WIN_HEIGHT corresponds to the bottom
 */
bool SpriteGameObject::IsWinTopBorderTouched() const
{
	return GetPosition().y <= 0;
}

bool SpriteGameObject::IsWinBottomBorderTouched() const
{
	return (GetPosition().y >= Game::FIELD_HEIGHT - GetBounds().height);
}
