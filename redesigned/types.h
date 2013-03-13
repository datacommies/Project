#ifndef _TYPE_H
#define _TYPE_H

#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define PLAYER_NAME_SIZE 32
#define MAP_NAME_SIZE  64

enum {
    MSG_MAPNAME,            // Update everyone's mapname
    MSG_START,              // It's time to start the game!
    MSG_PLAYER_UPDATE, // Update a client's players container.
    MSG_PLAYER_JOIN,
    MSG_PLAYER_LEAVE,
    MSG_CHAT,                // A chat message has been generated
    MSG_TOWER_CREATE,
    MSG_TOWER_REMOVE,
    MSG_TOWER_UPDATE,
    MSG_CREEP_CREATE,
    MSG_CREEP_REMOVE, //creeps dying
    MSG_CREEP_UPDATE,
    MSG_RESOURCE_UPDATE
};

// Use resouce UnitType instead!
enum UnitTypes {
	TYPE_CREEP,
	TYPE_TOWER,
	TYPE_PLAYER,
	TYPE_CASTLE
} ;

// Common Message Header
typedef struct {
    int type; //MSG_PLAYER_UPDATE for e.g.
    int size; //sizeof(player_matchmakcing_t) for eg.
} header_t;

// Map message: the map name.
typedef struct {
    header_t head;
    char value [MAP_NAME_SIZE];
} map_t;

// Player: name, team id, role type, ready - is player ready to start.
typedef struct {
    header_t head;
    char name[PLAYER_NAME_SIZE];
    int pid;
    int team;
    int role;
    bool ready;
} player_matchmaking_t;

// Game session structs
typedef struct {
    header_t head;
    int id;
    int team;
    int role;
    float xpos;
    float ypos;
    int health;
} player_game_t;

typedef struct {
    int wallArmour;
} tower_t;

/*typedef struct {
    header_t head;
    int id;
    //int type;
    float xpos;
    float ypos;
    int health;
} castle_t;*/

typedef struct {
    header_t head;
    int team;
    int value;
} resource_t;

/*typedef struct {
    header_t head;
    int id;
    int team;
    int health;
    float xpos;
    float ypos;
} creep_t;*/

typedef struct {
    header_t head;
    int id; //unit id
    int posx, posy;
    int health;
    //int iElement;
    int attackDamage;//damage that the unit deals per hit
    int attackRange; //distance that the unit can successfully attack
    int attackSpeed; //the speed which the attack counter has to hit in order to initiate an attack
    int perception;  //distance that the unit can aquire a target
    int attackCount; //counter between unit attacks
} unit_t;

typedef struct {
    int speed;
    int direction;
} mobileunit_t;


bool operator == (const player_matchmaking_t& a, const player_matchmaking_t& b);
void error (const char *msg);
int server (int port = 4545);
int recv_complete (int sockfd, void *buf, size_t len, int flags);
int send_chat ( int client, const std::string & body );

#endif

