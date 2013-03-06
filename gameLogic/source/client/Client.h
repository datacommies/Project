/*--------------------------------------------------------------------------------------
--	SOURCE FILE:	Client.h -	Header file for the Client class
--
--	PROGRAM:		client
--
--	FUNCTIONS:
--				void* runningThread(void * arg)
--
--	DATE:		Feburary 28, 2013
--
--	DESIGNER:	Steve Lo
--
--	PROGRAMMER:	Steve Lo
--
--	NOTES:
--------------------------------------------------------------------------------------*/
#ifndef CLIENT_H
#define CLIENT_H

#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <unistd.h>

#include "Player.h"
//#include "../gameClasses/Team.h"

class Client {
private:
	Player _player;
	int _connectionStatus;
	
public:
	Client(Player, int);
	~Client() {}
	
	//Client's helper functions
	bool sendMsg();//Packet);
	bool receiveMsg();
	bool enterGameRoom();
	bool roomFull();
	bool selectPositionInTeam();
	bool positionFree(int position);
	int attack();
	void takeDamage(int);
	void run();
};
#endif
