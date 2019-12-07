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
	 * Reset scores
	 */
	void Clear();

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
		void UpdateScore(int updatedScore) 
		{
			_scoreText.setString(std::to_string(updatedScore));
		}
		const sf::RectangleShape& GetBox() const { return _box; };
		const sf::Text& GetScoreText() const { return _scoreText; };
		const sf::Text& GetPlayerNameText() const { return _playerNameText;  };

		// reference to the ScoreBoard containing class
		const ScoreBoard& _scoreBoard;

		// the actual box
		sf::RectangleShape _box;

		// the text for the score
		sf::Text _scoreText;

		// text for player name
		sf::Text _playerNameText;
	};

	// score visualation handler for each player
	sf::RectangleShape _scoreBar;

	// score boxes for players
	ScoreBoard::ScoreBox _playerScoreBox;
	ScoreBoard::ScoreBox _computerScoreBox;

	// the last updated score
	result_t _currentScore;
};
