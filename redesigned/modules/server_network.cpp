#include "server_network.h"

/* Constructor
 *
 * PRE:     
 * POST:    
 * RETURNS: 
 * NOTES:   Creates a thread and starts running the module */
ServerNetwork::ServerNetwork(ServerGameLogic& serverGameLogic)
   : serverGameLogic_(serverGameLogic) 
{
   // TODO: create a thread and begin processing
}

/* Sends current game state to a client.
 *
 * PRE:     Client is connected
 * POST:    Client has received current game state.
 * RETURNS: true on success
 *          false on fail
 * NOTES:   Current implementation is to refresh ALL data on each update. */
bool ServerNetwork::sync(int clientId)
{
   return false;
}