#include "pch.h"
#include "GameMessage.h"

GameMessage::GameMessage(std::string msg, bool isError) : _message{ msg }, _isError{ isError } {}

std::string GameMessage::GetMessage() 
{
	return _message;
}

bool GameMessage::IsError()
{
	return _isError;
}

GameMessage GameMessage::EmptySuccessMessage() 
{
	return GameMessage("", false);
}
