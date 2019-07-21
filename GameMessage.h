#pragma once
/**
 * Represents a message concerning the state of the game, for example it can be a info message which,
 * from a game object (e.g. the ball) can propagate to the game handler class indicating if the game flow should change.
 * This general interface can be extended to more specific messages. 
 */
class GameMessage 
{
public:
	// constructors
	GameMessage() = default;
	GameMessage(std::string msg, bool isError);

	static GameMessage EmptySuccessMessage();
	std::string GetMessage(); 
	bool IsError();

private:
	std::string _message;
	bool _isError;
};
