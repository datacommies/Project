#ifndef SERVERGAMELOGIC_H
#define SERVERGAMELOGIC_H

#define INTERVAL 33333

#define INIT_NUM_CREEPS 3
#define INIT_TOWERS_START 4
#define INIT_NUM_TOWERS 4
#define INIT_CURRENCY 100
#define INIT_HEALTH 100

#define INIT_CASTLE_HP 100
#define INIT_CASTLE_ATKDMG 5
#define INIT_CASTLE_ATKRNG 7
#define INIT_CASTLE_ATKSPD 1
#define INIT_CASTLE_PERCEP 1
#define INIT_CASTLE_ATKCNT 1
#define INIT_CASTLE_WALL 2

#define INIT_CREEP_HP 100
#define INIT_CREEP_ATKDMG 5
#define INIT_CREEP_ATKRNG 7
#define INIT_CREEP_ATKSPD 1
#define INIT_CREEP_PERCEP 1
#define INIT_CREEP_ATKCNT 1
#define INIT_CREEP_SPD 1
#define INIT_CREEP_MOVESPEED 1

#define INIT_TOWER_HP 200
#define INIT_TOWER_ATKDMG 7
#define INIT_TOWER_ATKRNG 11
#define INIT_TOWER_ATKSPD 2
#define INIT_TOWER_PERCEP 23
#define INIT_TOWER_ATKCNT 1
#define INIT_TOWER_WALL 2 

// This will come actually be read from the map
#define MAX_X 500
#define MAX_Y 500

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../resource.h"

#include <string>
#include <queue>
#include <map>
#include "../team.h"
#include "../units/unit.h"
//#include "ai.h"

enum Command { Create, MovePlayer, MoveUnit, Attack };

struct CommandData {
  Command cmd;
  int playerID;
  int unitID;
  UnitType type;
  Point location;
  Direction direction;
};

class ServerGameLogic
{

  public:
    // Constructors
    ServerGameLogic();

    ~ServerGameLogic();

    // Fields
    Team teams[2];

    std::queue<CommandData> requestedCommands;

    // Functions
    void startGame();
    void receiveCreateUnitCommand(int playerId, UnitType type, Point location);
    void receiveMovePlayerCommand(int playerId, Direction direction);
    void receiveMoveUnitCommand(int unitId, Direction direction);
    void receiveAttackCommand(int playerId, Direction direction);
    void playerConnect();

  private:
    // Fields
    GameState gameState_;
    int next_unit_id_;
    //Ai ai_;

    struct Location {
      Point pos;
      UnitType type;
    };

    struct GameLogicMap {

      int max_x_;
      int max_y_;

      // Create a two dimensional grid player_ids .. 0 means the a position is empty
      int **grid_; 

      // Store locatation for each player_id
      std::map<int, Location> units_;


      void init() {

        grid_ = (int**) Malloc(sizeof(int*) * max_x_ + 1);

        for ( int x=0; x <= max_x_; x++) {
          grid_[x] = (int*) Malloc(sizeof(int) * max_y_ + 1);
          memset(grid_[x], 0, sizeof(int) * max_y_ + 1);
        }
      }

      GameLogicMap(int max_x = MAX_X, int max_y = MAX_Y): max_x_(max_x), max_y_(max_y) {
        init();
      }

      int min(int a, int b) 
      {
        return a < b ? a : b;
      }

      int max(int a, int b) 
      {
        return a > b ? a : b;
      }

      /*
       * This merges two maps together. eg, both = GameLogicMap(map1, map2);
       */
      GameLogicMap(GameLogicMap& map1, GameLogicMap& map2)
        : max_x_(max(map1.max_x_, map2.max_x_)), max_y_(max(map1.max_y_, map2.max_y_))
      {
        init();
        merge(map1, map2);
      }

      void merge(GameLogicMap& map1, GameLogicMap& map2)
      {

        reset ();
        int x, y;

        // Okay, yes, I know, in this game, both maps will be the same size....
        int min_x = min(map1.max_x_, map2.max_x_);
        int min_y = min(map1.max_y_, map2.max_y_);

        // add units_s together ...
        for(std::map<int, Location>::const_iterator it = map1.units_.begin(), it_end = map1.units_.end(); it != it_end; ++it)
          units_.insert(*it);
        for(std::map<int, Location>::const_iterator it = map2.units_.begin(), it_end = map2.units_.end(); it != it_end; ++it)
          units_.insert(*it);

        // add grid_s together
        for (x=0; x<=min_x; x++)
          for (y=0; y<=min_y; y++) {

            if (map1.grid_[x][y] != 0 && map2.grid_[x][y] != 0) {
              fprintf(stderr, "!!!Error..more than one object occuping the same space!!! %s line: %d\n", __FILE__, __LINE__);
            }

            // One of the values will be zero..so adding the two positions is an easy little trick..
            grid_[x][y] = map1.grid_[x][y] + map2.grid_[x][y];
          }
      }

      // I write this so that I might be able to see if things work correctly
      void printGrid() {

        int x, y;
        for (x=0; x<max_x_; x++) {
          for (y=0; y<max_y_; y++)
            printf("%d ", grid_[x][y]);
          printf("\n");
        }
      }

      ~GameLogicMap() {

        for (int x=0; x<= max_x_; x++)
          free (grid_[x]);

        free(grid_);
      }

      bool isValidPos(Point pos)
      {
        return (pos.x >= 0 && pos.x <= max_x_) && (pos.y >= 0 && pos.y <= max_y_);
      }

      void _helperBuild(int id, UnitType type, Point pos) {

        if (!isValidPos(pos)) {
          fprintf(stderr, "Invalid position x: %d y: %d %s line %d\n", pos.x, pos.y, __FILE__, __LINE__);
          return;
        }        

        Location location; 

        location.type = type;
        location.pos = pos;
        units_[id] = location;
        grid_[location.pos.x][location.pos.y] = id;
      }

      // This builds everything based on the Team class
      void build(Team &team) {

        reset();

        for (std::vector<Creep>::iterator it = team.creeps.begin(); it != team.creeps.end(); ++it)
          _helperBuild((int) it->id, CREEP, it->getPos());

        for (std::vector<Tower>::iterator it = team.towers.begin(); it != team.towers.end(); ++it) {
          _helperBuild((int) it->id, TOWER, it->getPos());
        }

        for (std::vector<Player>::iterator it = team.players.begin(); it != team.players.end(); ++it) {
          _helperBuild((int) it->id, PLAYER, it->getPos());
        }
      }

      void reset() {
        // Zero memory
        for (int x=0; x<=max_x_; x++)
          memset(grid_[x], 0, sizeof(int) * max_y_ + 1);

        units_.clear();
      } 

      void * Malloc(size_t size) {

        void * p;

        p = malloc(size);

        if (p == NULL)
          fprintf(stderr, "Error calling malloc in %s line %d\n", __FILE__, __LINE__);

        return p;
      }
    }; 
    
    GameLogicMap mapTeams_[2]; 
    GameLogicMap mapBoth_;

    // Functions
    void update();
    void updateCreate(CommandData& command);
    void updateAttack(CommandData& command);
    void updateMovePlayer(CommandData& command);
    void updateMoveUnit(CommandData& command);   

    // Initializing the Game functions
    void initializeTeams();
    void initializeCastles();
    void initializeCreeps();
    void initializeTowers();

    static void setAlarm();
    static void updateClients(int i);

    // teams, players, creeps, etc..
    std::vector<Unit>::iterator findUnit(std::vector<Unit>::iterator first, std::vector<Unit>::iterator end, int playerID);

    int WhichTeam(int id);
};

#endif

