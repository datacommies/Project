#ifndef SERVERGAMELOGIC_H
#define SERVERGAMELOGIC_H
 
#define INTERVAL 33333

#define INIT_NUM_CREEPS 3
#define INIT_TOWERS_START 4
#define INIT_CURRENCY 100
#define INIT_HEALTH 100

#define INIT_CREEP_HP 100
#define INIT_CREEP_ATKDMG 5
#define INIT_CREEP_ATKRNG 7
#define INIT_CREEP_ATKSPD 1
#define INIT_CREEP_PERCEP 1
#define INIT_CREEP_ATKCNT 1
#define INIT_CREEP_SPD 1
#define INIT_MOVESPEED 1
 
// This will come actually be read from the map
#define MAX_X 100
#define MAX_Y 100

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 

#include "../resource.h"
//#include "ai.h"    

#include <string>
#include <queue>
#include "../team.h"
 
enum Command { Create, MovePlayer, MoveUnit, Attack };
 
/* Until Ai is available/fixed */
class MyAi {
    public: 
        void update(Team &team1, Team &team2) {}
};
 
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
 
  friend void *UpdateThreadFunc(void *p);
 
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
   static MyAi ai_;
   GameState gameState_;
   pthread_t update_thread_;
   int next_unit_id_;
 
   // Functions
   void update();
   void updateCreate(CommandData& command);
   void updateAttack(CommandData& command);
   void updateMovePlayer(CommandData& command);
   void updateMoveUnit(CommandData& command);
 
   void startThread();
   
   
   // Initializing the Game functions
   void initializeTeams();
   void initializeCastles();
   void initializeCreeps();
   void initializeTowers();
   
   static void setAlarm();
   static void updateClients(int i);

   // teams, players, creeps, etc..
   std::vector<Unit>::iterator findUnit(std::vector<Unit>::iterator first, std::vector<Unit>::iterator end, int playerID);
};
 
#endif

