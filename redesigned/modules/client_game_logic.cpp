/*------------------------------------------------------------------------------
-- FILE:        client_game_logic.cpp
--
-- DATE:        2013/03/11
--
-- MAINTAINERS: Callum Styan, David Czech, Dennis Ho, Albert Liao, 
--              Steve Lo, Jesse Wright, Jacob Miner
--
-- FUNCTIONS:   ClientGameLogic constructor
--              start
--              join
--              menu
--              win
--              lose
--              createTower
--              createCreep
--              movePlayer
--              attack
--              exit
--              getCurrentState
--
-- DESCRIPTION: File contains implementation for the Unit class. Unit will be
--              a base class that Tower and MobileUnit inherit from. 
------------------------------------------------------------------------------*/
#include "client_game_logic.h"


ClientGameLogic::ClientGameLogic(ClientNetwork& clientNetwork)
   : clientNetwork_(clientNetwork), gameState_(MAIN_MENU)
{
   waitingForStart = false;
   clientNetwork_.gl = this;
   //unit_mutex = PTHREAD_MUTEX_INITIALIZER; // only allowed for declaration-initialization.
   pthread_mutex_init(&unit_mutex, NULL);
}

/*------------------------------------------------------------------------------
-- FUNCTION:    start
--
-- DATE:        2013/03/11
--
-- DESIGNER:    David Czech
-- PROGRAMMER:  David Czech
--
-- INTERFACE:   void ClientGameLogic::start ()
--
-- RETURNS:     void
--
-- DESCRIPTION: This function sets the gameState_ variable to IN_GAME. 
------------------------------------------------------------------------------*/
void ClientGameLogic::start () {
   gameState_ = IN_GAME;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    join
--
-- DATE:        2013/03/11
--
-- DESIGNER:    David Czech
-- PROGRAMMER:  David Czech
--
-- INTERFACE:   void ClientGameLogic::join ()
--
-- RETURNS:     void
--
-- DESCRIPTION: This function sets the gameState_ variable to LOBBY. 
------------------------------------------------------------------------------*/
void ClientGameLogic::join () {
   gameState_ = LOBBY;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    menu
--
-- DATE:        2013/03/11
--
-- DESIGNER:    David Czech
-- PROGRAMMER:  David Czech
--
-- INTERFACE:   void ClientGameLogic::menu ()
--
-- RETURNS:     void
--
-- DESCRIPTION: This function sets the gameState_ variable to MAIN_MENU. 
------------------------------------------------------------------------------*/
void ClientGameLogic::menu () {
   gameState_ = MAIN_MENU;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    win
--
-- DATE:        2013/03/11
--
-- DESIGNER:    Behnam Bastami
-- PROGRAMMER:  Behnam Bastami
--
-- INTERFACE:   void ClientGameLogic::win ()
--
-- RETURNS:     void
--
-- DESCRIPTION: This function sets the gameState_ variable to WON_GAME. 
------------------------------------------------------------------------------*/
void ClientGameLogic::win () {
   gameState_ = WON_GAME;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    lose
--
-- DATE:        2013/03/11
--
-- DESIGNER:    Behnam Bastami
-- PROGRAMMER:  Behnam Bastami
--
-- INTERFACE:   void ClientGameLogic::lose ()
--
-- RETURNS:     void
--
-- DESCRIPTION: This function sets the gameState_ variable to LOST_GAME. 
------------------------------------------------------------------------------*/
void ClientGameLogic::lose () {
   gameState_ = LOST_GAME;
   audio_.playSoundEffect("sounds/lose.wav");
}

/*------------------------------------------------------------------------------
-- FUNCTION:    createTower
--
-- DATE:        2013/03/11
--
-- DESIGNER:    Behnam Bastami
-- PROGRAMMER:  Behnam Bastami
--
-- INTERFACE:   bool ClientGameLogic::createTower(UnitType type, Point location)
--
-- RETURNS:     Boolean; True if the request was sent, False otherwise
--
-- DESCRIPTION: This function creates a tower of the specified type at the 
--              specified location.
------------------------------------------------------------------------------*/
bool ClientGameLogic::createTower(UnitType type, Point location)
{
   // TODO: validation
   //validate currency - handled in server_game_logic.cpp

   //pass team into create unit, switch based on unit type?

   //validate location
   //if the location you are attempting to build a tower at
   //is not currently occupied and is not impassible terrain

   clientNetwork_.createUnit(this->playerId, type, location, 2); //hardcoded path = 2 (last parameter)
   
   return true;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    createCreep
--
-- DATE:        2013/03/11
--
-- DESIGNER:    Behnam Bastami
-- PROGRAMMER:  Behnam Bastami, Albert Liao, Jesse Wright
--
-- INTERFACE:   bool ClientGameLogic::createCreep(UnitType type, int laneID)
--
-- RETURNS:     Boolean; True if the request was sent, False otherwise
--
-- DESCRIPTION: This function creates a creep of the specified type on the 
--              specified lane.
------------------------------------------------------------------------------*/
bool ClientGameLogic::createCreep(UnitType type, int laneID)
{
   // TODO: Need a function that will call the creation on the server side, 
   //just like the build tower function above.

   //should there be a delay between creep creation to ensure that they don't spawn 
   //on top of eachother? I don't know how we wanted that to work...?
   std::cout << "trying to send create creep request" << std::endl;
   Point location;
   location.x = 0;
   location.y = 0; // this doesn't do anything because the implementation sucks. Handled later.
   std::cout << "lane " << laneID << std::endl;
   clientNetwork_.createUnit(this->playerId, CREEP, location, laneID);
   
   return true;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    movePlayer
--
-- DATE:        2013/03/11
--
-- DESIGNER:    Behnam Bastami, Dennis Ho
-- PROGRAMMER:  Behnam Bastami, Jesse Wright, Dennis Ho
--
-- INTERFACE:   bool ClientGameLogic::movePlayer(Direction direction)
--
-- RETURNS:     Boolean; True if the request was sent, False otherwise
--
-- DESCRIPTION: This function moves the current player in the specified
--              direction.
------------------------------------------------------------------------------*/
bool ClientGameLogic::movePlayer(Direction direction)
{
   // TODO: validation
   std::cout << "Sending player move request" << std::endl;
   clientNetwork_.movePlayer(this->playerId, direction);

   return true;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    attack
--
-- DATE:        2013/03/11
--
-- DESIGNER:    Dennis Ho
-- PROGRAMMER:  Dennis Ho
--
-- INTERFACE:   bool ClientGameLogic::movePlayer(Direction direction)
--
-- RETURNS:     Boolean; True if the request was sent, False otherwise
--
-- DESCRIPTION: This function makes the current play attack in the specified
--              direction.
------------------------------------------------------------------------------*/
bool ClientGameLogic::attack(Direction direction)
{
   // TODO: validation
   clientNetwork_.attack(this->playerId, direction);
   return true;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    exit
--
-- DATE:        2013/03/11
--
-- DESIGNER:    Albert Liao
-- PROGRAMMER:  Albert Liao
--
-- INTERFACE:   void ClientGameLogic::exit()
--
-- RETURNS:     void
--
-- DESCRIPTION: This function sets the gameState_ variable to MAIN_MENU. 
------------------------------------------------------------------------------*/ 
void ClientGameLogic::exit()
{
   gameState_ = MAIN_MENU;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    getCurrentState
--
-- DATE:        2013/03/11
--
-- DESIGNER:    Dennis Ho
-- PROGRAMMER:  Dennis Ho
--
-- INTERFACE:   GameState ClientGameLogic::getCurrentState()
--
-- RETURNS:     GameState; the current state.
--
-- DESCRIPTION: This function returns the current state the game is in.
------------------------------------------------------------------------------*/ 
GameState ClientGameLogic::getCurrentState() {   
   return gameState_;      
}
