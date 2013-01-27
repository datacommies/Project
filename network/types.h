#ifndef _TYPE_H
#define _TYPE_H

#include <cstdio>
#include <cstdlib>

#define PLAYER_NAME_SIZE 32
#define MAP_NAME_SIZE 64

enum {
    MSG_MAPNAME,            // Update everyone's map name.
    MSG_START,              // It's time to start the game!
    MSG_PLAYER_UPDATE_INFO, // Update a client's players container.
};

// Common Message Header
typedef struct {
    int type;
    int size;
} header_t;

// Map Message: The map name.
typedef struct {
    header_t head;
    char value[MAP_NAME_SIZE];
} map_t;

// Player: name, team number, role type, ready (boolean)
typedef struct {
    header_t head;
    char name[PLAYER_NAME_SIZE];
    int team;
    int role;
    bool ready;
    bool more_players;
} player_matchmaking_t;


// FUNCTION PROTOTYPES
int recv_complete (int sockfd, void *buf, size_t len, int flags);

#endif

