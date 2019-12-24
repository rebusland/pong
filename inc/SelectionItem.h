#pragma once
class Screen;
class OptionsScreen;
class MenuScreen;

class SelectionItem 
{
public:
	SelectionItem(sf::Text&&, std::function<void()>&& callback);
	
	void Select();
	void UnMark();
	void Confirm();

	// declare container OptionsScreen class as friend class
	friend class Screen;
	friend class OptionsScreen;
	friend class MenuScreen;

private:
	sf::Text _text;
	std::function<void()> _onConfirmationCallback;
};
