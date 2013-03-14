#include <iostream>
#include "client_network.h"
#include "../units/creep.h"
#include "client_game_logic.h"

using namespace std;

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

/* Destructor
 *
 */
ClientNetwork::~ClientNetwork()
{
    shutdown(connectsock, SHUT_RDWR);
    close(connectsock);
}

/* Connects to a server with the specified hostname and port.
 *
 * PRE: none.
 * POST: client is connected to the server with the specified hostname and port
 * ARGS: hostname - the hostname (e.g. 192.168.1.1) in string format
 *		 port - the port of the server (eg. 7400)
 *
 * RETURNS: true if connected to the server succesfully, false otherwise.
 *
 * NOTES: Initializes the connection sockets, server details (structs), then
 * establishes a connection.
 */
bool ClientNetwork::connectToServer(std::string hostname, int port)
{
	cout << "connecting.." <<endl;
	long connectsock;

	struct sockaddr_in serv_addr;
	struct hostent *server;

	//connect through TCP (for now at least)
	connectsock = socket(AF_INET, SOCK_STREAM, 0); 

	if (connectsock < 0) 
	{
		std::cerr << "ERROR: opening socket" << std::endl;
		return false;
	}

	server = gethostbyname(hostname.c_str());

	if (server == NULL) 
	{
		std::cerr << "ERROR: no such host" << std::endl;
		return false;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	memcpy((char *) &serv_addr.sin_addr.s_addr, (char*) server->h_addr,
		server->h_length);
	serv_addr.sin_port = htons(port);

	if (connect(connectsock, (struct sockaddr *) &serv_addr,
		sizeof(serv_addr)) < 0)
	{
		std::cerr << "ERROR: connecting" << std::endl;
		return false;
	}

	std::cout << "I'M CONNECTEDDDDD!!!!! YEAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;

	while (true) {
		header_t head;
		recv_complete(connectsock, &head, sizeof(head), 0);
		cout << "Recv head size:" << head.size << endl;

		// CREEP type contains a unit_t with the creep's attributes.
		if (head.type == CREEP || head.type == CASTLE) {
			unit_t u = {0};
			CLIENT_UNIT c= {0};
			//int headLength = head.size - sizeof(head);
			cout << "Waiting for " << head.size - 
			sizeof(head) << endl;
			recv_complete(connectsock, ((char*)&u) + sizeof(header_t), head.size - sizeof(head), 0);
			c.position.x = u.posx;
			c.position.y = u.posy;
			c.past_position = c.position;
			c.health = u.health;
			cout << "Creep health" << c.health << endl;
			c.type = (UnitType)head.type;
			gl->units.push_back(c);
		} else if (head.type == MSG_CLEAR) {
			gl->units.clear();
		}
	}

	cout << "Done getting a unit" << endl;

	return true;
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

/*
 * Sends a generic request to the server
 *
 * PRE: client is connected to the server
 * POST: msg is received in server side
 *
 * RETURNS: the amount of message sent
 */
int ClientNetwork::sendRequest(int msg)
{
    /* DANGER: not tested. Use but no warranties guaranteed.
    int res = send(connectsock, &msg, sizeof(int), 0);

    return res;*/
    return 1;
}
