#include "pch.h"
#include "Game.h"
#include "ScoreBoard.h"

/** SCOREBOARD::SCOREBOX **/
ScoreBoard::ScoreBox::ScoreBox(const ScoreBoard& scoreBoard, const sf::String& name, const sf::Vector2f& position) : 
	_scoreBoard {scoreBoard},
	_playerName {name}
{
	// setup score box sizes and color
	this->_box.setSize(sf::Vector2f(Game::SCORE_BOX_WIDTH, Game::SCORE_BOX_HEIGHT));
	this->_box.setFillColor(sf::Color::White);

	_box.setPosition(position);

	// setup score text
	_scoreText.setFont(Game::Fonts::arialFont);
	_scoreText.setFillColor(sf::Color::Black);
	_scoreText.setCharacterSize(25);
	_scoreText.setStyle(sf::Text::Bold);
	_scoreText.setPosition(
		sf::Vector2f(
			Game::FIELD_WIDTH + Game::SCORE_BOARD_WIDTH / 2 - 7,
			_box.getPosition().y + Game::SCORE_BOX_HEIGHT / 2 - 15
		)
	);

	// set initial score to zero
	_scoreText.setString("0");
}

/** SCOREBOARD **/
ScoreBoard::ScoreBoard() :
	_scoreBar(sf::Vector2f(Game::SCORE_BOARD_WIDTH, Game::SCORE_BOARD_HEIGHT)),
	_playerScoreBox(
		*this,
		FIRST_PLAYER_NAME,
		sf::Vector2f(Game::FIELD_WIDTH, Game::FIELD_HEIGHT / 4 - Game::SCORE_BOX_HEIGHT / 2)
	),
	_computerScoreBox(
		*this,
		SECOND_PLAYER_NAME,
		sf::Vector2f(Game::FIELD_WIDTH, Game::FIELD_HEIGHT * 3 / 4 - Game::SCORE_BOX_HEIGHT / 2)
	)
{
	// setup the scoreboard bar rectangle
	_scoreBar.setFillColor(sf::Color(105, 105, 105)); // grey
	_scoreBar.setPosition(sf::Vector2f(Game::FIELD_WIDTH, 0));
}

void ScoreBoard::Clear() 
{
	_playerScoreBox._scoreText.setString("0");
	_computerScoreBox._scoreText.setString("0");
}

void ScoreBoard::Draw(sf::RenderWindow& window) 
{
	// window will draw every object of the scoreboard
	window.draw(_scoreBar);

	window.draw(_playerScoreBox.GetBox());
	window.draw(_playerScoreBox.GetScoreText());

	window.draw(_computerScoreBox.GetBox());
	window.draw(_computerScoreBox.GetScoreText());
}

void ScoreBoard::UpdateScores(const result_t& updatedResult)
{
	std::cout << __func__ <<  std::endl;
	_playerScoreBox.UpdateScore(updatedResult.playerScore);
	_computerScoreBox.UpdateScore(updatedResult.computerScore);
}
