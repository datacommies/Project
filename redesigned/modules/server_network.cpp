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

    std::cout << "Entering initNetwork()..." << std::endl;
    
    pthread_create (&uiThread_, NULL, handleInput, this); // start server input handler.

    std::cout << "created handleInput thread..." << std::endl;
    socklen_t clientLength_ = sizeof(sockaddr_in);
    struct sockaddr_in clientAddr_ = {0};

    // Listen for new connections, or until server socket is closed.
    while (( client_ = accept(sock_, (struct sockaddr *) &clientAddr_, &clientLength_) ) > 0) { //return -1 now
        std::cout << std::endl << "new connection." << std::endl;
        pthread_t thread;
        pthread_create (&thread, NULL, handleClient, this); // TODO: use struct as parameter
        threads_.push_back(thread);
        clients_.push_back(client_);
    }
    std::cout << "Leaving initNetwork()... client_ has value " << client_<<  " " << std::endl;
}

/* Sends current game state to a client_.
 *
 * PRE:     client_ is connected
 * POST:    client_ has received current game state.
 * RETURNS: true on success
 *          false on fail
 * NOTES:   Current implementation is to refresh ALL data on each update. */
bool ServerNetwork::sync(int clientId)
{
    /*for (size_t i = 0; i < clients_.size(); i++) {
        for (size_t j = 0; j < players_.size(); j++) {
            players_[j].head.type = message;
            if (send(clients_[i], &players_[j], sizeof(player_matchmaking_t), 0) == -1)
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
    cout << "Hello world!" << endl;
    ServerNetwork* thiz = (ServerNetwork*) args;
    //long client_ = (long)args;
    while (true) {
        for (size_t i = 0; i < thiz->serverGameLogic_.teams[0].creeps.size(); ++i)
        {
            string sc = thiz->serverGameLogic_.teams[0].creeps[i].serializeCreep();
            send(thiz->client_, sc.data(), sc.size(), 0);
            cout << "Sent " << sc.size() << endl;
        }
        for (size_t i = 0; i < thiz->serverGameLogic_.teams[1].creeps.size(); ++i)
        {
            string sc = thiz->serverGameLogic_.teams[1].creeps[i].serializeCreep();
            send(thiz->client_, sc.data(), sc.size(), 0);
            cout << "Sent " << sc.size() << endl;
        }
        sleep(1);
    }

    // Add this player first
    player_matchmaking_t player;
    
    // if client_ chooses to be a player, add them to player list
    if (recv_complete(thiz->client_, &player, sizeof(player), 0) > 0) {
        player.pid = thiz->client_; // cheap and easy way of assigning a unique player id.
        player.name[PLAYER_NAME_SIZE-1] = 0;
        cout << "Player: " << player.name << " Team: " << player.team << endl;
        thiz->players_.push_back(player);
    }
    
    // Send all current players_. probably need mutex here.
    for (size_t i = 0; i < thiz->players_.size(); i++) {
        thiz->players_[i].head.type = MSG_PLAYER_UPDATE;
        
        send(thiz->client_, &thiz->players_[i], sizeof(player_matchmaking_t), 0);
    }
    //update_all_clients_(MSG_PLAYER_UPDATE);
    /*const char * data = sc.data();
    header_t * head = (header_t*)&data;
    cout << head->type << endl;*/

    player.head.type = MSG_PLAYER_UPDATE;
    // Inform all other clients_ that this player has arrived.
    for (size_t i = 0; i < thiz->clients_.size(); ++i)
    {
        if (thiz->clients_[i] != thiz->client_)
            send(thiz->clients_[i], &player, sizeof(player_matchmaking_t), 0);
    }
    std::cout << "Sent current players_" << std::endl;
    
    // send map to new connected players_
    map_t m = {{0, 0}, {0}};
    m.head.type = MSG_MAPNAME;
    strcpy(m.value, "FirstMap");
    
    send(thiz->client_, &m, sizeof(map_t), 0);
    cout << "Send map name" << endl;
    
    // read commands
    while (1) {
        header_t head;
        int n = recv_complete(thiz->client_, &head, sizeof(head), 0);
        
        if (n <= 0)
            break;
        
        if (head.type == MSG_CHAT) {
            char * buf = new char [head.size];
            memset(buf, 0, head.size);
            recv_complete(thiz->client_, buf, head.size, 0);
            cout << "Got message:" << buf << "from client_" << endl;
            delete buf;
        }
    }
    
    close(thiz->client_);
    thiz->players_.erase(std::remove(thiz->players_.begin(), thiz->players_.end(), player), thiz->players_.end());
    thiz->clients_.erase(std::remove(thiz->clients_.begin(), thiz->clients_.end(), thiz->client_), thiz->clients_.end());
    
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