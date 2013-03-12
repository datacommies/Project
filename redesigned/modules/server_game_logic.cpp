    #include "server_game_logic.h"
     
    #include <stdio.h>
    #include <signal.h>
    #include <sys/time.h>
    #include <stdlib.h>
    #include <errno.h>
     
     
     
    void *UpdateThreadFunc(void *p)
    {
      ServerGameLogic *sgl = (ServerGameLogic *) p;
     
      for(;;)
        sgl->update();
     
      return NULL;
    }
     
     
    /* Constructor
     *
     * PRE:    
     * POST:    
     * RETURNS:
     * NOTES:   Creates a thread and starts running the module */
    ServerGameLogic::ServerGameLogic()
       : gameState_(LOBBY)
    {
     
      int result = pthread_create( &update_thread_, NULL, UpdateThreadFunc, (void*) this);
     
      if (result != 0)
        fprintf(stderr, "Error creating thread in %s line %d\n", __FILE__, __LINE__);
     
    }
     
    ServerGameLogic::~ServerGameLogic()
    {
     
     
    }
     
    /* Starts the game.
     *
     * PRE:     Game is in the lobby and players are ready.
     * POST:    Data structures and initialized and game is placed in an active state, with all appropriate modules processing.
     * RETURNS:
     * NOTES:    */
    void ServerGameLogic::startGame()
    {
      setAlarm();
    }
     
    /* Receive and queue a create unit command from a client.
     *
     * PRE:     Game is active.
     * POST:    Command has been queued.
     * RETURNS:
     * NOTES:   No validation is performed here. */
    void ServerGameLogic::receiveCreateUnitCommand(int playerId, UnitType type, Point location)
    {
      CommandData newCommand;
     
      newCommand.cmd = Create;
      newCommand.playerID = playerId;
      newCommand.type = type;
      newCommand.location = location;
     
      requestedCommands.push(newCommand);
    }
     
    /* Receive and queue a move player command from a client.
     *
     * PRE:     Game is active.
     * POST:    Command has been queued.
     * RETURNS:
     * NOTES:   No validation is performed here. */
    void ServerGameLogic::receiveMovePlayerCommand(int playerId, Direction direction)
    {
      CommandData newCommand;
     
      newCommand.cmd = MovePlayer;
      newCommand.playerID = playerId;
      newCommand.direction = direction;
     
      requestedCommands.push(newCommand);
    }
     
    void ServerGameLogic::receiveMoveUnitCommand(int unitId, Direction direction)
    {
        CommandData newCommand;

        newCommand.cmd = MoveUnit;
        newCommand.unitID = unitId;
        newCommand.direction = direction;

        requestedCommands.push(newCommand);
    }

    /* Receive and queue an attack command from a client.
     *
     * PRE:     Game is active.
     * POST:    Command has been queued.
     * RETURNS:
     * NOTES:   No validation is performed here. */
    void ServerGameLogic::receiveAttackCommand(int playerId, Direction direction)
    {
      CommandData newCommand;
     
      newCommand.cmd = Attack;
      newCommand.playerID = playerId;
      newCommand.direction = direction;
     
      requestedCommands.push(newCommand);
    }
     

    std::vector<Unit>::iterator findUnit(std::vector<Unit>::iterator first, std::vector<Unit>::iterator end, int playerID) {

        for (std::vector<Unit>::iterator it = first; first != end; ++it)
            if (it->id == playerID)
                return it; 

        return end;
    }

    
    void ServerGameLogic::updateCreate(CommandData& command)
    {
     
    }
     
    void ServerGameLogic::updateAttack(CommandData& command)
    {
     
    }
     
    void ServerGameLogic::updateMovePlayer(CommandData& command)
    {
     
    }
     
    void ServerGameLogic::updateMoveUnit(CommandData& command)
    {
     
    }

    /* Processes all waiting commands.
     *
     * PRE:    
     * POST:    Command queue is cleared.
     * RETURNS:
     * NOTES:   Perform validation here.
     *          Nice to have: send a fail message if command is invalid */
    void ServerGameLogic::update()
    {
      if (requestedCommands.empty())
        return;
     
      CommandData newCommand = requestedCommands.front();
      requestedCommands.pop();


     
      switch (newCommand.cmd) {
        case Create:
          updateCreate(newCommand);
          break;
        case Attack:
          updateAttack(newCommand);
          break;
        case MovePlayer:
          updateMovePlayer(newCommand);
          break;
        case MoveUnit:
          updateMoveUnit(newCommand);
          break;
      }
    }
     
    void ServerGameLogic::updateClients(int i)
    {
     
      signal(SIGALRM, updateClients);
     
      // Call network update function

      ServerGameLogic::setAlarm();
    }
     
    void ServerGameLogic::setAlarm()
    {
     
      struct itimerval tout_val;
      int result;
     
      tout_val.it_interval.tv_sec = 0;
      tout_val.it_interval.tv_usec = 0;
      tout_val.it_value.tv_sec = 0;
      tout_val.it_value.tv_usec = INTERVAL; /* set time for interval (1/30th of a second) */
      result = setitimer(ITIMER_REAL, &tout_val,0);
     
      if (result != 0)
        fprintf(stderr, "Error calling setitimer error %d in %s line %d\n", errno, __FILE__, __LINE__);
     
     
      signal(SIGALRM, updateClients); /* set the Alarm signal capture */
     
    }
     
     
    /*
     * To test this class use  g++ -DTESTCLASS -pthread -Wall server_game_logic.cpp
     */
    #ifdef TESTCLASS
    int main() {
     
      ServerGameLogic game;
     
      game.startGame();
     
      while (1)
        ;
     
    }
    #endif

