#include "server_network.h"

using namespace std;

// note: use of POSIX calls makes this platform-dependent

// use a pointer to a ClientCtx to pass both "this" pointer and client socket.
struct ClientCtx {
    ServerNetwork * sn;
    int client;
};

/* Constructor
 *
 * PRE:     
 * POST:    
 * RETURNS: 
 * NOTES:   Creates a thread and starts running the module */
ServerNetwork::ServerNetwork(ServerGameLogic& serverGameLogic)
   : serverGameLogic_(serverGameLogic) {}

// create nix socket
// returns error code; arg: port number
int ServerNetwork::initSock(int port)
{
    int ov = 1;
    struct sockaddr_in serv_addr;
    
    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ < 0)
            error("ERROR opening socket");
    
    setsockopt(sock_, SOL_SOCKET, SO_REUSEADDR, &ov, sizeof (ov));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    cout << "port: " << port << endl;
    if (bind(sock_, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    // Listen for connections
    
	// queue up to MAX connect requests
    listen(sock_, MAX_CONNECTIONS);
    return sock_;
}

void ServerNetwork::initNetwork()
{    
    pthread_create (&uiThread_, NULL, handleInput, this); // start server input handler.

    socklen_t clientLength_ = sizeof(sockaddr_in);
    struct sockaddr_in clientAddr_ = {0};
    int client = 0;
    // Listen for new connections, or until server socket is closed.
    while (( client = accept(sock_, (struct sockaddr *) &clientAddr_, &clientLength_) ) > 0) {

        std::cout << std::endl << "new connection." << std::endl;
        pthread_t thread;

        // Setup context struct
        ClientCtx * ctx = new ClientCtx;
        ctx->sn = this;
        ctx->client = client;

        //pthread_create(&thread, NULL, handleClient, ctx);
        pthread_create (&thread, NULL, handle_single_client_lobby, ctx);
        threads_.push_back(thread);
        clients_.push_back(client);
    }
}

/* Sends current game state to a client_.
 *
 * PRE:     client_ is connected
 * POST:    client_ has received current game state.
 * RETURNS: true on success
 *          false on fail
 * NOTES:   Current implementation is to refresh ALL data on each update. */
bool ServerNetwork::sync(int client_)
{
    //wrap into syncFirstTeam()
    for (size_t i = 0; i < serverGameLogic_.teams[0].towers.size(); ++i)
    {
        string sc = serverGameLogic_.teams[0].towers[i]->serializeTower();
        send(client_, sc.data(), sc.size(), 0);
    }

    for (size_t i = 0; i < serverGameLogic_.teams[0].creeps.size(); ++i)
    {
        serverGameLogic_.teams[0].creeps[i]->team = 0;
        string sc = serverGameLogic_.teams[0].creeps[i]->serializeCreep();
        send(client_, sc.data(), sc.size(), 0);
    }

    for (size_t i = 0; i < serverGameLogic_.teams[0].players.size(); ++i)
    {
        string sc = serverGameLogic_.teams[0].players[i]->serializeMobileUnit();
        send(client_, sc.data(), sc.size(), 0);
    }

    currency_t cu1 = {0};
    cu1.head.type = MSG_RESOURCE_UPDATE;
    cu1.teamCurrency = 2000;//serverGameLogic_.teams[0].currency;
    cu1.head.size = sizeof(currency_t);
    send(client_, (const char*)&cu1, sizeof(currency_t), 0);

    //wrap into syncSecondTeam()
     for (size_t i = 0; i < serverGameLogic_.teams[1].towers.size(); ++i)
    {
        string sc = serverGameLogic_.teams[1].towers[i]->serializeTower();
        send(client_, sc.data(), sc.size(), 0);
    }

    for (size_t i = 0; i < serverGameLogic_.teams[1].creeps.size(); ++i)
    {
        serverGameLogic_.teams[1].creeps[i]->team = 1;
        string sc = serverGameLogic_.teams[1].creeps[i]->serializeCreep();
        send(client_, sc.data(), sc.size(), 0);
    }
    
    for (size_t i = 0; i < serverGameLogic_.teams[1].players.size(); ++i)
    {
        string sc = serverGameLogic_.teams[1].players[i]->serializeMobileUnit();
        send(client_, sc.data(), sc.size(), 0);
    }

    currency_t cu2 = {0};
    cu2.head.type = MSG_RESOURCE_UPDATE;
    cu2.teamCurrency = 1000;//serverGameLogic_.teams[1].currency;
    cu2.head.size = sizeof(currency_t);
    send(client_, (const char*)&cu2, sizeof(currency_t), 0);

    return true;
}

// fatal error wrapper
void ServerNetwork::error (const char *msg)
{
    perror(msg);
    exit(1);
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
            shutdown(thiz->sock_, SHUT_RDWR);
            close(thiz->sock_);
            exit(0);
        } else if (s == "list") {
            for (size_t i = 0; i < thiz->players_.size(); ++i) {
                player_matchmaking_t& p = thiz->players_[i];
                printf("%s\t %d\t %d\t %s\n",p.name, p.team, p.role, (p.ready ? "yes" : "no"));
            }
        } else if (s == "chat") {
            string rest;
            ss >> ws;
            getline(ss, rest);
            std::cout << "rest: " << rest << std::endl;
            //create an iterator
            std::vector<int>::iterator it;
            
            for (it = thiz->clients_.begin() ; it!= thiz->clients_.end() ; ++it){
            //for (size_t i = 0; i < thiz->clients_.size(); ++i) {
               // send_chat(thiz->clients_[i], rest);
                //send_chat(*it, rest);
            }
        }
    }
    
    return NULL;
}

