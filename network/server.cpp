#include <iostream>
#include <netinet/in.h>
#include <pthread>
#include <sys/sockets.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include "types.h"

using namespace std;

vector <player_matchmaking_t> players;

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int server() {
    struct sockaddr_in server_addr;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        error("ERROR opening socket");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_saddr = INADDR_ANY;
    serv_addr.sin_port = htons(4545);

    if (bind(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR binding");

    listen(sock, 5);

    return sock;
}


void * handleclient(void* thing) {
    int client = (long)thing;
    player_matchmaking_t player;

    if (recv_complete(client, &player, sizeof(player), 0) > 0) {
        player.name[PLAYER_NAME_SIZE-1] = 0;
        cout << "Player: " << player.name << " Team: " << player.team << endl;
        players.push_back(player);
    }

    for (size_t i = 0; i < players.size(); i++) {
        players[i].more_players = true;
        if (i+1 == players.size())  // last player
            players[i].more_players = false;
        send(client, &players[i], sizeof(player_matchmaking_t), 0);
    }

    cout << "Sent current players" << endl;
}

