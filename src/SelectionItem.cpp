#include "pch.h"
#include "inc/SelectionItem.h"

SelectionItem::SelectionItem(sf::Text&& text, std::function<void()>&& callback) : 
	_text(std::move(text)),
	_onConfirmationCallback(std::move(callback))
{
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::White);
}

void SelectionItem::Select() 
{
	_text.setFillColor(sf::Color::Red);
	_text.setStyle(sf::Text::Bold);
}

void SelectionItem::UnMark() 
{
	_text.setFillColor(sf::Color::White);
	_text.setStyle(sf::Text::Regular);
}

void SelectionItem::Confirm() 
{
	_onConfirmationCallback();
}