void* ServerNetwork::handleClientRequest(void* args)
{
    ClientCtx* ctx = (ClientCtx*)args;
    ServerNetwork* thiz = (ServerNetwork*) ctx->sn;
    int client_ = ctx->client;

    //Player p;
    //thiz->serverGameLogic_.teams[0].players.push_back(p);

    while (1) {
        header_t head;

        cout << "Going to get a head" <<endl;
        int n = recv_complete(client_, &head, sizeof(header_t), 0);

        if (n <= 0)
            break;

        cout << "Got a head" <<endl;

        int x = 0; 

        Point loc;
        switch(head.type){
            case MSG_REQUEST_CREATE:
                request_create_t rc;
                rc.head = head;
                x = recv_complete(client_, ((char*)&rc)+sizeof(header_t), sizeof(request_create_t) - sizeof(header_t), 0);

                if (x <= 0)
                    break;

                //Point loc;
                loc.x = rc.posx;
                loc.y = rc.posy;
                thiz->serverGameLogic_.receiveCreateUnitCommand(client_, rc.unit, loc);
            break;

            case MSG_REQUEST_PLAYER_MOVE:
                request_player_move_t rpm;
                rpm.head = head;
                x = recv_complete(client_, ((char*) &rpm) + sizeof(header_t), sizeof(request_player_move_t) - sizeof(header_t), 0);

                if (x <=0)
                    break;

                Direction dir = rpm.direction;

                cout << "Direction: " << dir << endl;
                thiz->serverGameLogic_.receiveMovePlayerCommand(client_, dir);
                
            break;
       }
    }

    return NULL;
}

void* ServerNetwork::handleClient(void* args)
{
    cout << "Handling client!" << endl;
    ClientCtx* ctx = (ClientCtx*)args;
    ServerNetwork* thiz = (ServerNetwork*) ctx->sn;
    int client_ = ctx->client;

    // Create client request handler thread.
    pthread_create (&thiz->crThread_, NULL, handleClientRequest, args); // start server input handler.

    while (true) {
        header_t clear = {MSG_CLEAR, 0};
        if (send(client_, &clear, sizeof(header_t), 0) < 1)
            break;
        thiz->sync(client_);
        usleep(100000);
    }
 
    return NULL;
}

void ServerNetwork::handleRequests()
{
    
}

/* Receive len amount of byte completely (no partial recv) */
// returns int bytes read
// recv_complete
int recv_complete (int sockfd, void *buf, size_t len, int flags) {
    size_t bytesRead = 0;
    ssize_t result;
    
    while (bytesRead < len) {
        result = recv (sockfd, (char*)buf + bytesRead, len - bytesRead, flags);
        
        if (result < 1) {
            cerr << ("Error in handleRequest() recv()") << endl;
            return result;
        }
        
        bytesRead += result;
    }
    
    return bytesRead;
}

