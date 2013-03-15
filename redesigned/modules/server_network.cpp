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
        string sc = serverGameLogic_.teams[0].creeps[i].serializeCreep();
        send(client_, sc.data(), sc.size(), 0);
    }

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
        string sc = serverGameLogic_.teams[1].creeps[i].serializeCreep();
        send(client_, sc.data(), sc.size(), 0);
    }
    
    /*for (size_t i = 0; i < serverGameLogic_.teams[1].players.size(); ++i)
    {
        string sc = serverGameLogic_.teams[1].players[i].serializePlayer();
        send(client_, sc.data(), sc.size(), 0);
    }*/
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

void* ServerNetwork::handleClient(void* args)
{
    cout << "Handling client!" << endl;
    ClientCtx* ctx = (ClientCtx*)args;
    ServerNetwork* thiz = (ServerNetwork*) ctx->sn;
    int client_ = ctx->client;

    while (true) {
        header_t clear = {MSG_CLEAR, 0};
        if (send(client_, &clear, sizeof(header_t), 0) < 1)
            break;
        thiz->sync(client_);
        usleep(100000);
    }

    // Add this player first
    player_matchmaking_t player;
    
    // if client_ chooses to be a player, add them to player list
    if (recv_complete(client_, &player, sizeof(player), 0) > 0) {
        player.pid = client_; // cheap and easy way of assigning a unique player id.
        player.name[PLAYER_NAME_SIZE-1] = 0;
        cout << "Player: " << player.name << " Team: " << player.team << endl;
        thiz->players_.push_back(player);
    }
    
    // Send all current players_. probably need mutex here.
    for (size_t i = 0; i < thiz->players_.size(); i++) {
        thiz->players_[i].head.type = MSG_PLAYER_UPDATE;
        
        send(client_, &thiz->players_[i], sizeof(player_matchmaking_t), 0);
    }
    //update_all_clients_(MSG_PLAYER_UPDATE);
    /*const char * data = sc.data();
    header_t * head = (header_t*)&data;
    cout << head->type << endl;*/

    player.head.type = MSG_PLAYER_UPDATE;
    // Inform all other clients_ that this player has arrived.
    for (size_t i = 0; i < thiz->clients_.size(); ++i)
    {
        if (thiz->clients_[i] != client_)
            send(thiz->clients_[i], &player, sizeof(player_matchmaking_t), 0);
    }
    std::cout << "Sent current players_" << std::endl;
    
    // send map to new connected players_
    map_t m = {{0, 0}, {0}};
    m.head.type = MSG_MAPNAME;
    strcpy(m.value, "FirstMap");
    
    send(client_, &m, sizeof(map_t), 0);
    cout << "Send map name" << endl;
    
    // read commands
    while (1) {
        header_t head;
        int n = recv_complete(client_, &head, sizeof(head), 0);
        
        if (n <= 0)
            break;
        
        if (head.type == MSG_CHAT) {
            char * buf = new char [head.size];
            memset(buf, 0, head.size);
            recv_complete(client_, buf, head.size, 0);
            cout << "Got message:" << buf << "from client_" << endl;
            delete buf;
        }
    }
    
    close(client_);
    thiz->players_.erase(std::remove(thiz->players_.begin(), thiz->players_.end(), player), thiz->players_.end());
    thiz->clients_.erase(std::remove(thiz->clients_.begin(), thiz->clients_.end(), client_), thiz->clients_.end());
    
    player.head.type = MSG_PLAYER_LEAVE;
    for (size_t i = 0; i < thiz->clients_.size(); ++i)
    {
        send(thiz->clients_[i], &player, sizeof(player_matchmaking_t), 0);
    }
    
    cout << endl << "client_ disconnected." << endl << "server> ";
    cout.flush();
    
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
            cerr << ("recasdfasdfsadfv") << endl;
            return result;
        }
        
        bytesRead += result;
    }
    
    return bytesRead;
}

// Move me!
bool operator == (const player_matchmaking_t& a, const player_matchmaking_t& b) {
    return a.pid == b.pid;
}