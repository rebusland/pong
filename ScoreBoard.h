#pragma once
#include "Referee.h"

/**
 * Handles scoreboard bar
 */
class ScoreBoard 
{
public:
	ScoreBoard();

	/**
	 * draw the scoreboard on the given window 
	 */
	void Draw(sf::RenderWindow& window);

	void UpdateScores(const result_t& updatedResult);

private:
	// inner score box handler
	struct ScoreBox 
	{
		ScoreBox(const ScoreBoard& containingBoard, const sf::String& playerName, const sf::Vector2f& position);
		void UpdateScore(int updatedScore);
		const sf::RectangleShape& GetBox() { return _box; };
		const sf::Text& GetScoreText() { return _scoreText; };

		// reference to the ScoreBoard containing class
		const ScoreBoard& _scoreBoard;

		// the actual box
		sf::RectangleShape _box;

		// the text for the score
		sf::Text _scoreText;

		// player name
		const sf::String& _playerName;
	};

	// score visualation handler for each player
	sf::RectangleShape _scoreBar;

	// score boxes for players
	ScoreBoard::ScoreBox _playerScoreBox;
	ScoreBoard::ScoreBox _computerScoreBox;

	// the last updated score
	result_t _currentScore;

	const sf::String FIRST_PLAYER_NAME = "Computer";
	const sf::String SECOND_PLAYER_NAME = "Player"; // TODO let the user choose its gaming name
};
