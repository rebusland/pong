#pragma once
/**
 * Represents a message concerning the state of the game, for example it can be a info message which,
 * from a game object (e.g. the ball) can propagate to the game handler class indicating if the game flow should change.
 * This general interface can be extended to more specific messages. 
 */
class GameMessage
{
public:

	typedef enum
	{
		SUCCESS,
		PLAYER_MISS,
		COMPUTER_MISS,
		ERROR
	} message_type_t;

	// constructors
	GameMessage() = default;
	GameMessage(message_type_t msgType, std::string msgString, bool isError);

	static GameMessage EmptySuccessMessage();
	
	const message_type_t& GetMessageType() const;
	const std::string& GetMessageString() const; 
	bool IsError() const;
	bool IsBallMiss() const;

private:
	message_type_t _messageType;
	std::string _messageString;
	bool _isError;
};
