#include "pch.h"
#include "inc/VisibleGameObject.h"
#include "inc/Game.h"

bool VisibleGameObject::IsWinLeftBorderTouched() const
{
	return GetPosition().x <= 0;
}

bool VisibleGameObject::IsWinRightBorderTouched() const
{
	return (GetPosition().x >= Game::FIELD_WIDTH - GetBounds().width);
}

bool VisibleGameObject::IsWinTopBorderTouched() const
{
	return GetPosition().y <= 0;
}

bool VisibleGameObject::IsWinBottomBorderTouched() const
{
	return (GetPosition().y >= Game::FIELD_HEIGHT - GetBounds().height);
}
