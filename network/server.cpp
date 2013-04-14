#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "types.h"

using namespace std;

vector<int> clients;       // client sockets
vector <player_matchmaking_t> players;

// Updates all clients in server
bool update_all_clients(int message) {
    for (size_t i = 0; i < clients.size(); i++) {
        for (size_t j = 0; j < players.size(); j++) {
            players[j].head.type = message;
            if (send(clients[i], &players[j], sizeof(player_matchmaking_t), 0) == -1)
                return false;
        }
    }
    return true;
}

void * handle_client(void* thing) {
    int client = (long)thing;

    // Add this player first
    player_matchmaking_t player;

    if (recv_complete(client, &player, sizeof(player), 0) > 0) {
        player.pid = client; // cheap and easy way of assigning a unique player id.
        player.name[PLAYER_NAME_SIZE-1] = 0;
        cout << "Player: " << player.name << " Team: " << player.team << endl;
        players.push_back(player);
    }

    // Send all current players. probably need mutex here.
    for (size_t i = 0; i < players.size(); i++) {
        players[i].head.type = MSG_PLAYER_UPDATE;

        send(client, &players[i], sizeof(player_matchmaking_t), 0);
    }
    //update_all_clients(MSG_PLAYER_UPDATE);

    player.head.type = MSG_PLAYER_UPDATE;
    // Inform all other clients that this player has arrived.
    for (size_t i = 0; i < clients.size(); ++i)
    {
        if (clients[i] != client)
            send(clients[i], &player, sizeof(player_matchmaking_t), 0);
    }
    cout << "Sent current players" << endl;

    map_t m = {{0, 0}, {0}};
    m.head.type = MSG_MAPNAME;
    strcpy(m.value, "FirstMap");

    send(client, &m, sizeof(map_t), 0);
    cout << "Send map name" << endl;

    while (1) {
        header_t head;
        int n = recv_complete(client, &head, sizeof(head), 0);

        if (n < 0) break;

        if (head.type == MSG_CHAT) {
            char * buf = new char [head.size];
            memset(buf, 0, head.size);
            recv_complete(client, buf, head.size, 0);
            cout << "Got message:" << buf << "from client" << endl;
            delete buf;
        }
    }

    close(client);
    players.erase(std::remove(players.begin(), players.end(), player), players.end());
    clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());

    player.head.type = MSG_PLAYER_LEAVE;
    for (size_t i = 0; i < clients.size(); ++i)
    {
        send(clients[i], &player, sizeof(player_matchmaking_t), 0);
    }
    cout << endl << "Client disconnected." << endl << "server> ";
    cout.flush();

    return NULL;
}

int sock;
void killsocket(int sign) {
    cout << "Caught signal " << sign << " "
         << "Closing socket" << endl;
    for (size_t  i = 0; i < clients.size(); ++i)
    {
        shutdown(clients[i], SHUT_RDWR);
        close(clients[i]);
    }
    shutdown(sock, SHUT_RDWR);
    close(sock);
}

void * handle_input (void *) {
    string line;
    while (cout << "server> " && getline(cin, line)) {
        string s;
        stringstream ss(line);
        ss >> s;

        if (s == "exit") {
            shutdown(sock, SHUT_RDWR);
            close(sock);
        } else if (s == "list") {
            for (size_t i = 0; i < players.size(); ++i) {
                player_matchmaking_t& p = players[i];
                printf("%s\t %d\t %d\t %s\n",p.name, p.team, p.role, (p.ready ? "yes" : "no"));
            }
        } else if (s == "chat") {
            string rest;
            ss >> ws;
            getline(ss, rest);
            cout << "rest: " << rest << endl;

            for (size_t i = 0; i < clients.size(); ++i) {
                send_chat(clients[i], rest);
            }
        }
    }

    return NULL;
}

int main () {
    pthread_t ui_thread;
    long client; // the correct type here in uintptr: an int that has the size of a pointer.
    socklen_t clilen;
    struct sockaddr_in cli_addr;

    vector<pthread_t> threads; // client handler threads.

    // Start server on default port
    sock = server();
    signal(SIGINT, killsocket); // handle ctrl-c nicely.

    cout << "Listening for connections..." << endl;
    pthread_create (&ui_thread, NULL, handle_input, NULL); // start server input handler.
    // Listen for new connections, or until server socket is closed.
    while (( client = accept(sock, (struct sockaddr *) &cli_addr, &clilen) ) > 0) {
        cout << endl << "new connection." << endl;
        pthread_t thread;
        pthread_create (&thread, NULL, handle_client, (void*)client);
        threads.push_back(thread);
        clients.push_back(client);
    }

    cout << "Closing down." << endl;

    for (size_t i =0; i < threads.size(); i++)
        pthread_join (threads[i], NULL);

    return 0;
}

