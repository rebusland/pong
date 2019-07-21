#pragma once
class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow & window);
	virtual void Update();

	virtual sf::FloatRect GetBounds() const;

	virtual void SetPosition(float x, float y);
	// set the x and y dimensions of the object
	virtual void SetScale(float sizeX, float sizeY);
	virtual sf::Vector2f GetPosition() const;
	virtual bool IsWinLeftBorderTouched() const;
	virtual bool IsWinRightBorderTouched() const;
	virtual bool IsWinTopBorderTouched() const;
	virtual bool IsWinBottomBorderTouched() const;
	virtual bool IsLoaded() const;

protected:
	sf::Sprite& GetSprite();

private:
	sf::Sprite  _sprite;
	sf::Texture _image;
	std::string _filename;
	bool _isLoaded;
};
