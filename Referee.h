#pragma once
#include "pch.h"
#include "GameMessage.h"

/**
 * A referee for the game, counting the ball misses for each player, updating the sets/matches score.
 */

typedef struct {
	int playerScore;
	int computerScore;
	
	// the score needed by a player to win the game
	static constexpr int MAX_SCORE = 10;
} result_t;

class Referee 
{
public:
	~Referee();
	const result_t& GetCurrentResult() const;
	void InterpretBallMessage(const GameMessage& ballMessage);

private:
	void IncrementPlayerScore();
	void IncrementComputerScore();

	result_t _result;
};
