/*--------------------------------------------------------------------------------------
--	SOURCE FILE:	Client.cpp -	A client class for any behaviors that a client
--									program has.
--
--	PROGRAM:		client
--
--	FUNCTIONS:
--				Client::Client(key_t &key, bool thread) : key_(key), connection_(key, false)
--				void Client::sendMsg(Packet);
--				void Client::receiveMsg();
--				void Client::enterGameRoom();
--				bool Client::ifRoomFull(Room);
--				void Client::selectPositionInTeam();
--				bool Client::ifPositionFree(Team);
--				void Client::attack();
--				void Client::takeDamage(int);
--				void Client::run();
--
--	DATE:		Feburary 28, 2013
--
--	DESIGNER:	Steve Lo
--
--	PROGRAMMER:	Steve Lo
--
--	NOTES:
--	The client class for how the program behave when the client is executed and how
--	requests are sent.
--------------------------------------------------------------------------------------*/
#include "Client.h"
using namespace std;

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Client constructor
--
-- DATE: January 30, 2013
--
-- DESIGNER: Steve Lo
--
-- PROGRAMMER: Steve Lo
--
-- INTERFACE: Client::Client(key_t &key, bool thread) : key_(key), connection_(key, false)
--
-- NOTES:
--	The constructor for the Client
----------------------------------------------------------------------------------------------------------------------*/
Client::Client(Player player, int connection) : _player(player), _connectionStatus(connection);

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: sendMsg
--
-- DATE: Feburary 28, 2013
--
-- DESIGNER: Steve Lo
--
-- PROGRAMMER: Steve Lo
--
-- INTERFACE: bool Client::sendMsg(Packet);
--
-- RETURNS: True on success, False otherwise

-- NOTES:
--	Send a file request to the server.
----------------------------------------------------------------------------------------------------------------------*/
bool Client::sendMsg(Packet p) {
	//send message to the server when an event occurs
	//	i.e. mouse click, send out mouse pointer coordinates and the object that's clicked on
	//send out one message every 1/30 second
	//return false when errors occur
	return true;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: receiveMsg
--
-- DATE: Feburary 28, 2013
--
-- DESIGNER: Steve Lo
--
-- PROGRAMMER: Steve Lo
--
-- INTERFACE: bool Client::receiveMsg();
--
-- RETURNS: True on success, False otherwise

-- NOTES:
--	Send a file request to the server.
----------------------------------------------------------------------------------------------------------------------*/
bool Client::receiveMsg() {
	return true;
}
	void Client::enterGameRoom();
	bool Client::ifRoomFull(Room);
	void Client::selectPositionInTeam();
	bool Client::ifPositionFree(Team);
	void Client::attack();
	void Client::takeDamage(int);
	void Client::run();
