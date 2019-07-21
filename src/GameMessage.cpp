#include "pch.h"
#include "GameMessage.h"

GameMessage::GameMessage(GameMessage::message_type_t msgType, std::string msgString, bool isError) : 
	_messageType{ msgType }, 
	_messageString{ msgString }, 
	_isError{ isError } {}

const GameMessage::message_type_t& GameMessage::GetMessageType() const
{
	return _messageType;
}

const std::string& GameMessage::GetMessageString() const
{
	return _messageString;
}

bool GameMessage::IsError() const
{
	return _isError;
}

bool GameMessage::IsBallMiss() const
{
	return (_messageType == message_type_t::PLAYER_MISS || _messageType == message_type_t::COMPUTER_MISS);
}

GameMessage GameMessage::EmptySuccessMessage() 
{
	return GameMessage(GameMessage::message_type_t::SUCCESS, "", false);
}
