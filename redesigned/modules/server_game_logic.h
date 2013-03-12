    #ifndef SERVERGAMELOGIC_H
    #define SERVERGAMELOGIC_H
     
     
    #define INTERVAL 33333
     
    #include <stdio.h>
    #include <stdlib.h>
    #include <pthread.h>
     
    #include "../resource.h"
     
    #include <string>
    #include <queue>
    #include "../team.h"
     
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
       GameState gameState_;
       pthread_t update_thread_;
     
     
       // Functions
       void update();
       void updateCreate(CommandData& command);
       void updateAttack(CommandData& command);
       void updateMovePlayer(CommandData& command);
       void updateMoveUnit(CommandData& command);
     
       static void setAlarm();
       static void updateClients(int i);

       // teams, players, creeps, etc..
       std::vector<Unit>::iterator findUnit(std::vector<Unit>::iterator first, std::vector<Unit>::iterator end, int playerID);
    };
     
    #endif

