#include "pch.h"
#include "inc/Referee.h"
#include "inc/Utilities.h"

const result_t& Referee::GetCurrentResult() const
{
	LOG(__func__ << ": current result, computer vs player: " << _result.computerScore << " - " << _result.playerScore)
	return _result;
}

void Referee::InterpretBallMessage(const GameMessage& msg) 
{
	if (msg.GetMessageType() == GameMessage::message_type_t::PLAYER_MISS)
	{
		IncrementComputerScore();
	}
	else if (msg.GetMessageType() == GameMessage::message_type_t::COMPUTER_MISS)
	{
		IncrementPlayerScore();
	}
	else 
	{
		LOG("Warning: unhandled case, referee received ball message not pertaining to a ball miss.")
	}
}

void Referee::IncrementComputerScore()
{
	LOG(__func__ <<  ": increment computer score")
	++_result.computerScore;
}

void Referee::IncrementPlayerScore()
{
	LOG(__func__ << ": increment player score")
	++_result.playerScore;
}
