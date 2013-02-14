sync_all_clients()
- big update, makes sure that all clients have data they need
	1. get all the current clients (clients_vector)
	2. for each client in clients_vector:
		send_player_info()
		send_tower_info()
		send_creep_info()

send_player_info()
	1. from the container containing all of the players, find player p that has (p.id == player.id)
	2.if the player status has changed since the last send then:
		-send the most up to date data of that player to the client controlled by that player
	
send_tower_info()
	1. from the container containing all of the towers, find tower t that has(t.id == tower.id)
	2.if the tower status has changed since the last send then:
	 	-send the most up to date  data of that tower to all clients in the clients container
	 	
send_creep_info()
	1. from the container containing all of the creeps, find creep c that has(c.id == creep.id)
	2.if the tower status has changed since the last send then:
	 	-send the most up to date  data of that creep to all clients in the clients container
	
send_packet() 
//not sure what this does, does it simply make a TCP packet and send it?
	
receive_packet()
//same as above

initialize_session()
	1. ensure that all of the players are connected
	2. zero out all the resource/player/tower stats
	3. send a packet to all clients to indicate the start of game
	