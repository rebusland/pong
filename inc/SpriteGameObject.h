#pragma once
#include "VisibleGameObject.h"

class SpriteGameObject : 
	public VisibleGameObject,
	public sf::Sprite
{
	public:
		/**
		 * Constructor loading the specified texture given the file name.
		 * An assert statement makes sure the default image is loaded.
		 */
		SpriteGameObject(const std::string& fileName);

		virtual ~SpriteGameObject() { std::cout << __func__ << std::endl; }

		virtual void Draw(sf::RenderWindow & renderWindow) override;

		virtual sf::FloatRect GetBounds() const override { return Sprite::getGlobalBounds(); }
		virtual sf::Vector2f GetPosition() const override { return Sprite::getPosition(); }
		virtual sf::Vector2f GetOrigin() const override { return Sprite::getOrigin(); }

		virtual void SetScale(float scaleFactorX, float scaleFactorY) override { Sprite::setScale(scaleFactorX, scaleFactorY); }
		virtual void SetPosition(float x, float y) override { Sprite::setPosition(x, y); }
		virtual void SetOrigin(float x, float y) override { Sprite::setOrigin(x, y); }

		/**
		 * Allows to set explicitly the sizes in pixels for the sprite.
		 * The SFML API for Sprite lacks of a setSize method, it only exposes a way to rescale images.
		 * The current method retrieves the sizes of the original image, hence calculating and applying 
		 * the scaling factor required to have a sprite rectangle with the input x and y sizes.
		 */
		virtual void SetSize(float sizeX, float sizeY);

		/**
		 * If failure when loading the texture an exception is thrown.
		 * The default texture must be specified in the constructor.
		 * This method can be invoked when the default image should be changed.
		 */
		virtual void LoadTexture(std::string filename);

		virtual bool IsTextureLoaded() const { return _isLoaded; }

	protected:
		sf::Texture _image;
		bool _isLoaded = false;
		std::string _filename;
};
