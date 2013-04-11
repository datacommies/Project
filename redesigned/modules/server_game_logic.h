#ifndef SERVERGAMELOGIC_H
#define SERVERGAMELOGIC_H

#define INTERVAL 33333

#define INIT_NUM_CREEPS 1
#define INIT_NUM_TOWERS 4
#define INIT_CURRENCY 500
#define INIT_HEALTH 100

#define INIT_CASTLE_HP 100
#define INIT_CASTLE_ATKDMG 5
#define INIT_CASTLE_ATKRNG 7
#define INIT_CASTLE_ATKSPD 1
#define INIT_CASTLE_PERCEP 10
#define INIT_CASTLE_ATKCNT 1
#define INIT_CASTLE_WALL 2

#define INIT_CREEP_HP 100
#define INIT_CREEP_ATKDMG 5
#define INIT_CREEP_ATKRNG 7
#define INIT_CREEP_ATKSPD 20
#define INIT_CREEP_PERCEP 30
#define INIT_CREEP_ATKCNT 1
#define INIT_CREEP_SPD 2
#define INIT_CREEP_MOVESPEED 1
#define CREEP_COST 10

#define INIT_TOWER_HP 100
#define INIT_TOWER_ATKDMG 7
#define INIT_TOWER_ATKRNG 75
#define INIT_TOWER_ATKSPD 20
#define INIT_TOWER_PERCEP 150
#define INIT_TOWER_ATKCNT 1
#define INIT_TOWER_WALL 2 
#define TOWER_COST 100

#define PATH_COUNT 3

#define PLAYER_KILL_BONUS 100
#define CREEP_KILL_BONUS 10
#define TOWER_KILL_BONUS 50

#define CREEP_COOLDOWN 20

// This will come actually be read from the map
#ifndef TESTCLASS
#define MAX_X 800
#define MAX_Y 600
#else
#define MAX_X 20 
#define MAX_Y 20
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
#include "../units/basic_tower.h"
#include "audio.h"
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

class GameMap;

class ServerGameLogic
{
  public:
    // Constructors
    ServerGameLogic();
    ~ServerGameLogic();

    pthread_mutex_t unit_mutex;

    // Fields
    Team teams[2];
    GameState gameState_;

    std::queue<CommandData> requestedCommands;

    // Functions
    void startGame();
    void receiveCreateUnitCommand(int playerId, UnitType type, Point location, int pathId);
    void receiveMovePlayerCommand(int playerId, Direction direction);
    void receiveMoveUnitCommand(int unitId, Direction direction);
    void receiveAttackCommand(int playerId, Direction direction);
    void playerConnect();
    int getWinner();
    void initializeTeams(std::vector<player_matchmaking_t> players);
    int getPlayerRole(int teamNumber, int playerID);
    void handleDeaths();

    Point FindCreepSpawnPoint(int team_no, int pathID);

  private:
    // Fields
    
    int next_unit_id_;
    //Ai ai_;
    GameMap *gameMap_;

    // The time a creep was created last for each team respectively.
    time_t lastCreepTime_[2];
    
    GameLogicMap mapTeams_[2]; 
    GameLogicMap mapBoth_;

    // Functions
    void update();
    void updateCreate(CommandData& command);
    void updateAttack(CommandData& command);
    void updateMovePlayer(CommandData& command);
    void updateMovement(int, int);
    void updateMoveUnit(CommandData& command);

    // Initializing the Game functions
    void initializeCastles();
    void initializeCreeps();
    void initializeTowers();
    void initializeCurrency();
    void initializePaths();
    void initializePlayers(std::vector<player_matchmaking_t> players);
    
    void createCreep(int team_no, Point location, int path_no = 0, UnitType unitType =  CREEP);
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

    void updateMaps();
    Audio audio_;
};

#endif
