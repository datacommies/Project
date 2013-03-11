#include "client_network.h"

/* Constructor
 *
 * PRE:     
 * POST:    
 * RETURNS: 
 * NOTES:   Creates a thread and starts running the module */
ClientNetwork::ClientNetwork()
{
   // TODO: create a thread and begin processing
}

/* Sends a create unit request to the server.
 *
 * PRE:     Client is connected
 * POST:    Request has been sent to server
 * RETURNS: true on success
 *          false on fail
 * NOTES:   No validation performed here. */
bool ClientNetwork::createUnit(int playerId, UnitType type, Point location)
{
   return false;
}

/* Sends a move player request to the server.
 *
 * PRE:     Client is connected
 * POST:    Request has been sent to server
 * RETURNS: true on success
 *          false on fail
 * NOTES:   No validation performed here. */
bool ClientNetwork::movePlayer(int playerId, Direction direction)
{
   return false;
}

/* Sends an attack request to the server.
 *
 * PRE:     Client is connected
 * POST:    Request has been sent to the server
 * RETURNS: true on success
 *          false on fail
 * NOTES:   No validation performed here. */
bool ClientNetwork::attack(int playerId, Direction direction)
{
   return false;
}