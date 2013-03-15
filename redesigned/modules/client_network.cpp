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
//gl = (ClientGameLogic*) malloc (sizeof(ClientGameLogic*));

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

	struct sockaddr_in serv_addr;
	struct hostent *server;

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
	recvReply();
	return true;
}

void ClientNetwork::recvReply() {
	while (true) {
		header_t head = {0};
		recv_complete(connectsock, &head, sizeof(head), 0);

		// CREEP type contains a unit_t with the creep's attributes.
		if (head.type == MSG_CREATE_UNIT) {
			unit_t u = {0};
			recv_complete(connectsock, ((char*)&u) + sizeof(header_t), sizeof(unit_t) - sizeof(header_t), 0);
			printf("Unit: x: %d, y: %d, health: %d\n", u.posx, u.posy, u.health);
			switch (u.unit_type) {
				//FALL THROUGH
				case TOWER:
				case CASTLE: {
					tower_t t = {0};
					CLIENT_UNIT c = {0};
					//int headLength = head.size - sizeof(head);
					recv_complete(connectsock, &t, sizeof(t), 0);
					c.position.x = u.posx;
					c.position.y = u.posy;
					c.past_position = c.position;
					c.health = u.health;
					c.type = u.unit_type;
					pthread_mutex_lock( &gl->unit_mutex );
					printf("Adding unit!\n");
					gl->units.push_back(c);
					pthread_mutex_unlock( &gl->unit_mutex );
				break;
				}
				
				case CREEP:
				case PLAYER: {
					mobileunit_t mu = {0};
					CLIENT_UNIT c = {0};
					recv_complete(connectsock, &mu, sizeof(mu), 0);
					c.position.x = u.posx;
					c.position.y = u.posy;
					c.past_position = c.position;
					c.health = u.health;
					c.type = u.unit_type;
					pthread_mutex_lock( &gl->unit_mutex );
					gl->units.push_back(c);
					pthread_mutex_unlock( &gl->unit_mutex );
					break;
				}
			}
		} else if (head.type == MSG_CLEAR) {
			pthread_mutex_lock( &gl->unit_mutex );
			gl->units.clear();
			pthread_mutex_unlock( &gl->unit_mutex );
		}
	}
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
	//TODO: Not using playtypeerID at all!


	// Create request and send via connectsock
	request_create_t request;

	request.head.type = MSG_REQUEST_CREATE;
	request.head.size = sizeof(request_create_t);
	request.unit = type;
	request.posx = location.x;
	request.posy = location.y;

	send(connectsock, &request, sizeof(request_create_t), 0);
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
	request_player_move_t request;

	request.head.type = MSG_REQUEST_PLAYER_MOVE;
	request.head.size = sizeof(request_player_move_t);
	request.direction = direction;
	send(connectsock, &request, sizeof(request_player_move_t), 0);

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
    return 1;
}
