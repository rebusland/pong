#pragma once
#include "VisibleGameObject.h"

class SpriteGameObject : 
	public VisibleGameObject,
	public sf::Sprite
{
	public:
		virtual ~SpriteGameObject()
		{
			std::cout << __func__ << std::endl;
		}

		/**
		 * Constructor loading the specified texture given the file name.
		 * An assert statement makes sure the default image is loaded.
		 */
		SpriteGameObject(const std::string& fileName);

		virtual void Draw(sf::RenderWindow & renderWindow) override;
		virtual sf::FloatRect GetBounds() const override;

		/*
		virtual bool IsWinLeftBorderTouched() const override;
		virtual bool IsWinRightBorderTouched() const override;
		virtual bool IsWinTopBorderTouched() const override;
		virtual bool IsWinBottomBorderTouched() const override;
		*/

		virtual void SetScale(float sizeX, float sizeY) override;
		virtual void SetPosition(float x, float y) override;
		virtual sf::Vector2f GetPosition() const override;

		/**
		 * If failure when loading the texture an exception is thrown
		 * The default texture must be specified in the constructor.
		 * This method can be invoked when the default image should be changed.
		 */
		virtual void LoadTexture(std::string filename);
		virtual bool IsTextureLoaded() const;

	protected:
		sf::Texture _image;
		bool _isLoaded = false;
		std::string _filename;
};
