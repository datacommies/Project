Pseudocode for public setters version 1
======




Partial Type Definitions
======
Game logic group needs to provide official definitions.

player_t {
    id
    position
	health
}

resource_t {
    team
    restype
	value
}

creep_t {
    id
	team
	archetype
	health
	position
}

tower_t {
    id
	archetype
	position
	health
}




Public Setter Methods
======

update_player_info(player_t player)
------
Allows clients to update player info on central server.
1. from array of connected players, find a player X that has (X.id == player.id)
    2. if found, copy values of each attribute of player.* to X.*
    3. if not found, return error ("given player id not found")
4. return 0 ("success")

update_tower_info(tower_t twr)
------
Allows clients to update tower info on central server.
1. from array of towers, find a tower X that has (X.id == twr.id)
    2. if found, copy values of each attribute of twr.* to X.*
    3. if not found, return error ("given tower id not found")
4. return 0 ("success")

update_creep_info(creep_t creep)
------
Allows clients to update creep info on central server.
1. from array of creeps, find a creep X that has (X.id == creep.id)
    2. if found, copy values of each attribute of creep.* to X.*
    3. if not found, return error ("given creep id not found")
4. return 0 ("success")

update_resources(resource_t restype)
------
Allows clients to update team resource info on central server.
Note: Unsure about the typedef of resource_t on this one.
1. from array of resources, find a resource X that has (resource.team == X.team)
    2. if found, copy values of each attribute of resource.* to X.*
    3. if not found, return error ("given team resource not found")
4. return 0 ("success")

remove_player(player_t player)
------
Remove a player from connected player from client list.
Note: Unsure about this one. Another function must be called to inform clients of missing player along with other cleanup functions.
1. from array of connected players, find a player X that has (X.id == player.id)
    2. if found, remove X from array
    3. if not found, return error ("given player id not found")
4. return 0 ("success")
