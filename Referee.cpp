#include "pch.h"
#include "Referee.h"

Referee::~Referee() 
{
	std::cout << "Referee destructor!" << std::endl;
}

void Referee::ResetScore() 
{
	_result.Clear();
}

const result_t& Referee::GetCurrentResult() const
{
	std::cout << __func__ << ": current result, computer vs player: " << _result.computerScore << " - " << _result.playerScore << std::endl;
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
		std::cout << "Warning: unhandled case, referee received ball message not pertaining to a ball miss." << std::endl;
	}
}

void Referee::IncrementComputerScore()
{
	std::cout << __func__ <<  ": increment computer score" << std::endl;
	++_result.computerScore;
}

void Referee::IncrementPlayerScore()
{
	std::cout << __func__ << ": increment player score" << std::endl;
	++_result.playerScore;
}
