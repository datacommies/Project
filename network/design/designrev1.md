Revision 1
===========

Send everything by TCP

Private methods:
-----------------

sync_all_clients()
- big update, makes sure that all clients have data they need
- get all the current clients (clients_vector)
- for each client in clients_vector:
	- send player_info
	- send tower_info
	- send creep_info

send_packet()
receive_packet()
initialize_session()

Public methods:
-------------

Getter:
- get_player_info(player_t player)
	- return player_t struct
- get_tower_info(tower_t twr)
- get_creep_info(creep_t creep)
- get_resources(resource_t res)

settter:
- update_player_info(player_t player)
	- info: position, health,
- update_tower_info(tower_t twr)
- update_creep_info(creep_t creep)
- update_resources(resource_t restype)
- remove_player(player_t player)


Revision 2
==========

Send everything by TCP

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

Private methods:
-----------------

sync_all_clients()
- big update, makes sure that all clients have data they need
- get all the current clients (clients_vector)
- for each client in clients_vector:
	- send player_info
	- send tower_info
	- send creep_info

send_packet()
receive_packet()
initialize_session()

Public methods:
-------------

Getter:
- get_player_info(player_t.id player)
	- return player_t struct
- get_tower_info(tower_t.id twr)
    -return tower_t
- get_creep_info(creep_t.id creep)
    - return creep_t
- get_resources()
    - return resource_t

settter:
- update_player_info(player_t player)
	- info: position, health,
- update_tower_info(tower_t twr)
- update_creep_info(creep_t creep)
- update_resources(resource_t restype)
- remove_player(player_t player)
