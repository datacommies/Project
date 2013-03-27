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

        pthread_create (&thread, NULL, handleClient, ctx);
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
        string sc = serverGameLogic_.teams[0].towers[i].serializeTower();
        send(client_, sc.data(), sc.size(), 0);
    }

    for (size_t i = 0; i < serverGameLogic_.teams[0].creeps.size(); ++i)
    {
        serverGameLogic_.teams[0].creeps[i].team = 0;
        string sc = serverGameLogic_.teams[0].creeps[i].serializeCreep();
        send(client_, sc.data(), sc.size(), 0);
    }

    //also send updated currency to teams[0] here

    /*for (size_t i = 0; i < serverGameLogic_.teams[0].players.size(); ++i)
    {
        string sc = serverGameLogic_.teams[0].players[i].serializePlayer();
        send(client_, sc.data(), sc.size(), 0);
    }*/

    //wrap into syncSecondTeam()
     for (size_t i = 0; i < serverGameLogic_.teams[1].towers.size(); ++i)
    {
        string sc = serverGameLogic_.teams[1].towers[i].serializeTower();
        send(client_, sc.data(), sc.size(), 0);
    }

    for (size_t i = 0; i < serverGameLogic_.teams[1].creeps.size(); ++i)
    {
        serverGameLogic_.teams[1].creeps[i].team = 1;
        string sc = serverGameLogic_.teams[1].creeps[i].serializeCreep();
        send(client_, sc.data(), sc.size(), 0);
    }
    
    /*for (size_t i = 0; i < serverGameLogic_.teams[1].players.size(); ++i)
    {
        string sc = serverGameLogic_.teams[1].players[i].serializePlayer();
        send(client_, sc.data(), sc.size(), 0);
    }*/

    //also send updated currency to teams[1] here

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

     while (1) {

        
        header_t head;


        cout << "Going to get a head" <<endl;
        int n = recv_complete(client_, &head, sizeof(header_t), 0);

        if (n <= 0)
            break;

        cout << "Got a head" <<endl;

        int x = 0; 

        switch(head.type){

             

            case MSG_REQUEST_CREATE:
                request_create_t rc;
                rc.head = head;
                x = recv_complete(client_, ((char*)&rc)+sizeof(header_t), sizeof(request_create_t) - sizeof(header_t), 0);

                if (x <= 0)
                    break;

                Point loc;
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