#include "../resource.h"
#include "Point.h"

class GameMap{
public:
    Point castle1; //position for team 0's castle
    Point castle2; //position for team 0's castle
    PATH topOne, midOne, botOne; //paths for team 0's creeps
    PATH topTwo, midTwo, botTwo; //paths for team 1's creeps
    Point team0start[4]; //starting positions for team 0's players
    Point team1start[4]; //starting positions for team 1's players
    //add the 2d array
    

    //initializes castle positions and paths for each team
    //these still need to be assigned to a team object somehow
    //should probably be changed to use the MAPWIDTH/MAPHEIGHT defines
    //do we want default player spawn positions?
    void initMap();

};