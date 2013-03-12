#include "server_network.h"

using namespace std;

// note: use of POSIX calls makes this platform-dependent


/* Constructor
 *
 * PRE:     
 * POST:    
 * RETURNS: 
 * NOTES:   Creates a thread and starts running the module */
ServerNetwork::ServerNetwork(ServerGameLogic& serverGameLogic)
   : serverGameLogic_(serverGameLogic) 
{
    // initialize everything
    
    
   // TODO: create a thread and begin processing

    /*
    pthread_t ui_thread;
    long client; // the correct type here in uintptr: an int that has the size of a pointer.
    socklen_t clilen;
    struct sockaddr_in cli_addr;
    
    vector<pthread_t> threads; // client handler threads.
    
    // Start server on default port
    sock = initSock();
    //signal(SIGINT, killsocket); // handle ctrl-c nicely.
    
    cout << "Listening for connections..." << endl;
    pthread_create (&ui_thread, NULL, handle_input, NULL); // start server input handler.
    
    // Listen for new connections, or until server socket is closed.
    while (( client = accept(sock, (struct sockaddr *) &cli_addr, &clilen) ) > 0) {
        //cout << endl << "new connection." << endl;
        pthread_t thread;
        pthread_create (&thread, NULL, handle_client, (void*)client); // TODO: use struct as parameter
        threads.push_back(thread);
        
        
        
        clients.push_back(client);
    }
    
    cout << "Closing down." << endl;
    
    for (size_t i=0; i < threads.size(); i++)
        pthread_join (threads[i], NULL);*/
}

// Move me!
bool operator == (const player_matchmaking_t& a, const player_matchmaking_t& b) {
    return a.pid == b.pid;
}

void ServerNetwork::initNetwork()
{
    std::cout << "Listening for connections..." << std::endl;
    
    pthread_create (&ui_thread, NULL, handleInput, this); // start server input handler.
    
    // Listen for new connections, or until server socket is closed.
    while (( client = accept(sock, (struct sockaddr *) &cli_addr, &clilen) ) > 0) {
        std::cout << std::endl << "new connection." << std::endl;
        pthread_t thread;
        pthread_create (&thread, NULL, handleClient, this); // TODO: use struct as parameter
        threads.push_back(thread);
        clients.push_back(client);
    }
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
    /*for (size_t i = 0; i < clients.size(); i++) {
        for (size_t j = 0; j < players.size(); j++) {
            players[j].head.type = message;
            if (send(clients[i], &players[j], sizeof(player_matchmaking_t), 0) == -1)
                return false;
        }
    }*/
    return true;
}

// fatal error wrapper
void ServerNetwork::error (const char *msg)
{
    perror(msg);
    exit(1);
}

// create nix socket
// returns error code; arg: port number
int ServerNetwork::initSock(int port)
{
    int ov = 1;
    struct sockaddr_in serv_addr;
    
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        error("ERROR opening socket");
    
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &ov, sizeof (ov));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    
    if (bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    // Listen for connections
    
	// queue up to MAX connect requests
    listen(sock, MAX_CONNECTIONS);
    return sock;
}

/* Interactive CLI console
 *
 * PRE:     Server sockets started
 * POST:    
 * RETURNS: void*
 * NOTES:   Current implementation is to refresh ALL data on each update. */
