#pragma once
#include "GameMessage.h"

using result_t = struct {
	int playerScore;
	int computerScore;

	void Clear() 
	{
		playerScore = 0;
		computerScore = 0;
	}
	
	// the score needed by a player to win the game
	static constexpr int MAX_SCORE = 10;
};

/**
 * A referee for the game, counting the ball misses for each player, updating the sets/matches score.
 */
class Referee 
{
public:
	~Referee() { std::cout << __func__ << std::endl; }
	void ResetScore() { _result.Clear(); }

	const result_t& GetCurrentResult() const;
	void InterpretBallMessage(const GameMessage& ballMessage);

private:
	void IncrementPlayerScore();
	void IncrementComputerScore();

	result_t _result;
};