// Move me! //NO!
bool operator == (const player_matchmaking_t& a, const player_matchmaking_t& b) {
    return a.pid == b.pid;
}

//Lobby functions
bool ServerNetwork::update_all_clients(int message) {
    for (size_t i = 0; i < clients_.size(); i++) {
        for (size_t j = 0; j < players_.size(); j++) {
            players_[j].head.type = message;
            if (send(clients_[i], &players_[j], sizeof(player_matchmaking_t), 0) == -1)
                return false;
        }
    }
    return true;
}

// Basically runs another function without making it static (this one is static)
void * ServerNetwork::handle_single_client_lobby(void* thing) {
    cout << "Handling client!" << endl;
    ClientCtx* ctx = (ClientCtx*)thing;
    ServerNetwork* thiz = (ServerNetwork*) ctx->sn;
    return thiz->handle_client_lobby(ctx);
}

void * ServerNetwork::handle_client_lobby(void * ctx)
{
    ClientCtx* ctax = (ClientCtx*)ctx;
    int client = ctax->client;
    // Add this player first
    player_matchmaking_t player;

    if (recv_complete(client, &player, sizeof(player), 0) > 0) {
        player.pid = client; // cheap and easy way of assigning a unique player id.
        player.name[PLAYER_NAME_SIZE-1] = 0;
        cout << "Player: " << player.name << " Team: " << player.team << endl;
        players_.push_back(player);
    }

    // Send all current players_. probably need mutex here.
    for (size_t i = 0; i < players_.size(); i++) {
        players_[i].head.type = MSG_PLAYER_UPDATE;

        send(client, &players_[i], sizeof(player_matchmaking_t), 0);
    }
    //update_all_clients(MSG_PLAYER_UPDATE);

    player.head.type = MSG_PLAYER_UPDATE;
    // Inform all other clients_ that this player has arrived.
    for (size_t i = 0; i < clients_.size(); ++i)
    {
        if (clients_[i] != client)
            send(clients_[i], &player, sizeof(player_matchmaking_t), 0);
    }
    cout << "Sent current players_" << endl;

    map_t m = {{0, 0}, {0}};
    m.head.type = MSG_MAPNAME;
    strcpy(m.value, "FirstMap");

    send(client, &m, sizeof(map_t), 0);
    cout << "Send map name" << endl;

    while (1) {
        header_t head;
        int n = recv_complete(client, &head, sizeof(head), 0);

        if (n <= 0) break;

        if (head.type == MSG_CHAT) {
            char * buf = new char [head.size];
            memset(buf, 0, head.size);
            recv_complete(client, buf, head.size, 0);
            cout << "Got message:" << buf << "from client" << endl;
            delete buf;
        }

        if (head.type == MSG_PLAYER_UPDATE) {
            bool start = true;
            recv_complete(client, ((char *) &player) + sizeof(header_t), sizeof(player_matchmaking_t) - sizeof(header_t), 0);
            
            for (size_t i = 0; i < players_.size(); ++i) {
                if (players_[i].pid == client) {
                    // Validate and update player info.
                    players_[i].ready = player.ready;
                }

            }

            for (size_t i = 0; i < clients_.size(); ++i)
            {
                if (clients_[i] != client)
                    send(clients_[i], &player, sizeof(player_matchmaking_t), 0);
            }

            for (size_t i = 0; i < players_.size(); ++i)
            {
                start = start && players_[i].ready;
            }            

            if (start)
            {
                for (size_t i = 0; i < clients_.size(); ++i)
                {
                    header_t start_head;
                    start_head.type = MSG_START;
                    start_head.size = 0;
                    send(clients_[i], &start_head, sizeof(start_head), 0);
                }              

                serverGameLogic_.initializeTeams(players_);

                handleClient(ctx);
            }
        }
    }

    close(client);
    players_.erase(std::remove(players_.begin(), players_.end(), player), players_.end());
    clients_.erase(std::remove(clients_.begin(), clients_.end(), client), clients_.end());

    player.head.type = MSG_PLAYER_LEAVE;
    for (size_t i = 0; i < clients_.size(); ++i)
    {
        send(clients_[i], &player, sizeof(player_matchmaking_t), 0);
    }
    cout << endl << "Client disconnected." << endl << "server> ";
    cout.flush();

    return NULL;
}
