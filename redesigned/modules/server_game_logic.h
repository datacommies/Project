#ifndef SERVERGAMELOGIC_H
#define SERVERGAMELOGIC_H

#define INTERVAL 33333

#define INIT_NUM_CREEPS 3
#define INIT_NUM_TOWERS 4
#define INIT_CURRENCY 500
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
#define CREEP_COST 10

#define INIT_TOWER_HP 200
#define INIT_TOWER_ATKDMG 7
#define INIT_TOWER_ATKRNG 11
#define INIT_TOWER_ATKSPD 2
#define INIT_TOWER_PERCEP 23
#define INIT_TOWER_ATKCNT 1
#define INIT_TOWER_WALL 2 
#define TOWER_COST 100

#define PATH_COUNT 1

#define PLAYER_KILL_BONUS 100
#define CREEP_KILL_BONUS 10
#define TOWER_KILL_BONUS 50

// This will come actually be read from the map
#ifndef TESTCLASS
#define MAX_X 700
#define MAX_Y 500
#else
#define MAX_X 20 
#define MAX_Y 20
#endif

#include <stdio.h>
#include <stdlib.h>
//#include <pthread.h>

#include "../resource.h"

#include <string>
#include <queue>
#include <map>
#include "../team.h"
#include "../units/unit.h"
#include "../units/GameMap.h"
//#include "ai.h"
#include "../types.h"
#include "../units/castle.h"

#include "game_logic_map.h"

enum Command { Create, MovePlayer, MoveUnit, Attack };

struct CommandData {
  Command cmd;
  int playerID;
  int unitID;
  UnitType type;
  Point location;
  Direction direction;
  int pathID;
};

class ServerGameLogic
{
  public:
    // Constructors
    ServerGameLogic();
    ~ServerGameLogic();

    // Fields
    Team teams[2];
    GameState gameState_;

    std::queue<CommandData> requestedCommands;

    // Functions
    void startGame();
    void receiveCreateUnitCommand(int playerId, UnitType type, Point location, int pathId = 0);
    void receiveMovePlayerCommand(int playerId, Direction direction);
    void receiveMoveUnitCommand(int unitId, Direction direction);
    void receiveAttackCommand(int playerId, Direction direction);
    void playerConnect();
    int getWinner();
    void initializeTeams(std::vector<player_matchmaking_t> players);
    int getPlayerRole(int teamNumber, int playerID);
    void handleDeaths();

  private:
    // Fields
    
    int next_unit_id_;
    //Ai ai_;
    GameMap *gameMap_;

 
    
    GameLogicMap mapTeams_[2]; 
    GameLogicMap mapBoth_;

    // Functions
    void update();
    void updateCreate(CommandData& command);
    void updateAttack(CommandData& command);
    void updateMovePlayer(CommandData& command);
    void updateMoveUnit(CommandData& command);   

    // Initializing the Game functions    
    void initializeCastles();
    void initializeCreeps();
    void initializeTowers();
    void initializeCurrency();
    void initializePaths();
    void initializePlayers(std::vector<player_matchmaking_t> players);
    
    void createCreep(int team_no, Point location, int path_no = 0);
    void createTower(int team_no, Point location);
    void createPlayer(int team_no, Point location, int client_id, int role);
    void respawnPlayer(Player* player, Point location);
    static void setAlarm();
    static void updateTimer(int i);
    
    int WhichTeam(int id);

    void giveTeamBonus(int team_no, int amount);    
    void handlePlayerDeath(Player *player);
    void handleCreepDeath(Creep *creep);
    void handleTowerDeath(Tower *tower);
    void handleCastleDeath();
};

#endif
