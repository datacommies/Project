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
--				bool Client::roomFull(Room);
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
Client::Client(Player player, int connection) : _player(player), _connectionStatus(connection){
	;
}

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
--	Send a message to the server.
----------------------------------------------------------------------------------------------------------------------*/
bool Client::sendMsg() {//Packet p) {
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
--	Receive mesage from the server.
----------------------------------------------------------------------------------------------------------------------*/
bool Client::receiveMsg() {
	//receive messages from the server of how the client should act/behave
	//message may contain instructions such as:
	//		- move to a corrdinate
	//		- interact with an object, i.e. attack
	//		- build structures
	return true;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: enterGameRoom
--
-- DATE: Feburary 28, 2013
--
-- DESIGNER: Steve Lo
--
-- PROGRAMMER: Steve Lo
--
-- INTERFACE: bool Client::enterGameRoom();
--
-- RETURNS: True on success, False otherwise

-- NOTES:
--	Enter a game room if it is not full already.
----------------------------------------------------------------------------------------------------------------------*/
bool Client::enterGameRoom() {
	//if(!roomFull()){	//if the room is not full
		//enter the room
		//change the player status		
	//}
	return true;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: roomFull
--
-- DATE: Feburary 28, 2013
--
-- DESIGNER: Steve Lo
--
-- PROGRAMMER: Steve Lo
--
-- INTERFACE: bool Client::roomFull()
--
-- RETURNS: True on success, False otherwise

-- NOTES:
--	checks if the game rooom is full.
----------------------------------------------------------------------------------------------------------------------*/
bool Client::roomFull() {
	//if(room.numOfPlayer < MAX_CAPACITY){	//if the room is not full
		//return true;
	//}
	return false;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: selectPositionInTeam
--
-- DATE: Feburary 28, 2013
--
-- DESIGNER: Steve Lo
--
-- PROGRAMMER: Steve Lo
--
-- INTERFACE: bool Client::selectPositionInTeam()
--
-- RETURNS: True on success, False otherwise

-- NOTES:
--	set the team position that the client clicks on
----------------------------------------------------------------------------------------------------------------------*/
bool Client::selectPositionInTeam() {
	//if the client clicks on a position in a team
	//checks if the position is already taken
	//if(positionFree()){
	//	change the client's team position to this one
	//	set this position as occupied
	//	return true;
	//}
	return false;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: positionFree
--
-- DATE: Feburary 28, 2013
--
-- DESIGNER: Steve Lo
--
-- PROGRAMMER: Steve Lo
--
-- INTERFACE: bool Client::positionFree()
--
-- RETURNS: True if the position is available, False otherwise

-- NOTES:
--	check if the selected position is free
----------------------------------------------------------------------------------------------------------------------*/
bool Client::positionFree(int position) {
	//if there's already someone on that position
	//	return false;
	return true;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: attack
--
-- DATE: Feburary 28, 2013
--
-- DESIGNER: Steve Lo
--
-- PROGRAMMER: Steve Lo
--
-- INTERFACE: int Client::attack()
--
-- RETURNS: True if the position is available, False otherwise

-- NOTES:
--	determines the amount of damage to an enemy unti
----------------------------------------------------------------------------------------------------------------------*/
int Client::attack() {
	//return theDamage;
	return 0;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: takeDamage
--
-- DATE: Feburary 28, 2013
--
-- DESIGNER: Steve Lo
--
-- PROGRAMMER: Steve Lo
--
-- INTERFACE: void Client::takeDamage(int amount)
--
-- RETURNS: True if the position is available, False otherwise

-- NOTES:
--	minus that amount of the damage
----------------------------------------------------------------------------------------------------------------------*/
void Client::takeDamage(int amount) {
	//_player._hp -= amount
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: run
--
-- DATE: Feburary 28, 2013
--
-- DESIGNER: Steve Lo
--
-- PROGRAMMER: Steve Lo
--
-- INTERFACE: void Client::run()
--
-- RETURNS: True if the position is available, False otherwise

-- NOTES:
--	minus that amount of the damage
----------------------------------------------------------------------------------------------------------------------*/
void Client::run() {
	while(1) {
		//send message to the server every 1/30 second to update the player's
		//status
	}
}

int main(){
	return 0;
}
