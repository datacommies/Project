###Changes
I changed the arguments based on the partial type definitions on `setters.md`.

`get_player_info(player_t.id playerid)`
- Looks up the player id specified by `playerid` in the server and
returns the player struct associated with it.

    `return player_t struct`

get_tower_info(tower_t.id twrid)
- Looks up the tower id specified by `twrid` in the server and
returns the tower struct associated with it.

    `return tower_t`

get_creep_info(creep_t.id creepid)
- Looks up the creep id specified by `creepid` in the server and
returns the creep struct associated with it.

    `return creep_t`

get_resources()
- Returns a resource struct which is the server's tally of the current game resources

    `return resource_t`
