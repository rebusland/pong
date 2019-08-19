#include "pch.h"
#include "inc/SpriteWrapper.h"

SpriteWrapper::SpriteWrapper(const std::string& fileName) : _filename {fileName}
{
	// Unable to load default image for sprite texture from "_filename"
	assert(_image.loadFromFile(fileName));

	// check that both texture sizes are at least greater than one pixel
	assert(_image.getSize().x > 1 && _image.getSize().y > 1);

	setTexture(_image);

	_isLoaded = true;
}

void SpriteWrapper::SetSize(float sizeX, float sizeY)
{
	setScale(
		sizeX / getLocalBounds().width,
		sizeY / getLocalBounds().height
	);
}

void SpriteWrapper::LoadTexture(std::string fileName) 
{
	if (not _image.loadFromFile(fileName))
	{
		_isLoaded = false;
		// TODO implement a custom exception miming std::ios_base::failure exception?
		const std::string errorMessage = "Unable to load image for texture. File " + fileName + " not found";
		std::cout << errorMessage << std::endl;
		throw std::runtime_error(errorMessage);
	}
	else
	{
		setTexture(_image);
		_isLoaded = true;
	}
}
