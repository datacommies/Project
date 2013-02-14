sync_all_clients()
- Global update; ensures all client data is synchronized.
    1.) Retrieve all clients from the client vector.
    2.) For each client in the client vector:
            a.) send_player_info()
            b.) send_tower_info()
            c.) send_creep_info()


send_player_info()
- Send all information pertaining to a particular player to the client
    1.) From the vector of players, locate and select player p such that p's id is
            equal to the requested player's id
    2.) If the player status has changed since the previous update:
            a.) Send the most up-to-date data pertaining to said player to the client
                controlled by said player


send_tower_info()
- Send all information pertaining to a particular tower to the client
    1.) From the vector of towers, locate and select tower t such that t's id is
            equal to the requested tower's id
    2.) If the tower's status has changed since the previous update:
            a.) Send the most up-to-date data pertaining to said tower to all
                clients within the client vector


send_creep_info()
- Send all information pertaining to a particular creep to the client
    1.) From the vector of creeps, locate and select creep c such that c's id is
            equal to the requested creep's id
    2.) If the creep's status has changed since the previous update:
            a.) Send the most up-to-date data pertaining to said tower to all
                clients within the client vector


send_packet()
???


receive_packet()
???


initialize_session()
- Initialize all data/structures necessary for a valid session
    1.) Ensure all players are in a connected state
    2.) Reset all resource's statis (players/towers/creeps)
    3.) Send a MSG_GAME_START packet to all clients, indicating start of game