void* ServerNetwork::handleInput(void* args)
{
    ServerNetwork * thiz = (ServerNetwork*) args;
    std::string line;
    
    while (cout << "server> " && getline(cin, line)) {
        std::string s;
        std::stringstream ss(line);
        ss >> s;
        
        if (s == "exit") {
            shutdown(thiz->sock, SHUT_RDWR);
            close(thiz->sock);
            exit(0);
        } else if (s == "list") {
            for (size_t i = 0; i < thiz->players.size(); ++i) {
                player_matchmaking_t& p = thiz->players[i];
                printf("%s\t %d\t %d\t %s\n",p.name, p.team, p.role, (p.ready ? "yes" : "no"));
            }
        } else if (s == "chat") {
            string rest;
            ss >> ws;
            getline(ss, rest);
            std::cout << "rest: " << rest << std::endl;
            //create an iterator
            std::vector<int>::iterator it;
            
            for (it = thiz->clients.begin() ; it!= thiz->clients.end() ; ++it){
            //for (size_t i = 0; i < thiz->clients.size(); ++i) {
               // send_chat(thiz->clients[i], rest);
                //send_chat(*it, rest);
            }
        }
    }
    
    return NULL;
}

void* ServerNetwork::handleClient(void* args)
{
    ServerNetwork* thiz = (ServerNetwork*) args;
    //long client = (long)args;
    
    // Add this player first
    player_matchmaking_t player;
    
    // if client chooses to be a player, add them to player list
    if (recv_complete(thiz->client, &player, sizeof(player), 0) > 0) {
        player.pid = thiz->client; // cheap and easy way of assigning a unique player id.
        player.name[PLAYER_NAME_SIZE-1] = 0;
        cout << "Player: " << player.name << " Team: " << player.team << endl;
        thiz->players.push_back(player);
    }
    
    // Send all current players. probably need mutex here.
    for (size_t i = 0; i < thiz->players.size(); i++) {
        thiz->players[i].head.type = MSG_PLAYER_UPDATE;
        
        send(thiz->client, &thiz->players[i], sizeof(player_matchmaking_t), 0);
    }
    //update_all_clients(MSG_PLAYER_UPDATE);
    
    player.head.type = MSG_PLAYER_UPDATE;
    // Inform all other clients that this player has arrived.
    for (size_t i = 0; i < thiz->clients.size(); ++i)
    {
        if (thiz->clients[i] != thiz->client)
            send(thiz->clients[i], &player, sizeof(player_matchmaking_t), 0);
    }
    std::cout << "Sent current players" << std::endl;
    
    // send map to new connected players
    map_t m = {{0, 0}, {0}};
    m.head.type = MSG_MAPNAME;
    strcpy(m.value, "FirstMap");
    
    send(thiz->client, &m, sizeof(map_t), 0);
    cout << "Send map name" << endl;
    
    // read commands
    while (1) {
        header_t head;
        int n = recv_complete(thiz->client, &head, sizeof(head), 0);
        
        if (n < 0)
            break;
        
        if (head.type == MSG_CHAT) {
            char * buf = new char [head.size];
            memset(buf, 0, head.size);
            recv_complete(thiz->client, buf, head.size, 0);
            cout << "Got message:" << buf << "from client" << endl;
            delete buf;
        }
    }
    
    close(thiz->client);
    thiz->players.erase(std::remove(thiz->players.begin(), thiz->players.end(), player), thiz->players.end());
    thiz->clients.erase(std::remove(thiz->clients.begin(), thiz->clients.end(), thiz->client), thiz->clients.end());
    
    player.head.type = MSG_PLAYER_LEAVE;
    for (size_t i = 0; i < thiz->clients.size(); ++i)
    {
        send(thiz->clients[i], &player, sizeof(player_matchmaking_t), 0);
    }
    
    cout << endl << "Client disconnected." << endl << "server> ";
    cout.flush();
    
    return NULL;
}

void ServerNetwork::handleRequests()
{
    
}

/* Receive len amount of byte completely (no partial recv) */
// returns int bytes read
// recv_complete
int ServerNetwork::recv_complete (int sockfd, void *buf, size_t len, int flags) {
    size_t bytesRead = 0;
    ssize_t result;
    
    while (bytesRead < len) {
        result = recv (sockfd, (char*)buf + bytesRead, len - bytesRead, flags);
        
        if (result < 1)
            cerr << "recv" << endl;//error("recv");
        
        bytesRead += result;
    }
    
    return bytesRead;
}