#include <iostream>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include "types.h"

using namespace std;

vector <player_matchmaking_t> players;


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
    close(client);
}


int sock;
void killsocket(int sign) {
    cout << "Closing socket" << endl;
    close(sock);
}


int main() {
    long client;
    socklen_t clilen;
    struct sockaddr_in cli_addr;
    vector<pthread_t> threads;

    sock = server();
    signal(SIGINT, killsocket);

    cout << "Listening for connections..." << endl;

    while ((client = accept(sock, (struct sockaddr *)&cli_addr, &clilen)) > 0) {
        cout << "New connection." << endl;
        pthread_t thread;
        pthread_create (&thread, NULL, handleclient, (void*)client);
        threads.push_back(thread);
    }

    cout << "Closing down." << endl;
    for (size_t i = 0; i < threads.size(); i++)
        pthread_join(threads[i], NULL);

    return 0;
}

