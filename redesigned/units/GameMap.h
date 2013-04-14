#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "Point.h"
#include "../modules/server_game_logic.h"
#include <stdio.h>
#include <stdlib.h> 
#include "../resource.h"
#include <string>
#include <queue>        
#include <map>          
#include "../team.h"
#include "../units/unit.h"
#include <vector>

//forward declaration for using a pointer
class GameMap;

#define TEAM_NOT_FOUND 2

//map size
#define MAP_X 800
#define MAP_Y 600

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
    void initPaths();
    void initPlayerPositions();
    void initCastlePositions();
    GameMap (int max_x=MAX_X, int max_y=MAX_Y);
    ~GameMap();
    
    Unit *getUnit(Point pos);

    Unit *getUnitFromId(int id);
    int getTeamNo(int id);

    // This builds everything based on the Team class
    void build(Team teams[]);

    void addUnit(Unit *unit, Point pos);
    void removeUnit(Unit *unit);
    void moveUnit(Unit *unit, Point new_pos);

    void printGrid();
    bool isValidPos(Point pos);

    //void build(Team &team);
    //GameMap(GameMap& map1, GameMap& map2);
    //void merge(GameMap& map1, GameMap& map2);
  private:

    int max_x_;
    int max_y_;

    // Go from position to unit*
    Unit ***grid_;

    // Go from unit id to postion
    std::map<int, Point> units_;

    // Methods

    void _init();

    int min(int a, int b);
    int max(int a, int b);

    // I write this so that I might be able to see if things work correctly

    void _helperBuild(Unit *unit, UnitType type, Point pos, int team_no);

    void reset();

    void * Malloc(size_t size);
}; 

#endif
