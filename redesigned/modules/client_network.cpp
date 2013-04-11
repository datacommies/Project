#include <iostream>
#include "client_network.h"
#include "../units/creep.h"
#include "client_game_logic.h"
#include "graphics.h"

using namespace std;

player_matchmaking_t empty = {{0, 0}, "Empty", 0, 0, 0, false};

extern Graphics* globalGraphics; 

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Aaron Lee
-- PROGRAMMER: Aaron Lee
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
ClientNetwork::ClientNetwork() {
	for (int i = 0; i < 5; ++i) {	
		memcpy(team_r+i, &empty, sizeof(player_matchmaking_t));
		memcpy(team_l+i, &empty, sizeof(player_matchmaking_t));
	}

	p = {{MSG_PLAYER_UPDATE, sizeof(player_matchmaking_t)}, {0}, 0, 0, 0, false};

}

/* Destructor
 * Aaron Lee
 */
ClientNetwork::~ClientNetwork()
{
	shutdown(connectsock, SHUT_RDWR);
	close(connectsock);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   David Czech, Behnam Bastami
-- PROGRAMMER: David Czech, Ron Bellido, Behnam Bastami
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
bool ClientNetwork::connectToServer()
{
	connecting_status = "Connecting...";
	struct sockaddr_in serv_addr;
	struct hostent *server;
	long n;

	connectsock = socket(AF_INET, SOCK_STREAM, 0); 

	if (connectsock < 0) 
	{
		std::cerr << "ERROR: opening socket" << std::endl;
		return false;
	}

	server = gethostbyname(_server.c_str());

	if (server == NULL) 
	{
		connecting_status = "Server hostname not found!";
		std::cerr << "ERROR: no such host" << std::endl;
		return false;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	memcpy((char *) &serv_addr.sin_addr.s_addr, (char*) server->h_addr,
			server->h_length);
	serv_addr.sin_port = htons(_port);

	if (connect(connectsock, (struct sockaddr *) &serv_addr,
		sizeof(serv_addr)) < 0)
	{
		connecting_status = "Could not connect, retrying...";
		std::cerr << "ERROR: connecting" << std::endl;
		return false;
	}

	connecting_status = "connected";
	std::cout << "Connected!" << std::endl;

	player_matchmaking_t p = {{0, 0}, {0}, 0, 0, 0, false};
	strcpy(p.name, _name.c_str());
	p.team = 2; // 2 is waiting/spectate team.
	p.role = 0;
	p.ready = false;

	if ((n = write(connectsock, &p, sizeof(p))) < 0)
	{
		std::cerr << "ERROR writing to socket" << std::endl;
		return false;
	}

	recvReply();
	return true;
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   David Czech, Behnam Bastami, Aaron Lee
-- PROGRAMMER: David Czech, Behnam Bastami, Ron Bellido
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void ClientNetwork::recvReply() {
	long n;

	while (true) {
		header_t head = {0};
		recv_complete(connectsock, &head, sizeof(head), 0);

		// CREEP type contains a unit_t with the creep's attributes.
		
		if(head.type == MSG_GAME_OVER){
			gameover_t go;
			recv_complete(connectsock, ((char*)&go) + sizeof(header_t), sizeof(gameover_t) - sizeof(header_t), 0);
			
			if (go.winner == WON_GAME){
				gl->win();
				cout << "We Won!" << endl;
			} else {
				gl->lose();
				cout << "We lost!" << endl;
			}
		}else if(head.type == MSG_RESOURCE_UPDATE){
			currency_t cu = {{}, 0};
			recv_complete(connectsock, ((char*)&cu) + sizeof(header_t), sizeof(currency_t) - sizeof(header_t), 0);
			pthread_mutex_lock( &gl->unit_mutex );
			gl->currency = cu.teamCurrency;
			pthread_mutex_unlock( &gl->unit_mutex );
		} else if (head.type == MSG_CREATE_UNIT) {
			unit_t u = {{0}, 0};
			recv_complete(connectsock, ((char*)&u) + sizeof(header_t), sizeof(unit_t) - sizeof(header_t), 0);
			switch (u.unit_type) {
				//FALL THROUGH
				case TOWER:
				case CASTLE: {
					tower_t t = {0};
					CLIENT_UNIT c = {0};
					//int headLength = head.size - sizeof(head);
					recv_complete(connectsock, &t, sizeof(t), 0);
					c.id = u.id;
					c.position.x = u.posx;
					c.position.y = u.posy;
					c.past_position = c.position;
					c.health = u.health;
					c.maxHealth = u.maxHealth;
					c.type = u.unit_type;
					c.team = u.team;
					pthread_mutex_lock( &gl->unit_mutex );
					bool updated = false;
					for (unsigned int i = 0; i < gl->units.size(); ++i)
					{
						if (gl->units[i].id == c.id){
							// Preserve past position and intervalue.
							c.inter_value = gl->units[i].inter_value;
							c.past_position = gl->units[i].inter_position;
							gl->units[i] = c;
							updated = true;

							if (gl->units[i].health <= 0)					
								gl->units.erase(gl->units.begin() + i);		
						}
					}
					if (!updated)
						gl->units.push_back(c);
					pthread_mutex_unlock( &gl->unit_mutex );
				break;
				}
				
				case CREEP:
				case PLAYER: {
					mobileunit_t mu = {0};
					CLIENT_UNIT c = {0};
					recv_complete(connectsock, &mu, sizeof(mu), 0);
					c.id = u.id;
					c.position.x = u.posx;
					c.position.y = u.posy;
					c.past_position = c.position;
					c.health = u.health;
					c.maxHealth = u.maxHealth;
					c.type = u.unit_type;
					c.role = mu.role;
					c.team = u.team;
					pthread_mutex_lock( &gl->unit_mutex );
					bool updated = false;
					for (unsigned int i = 0; i < gl->units.size(); ++i)
					{						
						if (gl->units[i].id == c.id){
							// Preserve past position and intervalue.
							c.inter_value = gl->units[i].inter_value;
							c.past_position = gl->units[i].inter_position;
							gl->units[i] = c;
							updated = true;

							if (gl->units[i].health <= 0)
							{
								if(u.unit_type == CREEP)
									audio_.playMusic("sounds/wilhelm.ogg");				
								gl->units.erase(gl->units.begin() + i);
							}
						}
					}
					if (!updated)
						gl->units.push_back(c);
					pthread_mutex_unlock( &gl->unit_mutex );
					break;
				}
				default:
					break;
			}
		} else if (head.type == MSG_CLEAR) {
			pthread_mutex_lock( &gl->unit_mutex );
			//gl->units.clear();
			pthread_mutex_unlock( &gl->unit_mutex );
		} else if (head.type == MSG_PLAYER_UPDATE) {
			cout << "Player updated" << endl;
			player_matchmaking_t p;
			p.head = head;
			n = recv_complete(connectsock, ((char*)&p) + sizeof(head), sizeof(p) - sizeof(head), 0);

			player_update(&p);    
		} else if (head.type == MSG_PLAYER_LEAVE) {
			player_matchmaking_t p;
			p.head = head;
			n = recv_complete(connectsock, ((char*)&p) + sizeof(head), sizeof(p) - sizeof(head), 0);

			player_leave(&p);
		} else if (head.type == MSG_MAPNAME) {
			//n = recv_complete(connectsock, ((char*)&m + sizeof(head)), sizeof(map_t) - sizeof(head), 0);
			char m[MAP_NAME_SIZE] = {0};
			if ((n = recv_complete(connectsock, m, MAP_NAME_SIZE, 0)) > 0)
				msg_mapname(m);
		} else if (head.type == MSG_START) {
			cout << "Game started!" << endl;
			
			// Ack the start.
			header_t ack = {MSG_START, 0}; 
			send(connectsock, &ack, sizeof(header_t), 0);

			// Remove the chat.
            globalGraphics->sfgChatDisplayWindow->Show(false);
            globalGraphics->sfgChatSendWindow->Show(false);
			
			gl->start();


		} else if (head.type == MSG_CHAT) { //chat message is received during the lobby
            char * buf = new char [head.size];

            recv_complete(connectsock, buf, head.size, 0);

            buf[head.size] = '\0';

            cout << "asdf: " << buf << endl; //message will contain who the message was from
            
            chatbuffer_.push_back(buf);
            //delete buf;
		}
	}
}

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Behnam Bastami, Aaron Lee
-- PROGRAMMER: Behnam Bastami
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
bool ClientNetwork::createUnit(int playerId, UnitType type, Point location, int path)
{
	//TODO: Not using playtypeerID at all!

	// Create request and send via connectsock
	request_create_t request;

	request.head.type = MSG_REQUEST_CREATE;
	request.head.size = sizeof(request_create_t);
	request.unit = type;
	request.posx = location.x;
	request.posy = location.y;
	request.path = path;
	std::cout << "sending request to create " << request.unit << " on path " << path << std::endl;
	send(connectsock, &request, sizeof(request_create_t), 0);
    return false;
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   David Czech
-- PROGRAMMER: David Czech, Ron Bellido
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/

bool ClientNetwork::updatePlayerLobby (int team, int role, const char* name, bool ready) {

	// If not empty, someone is already there!
	if ( !((team == 0 ? team_l : team_r)[role] == empty))
		return false;

	player_matchmaking_t p = {{0, 0}, {0}, 0, 0, 0, false};
	
	strcpy(p.name, name);
	p.team = team;
	p.role = role;
	p.ready = ready;

	p.head.type = MSG_PLAYER_UPDATE;
	p.head.size = sizeof(player_matchmaking_t);

	
	if ((write(connectsock, &p, sizeof(p))) < 0)
	{
		std::cerr << "ERROR writing to socket" << std::endl;
		return false;
	}

	//player_update(&p);
	
	return true;
}

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Behnam Bastami, Dennis Ho
-- PROGRAMMER: Behnam Bastami
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
bool ClientNetwork::movePlayer(int playerId, Direction direction)
{
	request_player_move_t request;

	request.head.type = MSG_REQUEST_PLAYER_MOVE;
	request.head.size = sizeof(request_player_move_t);
	request.direction = direction;
	send(connectsock, &request, sizeof(request_player_move_t), 0);

	return false;
}

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
bool ClientNetwork::attack(int playerId, Direction direction)
{
   return false;
}


/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   David Czech
-- PROGRAMMER: David Czech, Ron Bellido
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void ClientNetwork::player_update (player_matchmaking_t * p) {
	printf("Player: %d %s\t" "Team: %d\t"
		"Role: %d\t" "Ready: %s\n",
		p->pid, p->name, p->team,
		p->role, (p->ready ? "yes" : "no"));

	// Clear previous position in the team arrays.
	for (int i = 0; i < 5; i++) {
		if (team_r[i] == *p)
			memcpy(team_r+i, &empty, sizeof(player_matchmaking_t));
		else if (team_l[i] == *p)
			memcpy(team_l+i, &empty, sizeof(player_matchmaking_t));
	}
	
	waiting.erase(std::remove(waiting.begin(), waiting.end(), *p), waiting.end());

	if (p->team == 0){
		team_l[p->role] = *p;
	}
	else if (p->team == 1){
		team_r[p->role] = *p;
	}
	else 
		waiting.push_back(*p);
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   David Czech
-- PROGRAMMER: David Czech, Ron Bellido
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void ClientNetwork::player_leave (player_matchmaking_t * p) {
	printf("Player Left: %s\n", p->name);

	// Remove player from the waiting list.
	if (p->team == 2) {
		waiting.erase(std::remove(waiting.begin(), waiting.end(), *p), waiting.end());
	} else {
		// Remove the player from the team arrays.
		if (p->team == 0){
			memcpy(team_l+p->role, &empty, sizeof(player_matchmaking_t));
		} else if (p->team == 1) {
			memcpy(team_r+p->role, &empty, sizeof(player_matchmaking_t));
		}
	}
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   David Czech
-- PROGRAMMER: David Czech
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void ClientNetwork::msg_mapname (char * map) {
	printf("Got map name: %s\n", map);
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   David Czech
-- PROGRAMMER: David Czech
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void ClientNetwork::msg_chat (char * text) {
	printf("message: %s\n", text);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Ron Bellido, Behnam Bastami
-- PROGRAMMER: Ron Bellido
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void ClientNetwork::send_chatmsg(string msg) {
	chatmsg_t * chat = (chatmsg_t*) new char[sizeof(header_t) + msg.size()];
	chat->head.type = MSG_CHAT;
	chat->head.size = msg.size();
	strncpy(chat->msgbuf, msg.c_str(), chat->head.size);

	send(connectsock, chat, sizeof(header_t) + msg.size(), 0);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   David Czech
--
-- PROGRAMMER: David Czech, Behnam Bastami
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
int ClientNetwork::recv_complete (int sockfd, void *buf, size_t len, int flags) {
    size_t bytesRead = 0;
    ssize_t result;
    
    while (bytesRead < len) {
        result = recv (sockfd, (char*)buf + bytesRead, len - bytesRead, flags);
        
        if (result < 1) {
            cerr << ("Connection terminated by server") << endl;
            exit(0);
            return result;
        }
        
        bytesRead += result;
    }
    
    return bytesRead;
}
