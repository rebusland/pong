#pragma once
#include "VisibleGameObject.h"

class SpriteGameObject : 
	public VisibleGameObject,
	public sf::Sprite
{
	public:
		virtual void Load(std::string filename);
		virtual void Draw(sf::RenderWindow & renderWindow) override;
		virtual sf::FloatRect GetBounds() const override;

		virtual bool IsWinLeftBorderTouched() const override;
		virtual bool IsWinRightBorderTouched() const override;
		virtual bool IsWinTopBorderTouched() const override;
		virtual bool IsWinBottomBorderTouched() const override;

		virtual void SetScale(float sizeX, float sizeY) override;
		virtual void SetPosition(float x, float y) override;
		virtual sf::Vector2f GetPosition() const override;

	protected:
		virtual bool IsTextureLoaded() const;
		sf::Texture _image;
		// sf::Sprite _sprite;
		std::string _filename;
		bool _isLoaded = false;
};
