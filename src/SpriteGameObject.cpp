#include "pch.h"
#include "inc/SpriteGameObject.h"

SpriteGameObject::SpriteGameObject(const std::string& fileName) : _filename {fileName}
{
	// Unable to load default image for sprite texture from "_filename"
	assert(_image.loadFromFile(fileName));
	setTexture(_image);
	_isLoaded = true;
}

void SpriteGameObject::LoadTexture(std::string fileName) 
{
	if (not _image.loadFromFile(fileName))
	{
		_isLoaded = false;
		// TODO implement a custom exception miming std::ios_base::failure exception?
		const std::string errorMessage = "Unable to load image for texture. File " + fileName + " not found";
		throw std::runtime_error(errorMessage);
	}
	else
	{
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
	renderWindow.draw(*this); // *this as a Sprite will have a proper implementation for Drawable interface
}

void SpriteGameObject::SetScale(float sizeX, float sizeY)
{
	Sprite::setScale(sizeX, sizeY);
}

void SpriteGameObject::SetPosition(float x, float y)
{
	Sprite::setPosition(x, y);
}

sf::Vector2f SpriteGameObject::GetPosition() const
{
	return Sprite::getPosition();
}

sf::FloatRect SpriteGameObject::GetBounds() const
{
	return Sprite::getGlobalBounds();
}

/*

bool SpriteGameObject::IsWinLeftBorderTouched() const
{
	return GetPosition().x <= 0;
}

bool SpriteGameObject::IsWinRightBorderTouched() const
{
	return (GetPosition().x >= Game::FIELD_WIDTH - GetBounds().width);
}

bool SpriteGameObject::IsWinTopBorderTouched() const
{
	return GetPosition().y <= 0;
}

bool SpriteGameObject::IsWinBottomBorderTouched() const
{
	return (GetPosition().y >= Game::FIELD_HEIGHT - GetBounds().height);
}
*/
