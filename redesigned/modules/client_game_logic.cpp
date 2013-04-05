#include "client_game_logic.h"

/* Constructor
 *
 * PRE:     
 * POST:    
 * RETURNS: 
 * NOTES:   Creates a thread and starts running the module */
ClientGameLogic::ClientGameLogic(ClientNetwork& clientNetwork)
   : clientNetwork_(clientNetwork), gameState_(MAIN_MENU)
{
   clientNetwork_.gl = this;
   //unit_mutex = PTHREAD_MUTEX_INITIALIZER; // only allowed for declaration-initialization.
   pthread_mutex_init(&unit_mutex, NULL);
}
void ClientGameLogic::start () {
   gameState_ = IN_GAME;
}

void ClientGameLogic::join () {
   gameState_ = LOBBY;
}

/* Sends a create unit request to network module.
 *
 * PRE:     
 * POST:    Request has been sent to the network module (not directly to server) 
 * RETURNS: true if request was sent
 *          false if no request was sent
 * NOTES:   Partial validation is to be performed here (eg. sufficient funds, valid placement). Additional validation will be performed server side. */
bool ClientGameLogic::createTower(UnitType type, Point location)
{
   // TODO: validation

   //validate currency
   //confirm that we currently have enough currency to build that tower
   //mutex to access the currency?
   //where is the currency stored? team?
   //pass team into create unit, switch based on unit type?

   //validate location
   //if the location you are attempting to build a tower at
   //is not currently occupied and is not impassible terrain

   clientNetwork_.createUnit(this->playerId, type, location, 2); //hardcoded path = 2 (last parameter)
   
   return true;
}

/* Sends a create unit request to network module.
 *
 * PRE:     
 * POST:    Request has been sent to the network module (not directly to server) 
 * RETURNS: true if request was sent
 *          false if no request was sent
 * NOTES:   Partial validation is to be performed here (eg. sufficient funds, valid placement). Additional validation will be performed server side. */
bool ClientGameLogic::createCreep(UnitType type, int laneID)
{
   // TODO: Need a function that will call the creation on the server side, 
   //just like the build tower function above.

   //should there be a delay between creep creation to ensure that they don't spawn 
   //on top of eachother? I don't know how we wanted that to work...?

   //clientNetwork_.createUnit(this->playerId, type, location);
   
   return true;
}


/* Sends a move player (self) request to network module.
 *
 * PRE:     
 * POST:    Request has been sent to the network module (not directly to server)
 * RETURNS: true if request was sent
 *          false if no request was sent
 * NOTES:   Partial validation is to be performed here (eg. valid location). Additional validation will be performed server side. */
bool ClientGameLogic::movePlayer(Direction direction)
{
   // TODO: validation

   clientNetwork_.movePlayer(this->playerId, direction);

   return true;
}

/* Sends an attack request to network module.
 *
 * PRE:     
 * POST:    Request has been sent to the network module (not directly to server)
 * RETURNS: true if request was sent
 *          false if no request was sent
 * NOTES:   Partial validation is to be performed here (eg. builders can't attack). Additional validation will be performed server side. */
bool ClientGameLogic::attack(Direction direction)
{
   // TODO: validation

   clientNetwork_.attack(this->playerId, direction);

   return true;
}

/* Exits the game.
 *
 * PRE:     
 * POST:    
 * RETURNS: 
 * NOTES:   Any teardown should be performed here (eg. notify server). */
void ClientGameLogic::exit()
{
   gameState_ = MAIN_MENU;
}

GameState ClientGameLogic::getCurrentState() {
   return gameState_;   
}
