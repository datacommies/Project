/*------------------------------------------------------------------------------
-- FILE:        server_game_logic.cpp
--
-- DATE:        2013/03/11
--
-- MAINTAINERS: Callum Styan, David Czech, Dennis Ho,
--              Jesse Wright, Behnam Bastami
--
-- FUNCTIONS:
--              
------------------------------------------------------------------------------*/

#include "server_game_logic.h"
#include "../units/basic_tower.h"
#include "../units/castle.h"
#include "../units/AiController.h"
#include "../units/player.h"
#include "../units/electro_tower.h"
#include "../units/splash_tower.h"
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>
#include <errno.h>
#include <new>
#include <cmath>

#define NOT_FOUND 2

#define PLAYER_WIDTH 25
#define PLAYER_HEIGHT 25

ServerGameLogic * gSGL;

/*------------------------------------------------------------------------------
-- FUNCTION:   ServerGameLogic()
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Callum Styan
-- PROGRAMMER: Callum Styan, Dennis Ho
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: ServerGameLogic constructor.  Initializes the game map and creep
-- paths, as well as the time for creation of creeps.
------------------------------------------------------------------------------*/
  ServerGameLogic::ServerGameLogic()
: gameState_(LOBBY), next_unit_id_(1)
{

  pthread_mutex_init(&unit_mutex, NULL);

  gameMap_ = new GameMap();
  gameMap_->initMap();

  teams[0].paths.push_back(gameMap_->topOne);
  teams[0].paths.push_back(gameMap_->midOne);
  teams[0].paths.push_back(gameMap_->botOne);

  teams[1].paths.push_back(gameMap_->topTwo);
  teams[1].paths.push_back(gameMap_->midTwo);
  teams[1].paths.push_back(gameMap_->botTwo);

  lastCreepTime_[0] = time(NULL);
  lastCreepTime_[1] = time(NULL);
}   

ServerGameLogic::~ServerGameLogic()
{
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   David Czech, Behnam Bastami 
-- PROGRAMMER: David Czech, Behnam Bastami
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
int ServerGameLogic::getWinner()
{
  if(teams[0].isAlive() && !teams[1].isAlive())
  {
    return 0;
  }
  else if(teams[1].isAlive() && !teams[0].isAlive())
  {
    return 1;
  }

  return 2;
}
/*------------------------------------------------------------------------------
-- FUNCTION:   initializeCastles
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Darry Danzig, Callum Styan
-- PROGRAMMER: Darry Danzig, Callum Styan, Dennis Ho
--
-- INTERFACE:   
--
-- RETURNS:     void
--
-- DESCRIPTION: creates each teams castle and it's predefined position
------------------------------------------------------------------------------*/
void ServerGameLogic::initializeCastles() 
{

  int uid = next_unit_id_++;


  // Team 0
  Castle *castle1 = new Castle(uid, gameMap_->castle1, INIT_CASTLE_HP, INIT_CASTLE_ATKDMG, INIT_CASTLE_ATKRNG, INIT_CASTLE_ATKSPD,
      INIT_CASTLE_PERCEP, INIT_CASTLE_ATKCNT, INIT_CASTLE_WALL, 0);
  teams[0].towers.push_back(castle1);
  teams[0].units.push_back(castle1);

  Point p = castle1->getPos();
  printf("Castle 1 position..x: %d y: %d\n", p.x, p.y);
  
  // Team 1
  uid = next_unit_id_++;
  Castle *castle2 = new Castle(uid, gameMap_->castle2, INIT_CASTLE_HP, INIT_CASTLE_ATKDMG, INIT_CASTLE_ATKRNG, INIT_CASTLE_ATKSPD,
      INIT_CASTLE_PERCEP, INIT_CASTLE_ATKCNT, INIT_CASTLE_WALL, 1);
  teams[1].towers.push_back(castle2);
  teams[1].units.push_back(castle2);

}
/*------------------------------------------------------------------------------
-- FUNCTION:   initializeCreeps
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Darry Danzig, Callum Styan
-- PROGRAMMER: Darry Danzig, Callum Styan
--
-- INTERFACE:   
--
-- RETURNS:     void
--
-- DESCRIPTION: initializes creeps to spawn at the start of the game
------------------------------------------------------------------------------*/
void ServerGameLogic::initializeCreeps()
{
  for (int team_i=0; team_i<2; team_i++){
    for (int j=0; j<INIT_NUM_CREEPS; j++) {
      Point pos = Point();
      
      if (team_i == 0) {
        pos.x = 1 + INIT_NUM_TOWERS + j;
        pos.y = 1;
      }
      else {
        pos.x = MAX_X - INIT_NUM_TOWERS - j - 1;
        pos.y = MAX_Y - 1;
      }

      createCreep(team_i, pos, j % PATH_COUNT);
    }
  }
}
/*------------------------------------------------------------------------------
-- FUNCTION:   initializeTowers
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Darry Danzig, Callum Styan
-- PROGRAMMER: Darry Danzig, Callum Styan
--
-- INTERFACE:   
--
-- RETURNS:     void
--
-- DESCRIPTION: initializes towers to spawn at the start of the game
------------------------------------------------------------------------------*/
void ServerGameLogic::initializeTowers()
{
  for (int team_i=0; team_i<2; team_i++)
    for (int j=0; j<INIT_NUM_TOWERS; j++) {
      Point pos = Point();

      if (team_i == 0) {
        pos.x = 1 + j;
        pos.y = 2;
      }
      else {
        pos.x = MAX_X -j;
        pos.y = MAX_Y - 2;
      }

      //createTower(team_i, pos);
    }
}

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Behnam Bastami
-- PROGRAMMER: Behnam Bastami
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void ServerGameLogic::initializeCurrency()
{
  for (int team_i=0; team_i<2; team_i++)
    teams[team_i].currency = INIT_CURRENCY;
}
/*------------------------------------------------------------------------------
-- FUNCTION:   initializePlayers(std::vector<player_matchmaking_t> players)
--
-- DATE:        2013/04/06
--
-- DESIGNER:   Jesse Wright
-- PROGRAMMER: Dennis Ho
--
-- INTERFACE:   void initializePlayers(std::vector<player_matchmaking_t> players)
--
-- RETURNS:     void.
--
-- DESCRIPTION: Creates all the player objects from all the clients in the 
-- matchmaking lobby.
------------------------------------------------------------------------------*/
void ServerGameLogic::initializePlayers(std::vector<player_matchmaking_t> players)
{
  for (std::vector<player_matchmaking_t>::iterator it = players.begin(); it != players.end(); ++it) {
    createPlayer(it->team, it->team == 0 ? gameMap_->team0start[0] : gameMap_->team1start[0], it->pid, it->role);
  }
}

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Dennis Ho
-- PROGRAMMER: Dennis Ho
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void ServerGameLogic::initializeTeams(std::vector<player_matchmaking_t> players)
{
  initializeCastles();
  initializeCreeps();
  initializeTowers();
  initializeCurrency();
  initializePlayers(players);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void ServerGameLogic::startGame()
{
  gSGL = this;
  setAlarm();
}

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void ServerGameLogic::receiveCreateUnitCommand(int playerId, UnitType type, Point location, int pathId)
{
  CommandData newCommand;
  
  newCommand.cmd = Create;
  newCommand.playerID = playerId;
  newCommand.type = type;
  newCommand.location = location;
  newCommand.pathID = pathId;

  requestedCommands.push(newCommand);
}
/*------------------------------------------------------------------------------
-- FUNCTION:   FindCreepSpawnPoint
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Jesse Wright
-- PROGRAMMER: Jesse Wright
--
-- INTERFACE:   Point FindCreepSpawnPoint(int team_no, int pathID)
--
-- RETURNS:     Point - the location where the creep will spawn.
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
Point ServerGameLogic::FindCreepSpawnPoint(int team_no, int pathID)
{
  Point creepSpawnLocation;
  if(team_no == 2) // team 2
  {
    if(pathID == HIGHPATH)
    {
      creepSpawnLocation.x = gameMap_->topOne[0].x;
      creepSpawnLocation.y = gameMap_->topOne[0].y;
    }else if(pathID == MIDPATH)
    {
      creepSpawnLocation.x = gameMap_->midOne[0].x;
      creepSpawnLocation.y = gameMap_->midOne[0].y;
    }else
    {
      creepSpawnLocation.x = gameMap_->botOne[0].x;
      creepSpawnLocation.y = gameMap_->botOne[0].y;
    }
  } else if(team_no == 1)// team 2
  {
    if(pathID == HIGHPATH)
    {
      creepSpawnLocation.x = gameMap_->topTwo[0].x;
      creepSpawnLocation.y = gameMap_->topTwo[0].y;
    }else if(pathID == MIDPATH)
    {
      creepSpawnLocation.x = gameMap_->midTwo[0].x;
      creepSpawnLocation.y = gameMap_->midTwo[0].y;
    }else
    {
      creepSpawnLocation.x = gameMap_->botTwo[0].x;
      creepSpawnLocation.y = gameMap_->botTwo[0].y;
    }
  }
  return creepSpawnLocation;
}

/*------------------------------------------------------------------------------
-- FUNCTION:   receiveMovePlayerCommand
--
-- DATE:        2013/04/06
--
-- DESIGNER:   Jesse Wright
-- PROGRAMMER: Jesse Wright
--
-- INTERFACE:   void receiveMovePlayerCommand(int playerId, Direction direction)
--
-- RETURNS:    void.
--
-- DESCRIPTION: Sets command parameters but takes the player ID. Same as move unit
-- but is used for readability by calling this for a Player.
------------------------------------------------------------------------------*/
void ServerGameLogic::receiveMovePlayerCommand(int playerId, Direction direction)
{
  CommandData newCommand;

  newCommand.cmd = MovePlayer;
  newCommand.playerID = playerId;
  newCommand.direction = direction;
  newCommand.unitID = playerId;

  requestedCommands.push(newCommand);
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Dennis Ho, Behnam Bastami, 
-- PROGRAMMER: Dennis Ho
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void ServerGameLogic::receiveMoveUnitCommand(int unitId, Direction direction)
{
  CommandData newCommand;

  newCommand.cmd = MoveUnit;
  newCommand.unitID = unitId;
  newCommand.direction = direction;

  requestedCommands.push(newCommand);
}

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Dennis Ho, Behnam Bastami
-- PROGRAMMER: Dennis Ho
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void ServerGameLogic::receiveAttackCommand(int playerId, Direction direction)
{
  CommandData newCommand;

  newCommand.cmd = Attack;
  newCommand.playerID = playerId;
  newCommand.direction = direction;

  requestedCommands.push(newCommand);
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Albert Liao, Darry Danzig
-- PROGRAMMER: Albert Liao, Darry Danzig
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
int ServerGameLogic::WhichTeam(int id) {

  updateMaps();

  for (std::vector<Player*>::iterator it = teams[0].players.begin(); it != teams[0].players.end(); ++it)
  {
    if((*it)->clientID == id)
    {
      return 0;
    }
  }

  for (std::vector<Player*>::iterator it = teams[1].players.begin(); it != teams[1].players.end(); ++it)
  {
    if((*it)->clientID == id)
    {
      return 1;
    }
  }

  return -1;
}

/*------------------------------------------------------------------------------
-- FUNCTION:   updateCreate
--
-- DATE:        2013/04/07
--
-- DESIGNER:   Jesse Wright, Callum Styan, Albert Liao
-- PROGRAMMER: Jesse Wright,  Callum Styan, Darry Danzig, Albert Liao
--
-- INTERFACE:   void updateCreate(CommandData& command)
--
-- RETURNS:     
--
-- DESCRIPTION: Requests to create units, checkes the teams and the state of 
-- the game.
------------------------------------------------------------------------------*/
void ServerGameLogic::updateCreate(CommandData& command)
{
  // Passed in command: PlayerId, type, location

  int team_no;
  int x = 100;
  int y = 100;

  if ( !(teams[0].isAlive() && teams[1].isAlive()) ) {
    gameState_ = WON_GAME;
    return;
  }

  if ( ( (team_no = WhichTeam(command.playerID)) == NOT_FOUND) ) {
    return;
  }

  // If we aren't a role 0 or alive don't allow a build
  if(getPlayerRole(team_no, command.playerID) != 0 || !getPlayerIsAlive(team_no, command.playerID))
  {
    return;
  }

  updateMaps();
  if (!mapTeams_[0].isValidPos(command.location)) {
    return; 
  }

  if ( mapBoth_.grid_[x][y] != 0 ){
    std::cout << "x: " << x << " y: " << y << std::endl; 
    return; // position is already occupied 
  }
  // Create Unit  
  switch (command.type) {
    case CREEP:
    case CREEP_ONE:
    case CREEP_TWO:
    case CREEP_THREE:
    {
        // Check if 1 seconds has elapsed since the last creep creation for the team.
      if(time(NULL) - lastCreepTime_[team_no] >= 1)
      {
        createCreep(team_no, command.location, command.pathID, command.type);
        lastCreepTime_[team_no] = time(NULL);
      }
      break;

    }

    case CASTLE:
    case TOWER:
    case TOWER_ONE:
    case TOWER_TWO:
    case TOWER_THREE:
      { 
        createTower(team_no, command.location, command.type);  
        break;
      }
    default:
      fprintf(stderr, "Unknown type %s line:%d\n", __FILE__, __LINE__);
      return;
  }

  mapTeams_[0].build(teams[0]);
  mapTeams_[1].build(teams[1]);
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void ServerGameLogic::updateAttack(CommandData& command)
{
  // Passed in command: playerID and direction
  
  int team_no;

  if ( !(teams[0].isAlive() && teams[1].isAlive()) ) {
   //fprintf(stderr, "Game is already over!! file: %s line %d\n", __FILE__, __LINE__);
    return;
  }

  if ( (team_no = WhichTeam(command.playerID) == NOT_FOUND) ) {
    fprintf(stderr, "playerID not found file: %s line %d\n", __FILE__, __LINE__);
    return;
  }
  // Attack!!
  updateMaps();
}
/*------------------------------------------------------------------------------
-- FUNCTION:   updateMovePlayer
--
-- DATE:        2013/04/07
--
-- DESIGNER:   
-- PROGRAMMER: Jesse Wright
--
-- INTERFACE:   void updateMovePlayer(CommandData& command)
--
-- RETURNS:     void.
--
-- DESCRIPTION: Updates the players movement.
------------------------------------------------------------------------------*/
void ServerGameLogic::updateMovePlayer(CommandData& command)
{
  int team_no;
  Player* temp;
  
  if ( !(teams[0].isAlive() && teams[1].isAlive()) ) {
    return;
  }
  
  if((team_no = WhichTeam(command.unitID)) == CREEP_COOLDOWN)
  {
    return; // not found
  }

  temp = teams[team_no].findPlayer(command.playerID);
  if(temp == 0)
  {
    return;
  }

  temp->direction = command.direction;

  updateMaps();
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void ServerGameLogic::updateMoveUnit(CommandData& command)
{
  if ( !(teams[0].isAlive() && teams[1].isAlive()) ) {
    return;
  }


  updateMaps();
}
/*------------------------------------------------------------------------------
-- FUNCTION:   distance
--
-- DATE:        2013/03/22
--
-- DESIGNER:   David Czech
-- PROGRAMMER: David Czech
--
-- INTERFACE:   double distance(Point p, Point q)
--
-- RETURNS:     double - distance between p and q
--
-- DESCRIPTION: uses distance formula to find distance between p and q.
------------------------------------------------------------------------------*/
double distance(Point p, Point q)
{
  return sqrt( pow(q.x-p.x,2) + pow(q.y-p.y, 2));
}
/*------------------------------------------------------------------------------
-- FUNCTION:    updateMovement
--
-- DATE:        2013/03/22
--
-- DESIGNER:    David Czech, Behnam Bastami
-- PROGRAMMER:  Darry Danzig, Behnam Bastami, David Czech, Jesse Braham, Callum Styan
--
-- INTERFACE:   void ServerGameLogic::updateMovement (int team, int otherteam)
--
-- RETURNS:     void
--
-- DESCRIPTION: This function handles player movment.  It validates positions
--              (ensuring players don't leave the map), and performs collision
--              detection.  Also deals with player deaths and player respawns.
------------------------------------------------------------------------------*/
void ServerGameLogic::updateMovement (int team, int otherteam) {
for (unsigned int i = 0; i < teams[team].players.size(); ++i) {
    bool collided = false;
    int dir = teams[team].players[i]->direction;
    
    Point new_position = teams[team].players[i]->position;

    // std::cout << "TEAM: " << team << " PLAYER : " <<  i  << "TOD: " << teams[team].players[i]->tod  << std::endl;
    if (teams[team].players[i]->tod != 0 && time(NULL) >= teams[team].players[i]->tod + 5)
    {
        respawnPlayer(teams[team].players[i], teams[team].players[i]->team == 0 ? gameMap_->team0start[0] : gameMap_->team1start[0]);
        teams[team].players[i]->tod = 0;
        continue;
    }
    
    if (teams[team].players[i]->tod != 0) { // death
        continue;
    }

    if (dir & UP)
       new_position.y-= teams[team].players[i]->moveSpeed;
    if (dir & DOWN)
       new_position.y+= teams[team].players[i]->moveSpeed;
    if (dir & LEFT)
       new_position.x-= teams[team].players[i]->moveSpeed;
    if (dir & RIGHT)
       new_position.x+= teams[team].players[i]->moveSpeed;

   
    // Validate new position
    if (new_position.x >= 0 && new_position.x <= MAP_X - PLAYER_WIDTH)
	if (new_position.y >= 0 && new_position.y <= MAP_Y - PLAYER_HEIGHT)
	    teams[team].players[i]->position = new_position;

    for (unsigned int j = 0; j < teams[otherteam].players.size(); ++j) {
      if (teams[otherteam].players[j]->tod == 0 && distance(teams[team].players[i]->position, teams[otherteam].players[j]->position) < 25) {
        teams[otherteam].players[j]->health -= teams[team].players[i]->attackDamage;
        collided = true;
        break;
      }
    }

    for (unsigned int j = 0; j < teams[otherteam].creeps.size(); ++j) {
      if (distance(teams[team].players[i]->position, teams[otherteam].creeps[j]->position) < 25) {
        teams[otherteam].creeps[j]->health -= teams[team].players[i]->attackDamage;
        collided = true;
        break;
      }
    }

    for (unsigned int j = 0; j < teams[otherteam].towers.size(); ++j) {
      if (distance(teams[team].players[i]->position, teams[otherteam].towers[j]->position) < 25) {
        teams[otherteam].towers[j]->health -= teams[team].players[i]->attackDamage;
        collided = true;
        break;
      }
    }

    // If we collided with something else, stay where we are.
    if (collided){
      if (dir & UP)
        teams[team].players[i]->position.y+= teams[team].players[i]->moveSpeed;
      if (dir & DOWN)
        teams[team].players[i]->position.y-= teams[team].players[i]->moveSpeed;
      if (dir & LEFT)
        teams[team].players[i]->position.x+= teams[team].players[i]->moveSpeed;
      if (dir & RIGHT)
        teams[team].players[i]->position.x-= teams[team].players[i]->moveSpeed;
    }
  }
}

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: Darry Danzig
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void ServerGameLogic::update()
{ 
  updateMaps();
  
  pthread_mutex_lock( &unit_mutex );
  updateMovement(0, 1);
  updateMovement(1, 0);
  pthread_mutex_unlock( &unit_mutex );

  if (requestedCommands.empty())
    return;

  // Take snap shot of queue at time0
  // Only process the number of commands that were there at time0
  int size_at_time0 = requestedCommands.size(); // <---- this is time0

  for (int i=0; i<size_at_time0; i++) {

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
  updateMaps();
}

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: Darry Danzig
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void ServerGameLogic::updateTimer(int i)
{
  signal(SIGALRM, updateTimer);

#ifndef TESTCLASS
  pthread_mutex_lock( &gSGL->unit_mutex );
  AiUpdate(gSGL->teams[0], gSGL->teams[1]);
  pthread_mutex_unlock( &gSGL->unit_mutex );
#endif

  gSGL->update();

  gSGL->handleDeaths();

  // Call network update function
  ServerGameLogic::setAlarm();
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: Darry Danzig
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
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

  signal(SIGALRM, updateTimer); /* set the Alarm signal capture */

}


/*------------------------------------------------------------------------------
-- FUNCTION:   createCreep
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Behnam Bastami, Dennis Ho, Jesse Wright
-- PROGRAMMER: Behnam Bastami, Dennis Ho, Jesse Wright, Kevin Tangeman, Callum Styan
--
-- INTERFACE:   void createCreep(int team_no, Point location, int path_no, UnitType unitType)
--
-- RETURNS:     void.
--
-- DESCRIPTION: Creates the creep. Uses the unit type passed in to set the
-- attributes of the creep.
------------------------------------------------------------------------------*/
void ServerGameLogic::createCreep(int team_no, Point location, int path_no, UnitType unitType)
{  
  int uid = next_unit_id_++;

  int hp = INIT_CREEP_HP;
  int atkdmg = INIT_CREEP_ATKDMG;
  int atkrng = INIT_CREEP_ATKRNG * 4;
  int atkspd = INIT_CREEP_ATKSPD;
  int percep = INIT_CREEP_PERCEP * 10;
  int atkcnt = INIT_CREEP_ATKCNT;
  int spd = INIT_CREEP_SPD;
  switch(unitType)
  {

    case CREEP_ONE: // regular
      hp = INIT_CREEP_HP;
      atkdmg = INIT_CREEP_ATKDMG;
      atkrng = INIT_CREEP_ATKRNG * 4;
      atkspd = INIT_CREEP_ATKSPD;
      percep = INIT_CREEP_PERCEP * 10;
      atkcnt = INIT_CREEP_ATKCNT;
      spd = INIT_CREEP_SPD;
    break;
    case CREEP_TWO: // Tank (lots of health, but moves slowly)
      hp = INIT_CREEP_HP * 3;
      atkdmg = INIT_CREEP_ATKDMG + 4;
      atkrng = INIT_CREEP_ATKRNG * 4;
      atkspd = INIT_CREEP_ATKSPD;
      percep = INIT_CREEP_PERCEP * 5;
      atkcnt = INIT_CREEP_ATKCNT;
      spd = INIT_CREEP_SPD / 2;
    break;
    case CREEP_THREE: // Fast.
      hp = INIT_CREEP_HP * .75;
      atkdmg = INIT_CREEP_ATKDMG;
      atkrng = INIT_CREEP_ATKRNG * 4;
      atkspd = INIT_CREEP_ATKSPD / 2;
      percep = INIT_CREEP_PERCEP * 10;
      atkcnt = INIT_CREEP_ATKCNT;
      spd = INIT_CREEP_SPD * 1.5;
    break;
    default:
    break;
  }
  

  Direction direct = Direction();
  Point *path= &teams[team_no].paths[path_no % PATH_COUNT][0];
  int movespeed = INIT_CREEP_MOVESPEED;

  Point spawnLocation = FindCreepSpawnPoint(team_no, path_no);

  // if( CREEP_COST <= team currency ) then carry on and create a creep
  if(CREEP_COST <= teams[team_no].currency){

    // Create creep  
    Creep *creep = new Creep(uid, spawnLocation, hp, atkdmg, atkrng, atkspd, percep, atkcnt, spd, direct, path, movespeed);  

    // Add creep to team
    teams[team_no].addUnit(creep);  
 
    // Pay for creep
    teams[team_no].currency -= CREEP_COST;
  }
}


/*------------------------------------------------------------------------------
-- FUNCTION:   createTower
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Dennis Ho
-- PROGRAMMER: Dennis Ho, Kevin Tangeman
--
-- INTERFACE:   void ServerGameLogic::createTower(int team_no, Point location)
--
-- RETURNS:     
--
-- DESCRIPTION: Creates a tower
------------------------------------------------------------------------------*/
void ServerGameLogic::createTower(int team_no, Point location, UnitType ut)
{
   Point castleLoc;   
  double distX, distY;
  int maxTowerDist, dist;
  
  // calculate maxDist tower can be created from the castle 
  maxTowerDist = (((MAPWIDTH + MAPHEIGHT) / 2) - INIT_TOWER_ATKRNG);
  
  // get location of team's castle                 
  for(std::vector<Tower*>::iterator it = teams[team_no].towers.begin(); it != teams[team_no].towers.end(); ++it)
    if ((*it)->getType() == CASTLE) // then this is the team's castle
      castleLoc = (*it)->getPos();  // castle location
    
  // get distance of proposed location from castle
    distX = abs(castleLoc.x - location.x);
    distY = abs(castleLoc.y - location.y);
    dist = distX + distY;

  if((dist <= maxTowerDist) && (TOWER_COST <= teams[team_no].currency)){
  
    int uid = next_unit_id_++;

    // create new tower                     
    Tower *tower;
    
    if (ut == TOWER_ONE)
      tower = new BasicTower(uid, team_no, location, INIT_TOWER_HP, INIT_TOWER_ATKDMG, INIT_TOWER_ATKRNG, 
                           INIT_TOWER_ATKSPD, INIT_TOWER_PERCEP, INIT_TOWER_ATKCNT, INIT_TOWER_WALL);
    else if (ut == TOWER_TWO)
      tower = new ElectroTower(uid, team_no, location, INIT_TOWER_HP, INIT_TOWER_ATKDMG, INIT_TOWER_ATKRNG*2, 
                           INIT_TOWER_ATKSPD, INIT_TOWER_PERCEP, INIT_TOWER_ATKCNT, INIT_TOWER_WALL);
    else if (ut == TOWER_THREE)
      tower = new SplashTower(uid, team_no, location, INIT_TOWER_HP, INIT_TOWER_ATKDMG, INIT_TOWER_ATKRNG, 
                           INIT_TOWER_ATKSPD, INIT_TOWER_PERCEP, INIT_TOWER_ATKCNT, INIT_TOWER_WALL, 10, 60);
    else
      tower = new BasicTower(uid, team_no, location, INIT_TOWER_HP, INIT_TOWER_ATKDMG, INIT_TOWER_ATKRNG, 
                           INIT_TOWER_ATKSPD, INIT_TOWER_PERCEP, INIT_TOWER_ATKCNT, INIT_TOWER_WALL);
    //tower->team = team_no;

        
    // Add tower to team
    teams[team_no].addUnit(tower);

    // Pay for tower
    teams[team_no].currency -= TOWER_COST;

    // Update the Map!
    gameMap_->addUnit(tower, location);
  }
}


/*------------------------------------------------------------------------------
-- FUNCTION:   createPlayer
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Dennis Ho, Callum Styan, Behnam Bastami
-- PROGRAMMER: Dennis Ho, Callum Styan, Behnam Bastami
--
-- INTERFACE:   void ServerGameLogic::createPlayer(int team_no, Point location, int client_id, int role)
--
-- RETURNS:     
--
-- DESCRIPTION: Creates a human controlled player
------------------------------------------------------------------------------*/
void ServerGameLogic::createPlayer(int team_no, Point location, int client_id, int role)
{
  int uid = next_unit_id_++;

  //set up base player
  Player *player = new Player(uid, client_id, location, role);
  player->setSpeed(5);
  player->team = team_no;

  std::cout << "role: " << role << std::endl;

  switch (role){
    case 0: //mario, builder
      player->attackDamage = 8;
    break;

    case 1: //gordon freeman
      player->health = 275;
      player->attackDamage = 12;
      player->setSpeed(6);
    break;

    case 2: //the flash
      player->setSpeed(9);
      player->attackDamage = 7;
    break;

    case 3: //samus
      player->health = 215;
      player->setSpeed(6);
      player->attackDamage = 9;
    break;

    case 4: //hulk
      player->setSpeed(3);
      player->health = 600;
      player->attackDamage = 15;
    break;
  }
  player->maxHealth = player->health;
  teams[team_no].addUnit(player);
  std::cout << "adding player: " << player->clientID << " team: " << team_no << std::endl;
}
/*------------------------------------------------------------------------------
-- FUNCTION:   respawnPlayer
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Dennis Ho
-- PROGRAMMER: Dennis Ho, Jesse Braham
--
-- INTERFACE:   void ServerGameLogic::respawnPlayer(Player* player, Point location)
--
-- RETURNS:     
--
-- DESCRIPTION: Respawns a dead player (This only resets state - does not create a new object)
------------------------------------------------------------------------------*/
void ServerGameLogic::respawnPlayer(Player* player, Point location)
{
  player->position = location;
  player->health = player->maxHealth;
  player->pendingDelete = false;
}
/*------------------------------------------------------------------------------
-- FUNCTION:   giveTeamBonus
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Dennis Ho
-- PROGRAMMER: Dennis Ho
--
-- INTERFACE:   void ServerGameLogic::giveTeamBonus(int team_no, int amount)
--
-- RETURNS:     
--
-- DESCRIPTION: Gives a currency bonus to the specified team (used for when you kill an enemy)
------------------------------------------------------------------------------*/
void ServerGameLogic::giveTeamBonus(int team_no, int amount)
{
  teams[team_no].currency += amount;
}
/*------------------------------------------------------------------------------
-- FUNCTION:   handleDeaths
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Dennis Ho
-- PROGRAMMER: Dennis Ho
--
-- INTERFACE:   void ServerGameLogic::handleDeaths()
--
-- RETURNS:     
--
-- DESCRIPTION: Detect and handle all unit deaths
------------------------------------------------------------------------------*/
void ServerGameLogic::handleDeaths()
{
  pthread_mutex_lock( &unit_mutex );
  
  for (size_t i = 0; i < 2; ++i)
  {
    for (size_t j = 0; j < teams[i].players.size(); ++j)        
      if (teams[i].players[j]->pendingDelete)
        handlePlayerDeath(teams[i].players[j]);
    for (size_t j = 0; j < teams[i].creeps.size(); ++j)        
      if (teams[i].creeps[j]->pendingDelete)
        handleCreepDeath(teams[i].creeps[j]);
    for (size_t j = 0; j < teams[i].towers.size(); ++j)
      if (teams[i].towers[j]->pendingDelete)
      {
        if (j == 0)
            handleCastleDeath();
        else
            handleTowerDeath(teams[i].towers[j]);
      }
  }
  
  pthread_mutex_unlock( &unit_mutex );

  updateMaps();
}
/*------------------------------------------------------------------------------
-- FUNCTION:    handlePlayerDeath
--
-- DATE:        2013/04/11
--
-- DESIGNER:    Dennis Ho, David Czech, Jesse Braham
-- PROGRAMMER:  Dennis Ho, David Czech, Jesse Braham
--
-- INTERFACE:   void ServerGameLogic::handlePlayerDeath(Player *player)
--
-- RETURNS:     void
--
-- DESCRIPTION: This function checks if the player is alive or dead.  If the
--              Player is alive, the opposing team is given a bonus, and the
--              player's time of death is set.
------------------------------------------------------------------------------*/
void ServerGameLogic::handlePlayerDeath(Player *player)
{

  // Give other team some monies
  if (player->tod == 0) {
    giveTeamBonus(player->team == 0 ? 1 : 0, PLAYER_KILL_BONUS);
      
    // Set Respawn timestamp
    player->tod = time(NULL);
  }
}
/*------------------------------------------------------------------------------
-- FUNCTION:   handleCreepDeath
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Dennis Ho
-- PROGRAMMER: Dennis Ho
--
-- INTERFACE:   void ServerGameLogic::handleCreepDeath(Creep *creep)
--
-- RETURNS:     
--
-- DESCRIPTION: Handles a creep death event
------------------------------------------------------------------------------*/
void ServerGameLogic::handleCreepDeath(Creep *creep)
{
  // Remove creep
  teams[creep->team].removeUnit(creep);

  // Give other team some monies
  giveTeamBonus(creep->team == 0 ? 1 : 0, CREEP_KILL_BONUS);
}
/*------------------------------------------------------------------------------
-- FUNCTION:   handleTowerDeath
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Dennis Ho
-- PROGRAMMER: Dennis Ho
--
-- INTERFACE:   void ServerGameLogic::handleTowerDeath(Tower *tower)
--
-- RETURNS:     
--
-- DESCRIPTION: Handles a tower (non-castle) death event
------------------------------------------------------------------------------*/
void ServerGameLogic::handleTowerDeath(Tower *tower)
{
  // Remove tower
  teams[tower->team].removeUnit(tower);

  // Give other team some monies
  giveTeamBonus(tower->team == 0 ? 1 : 0, TOWER_KILL_BONUS);
}
/*------------------------------------------------------------------------------
-- FUNCTION:   handleCastleDeath
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Dennis Ho   
-- PROGRAMMER: Dennis Ho
--
-- INTERFACE:   void ServerGameLogic::handleCastleDeath()
--
-- RETURNS:     
--
-- DESCRIPTION: Handles a castle death event
------------------------------------------------------------------------------*/
void ServerGameLogic::handleCastleDeath()
{
  // Game over
  gameState_ = GAME_END;
}

/*------------------------------------------------------------------------------
-- FUNCTION:   getPlayerRole
--
-- DATE:        2013/03/22
--
-- DESIGNER:   Albert Liao
-- PROGRAMMER: Albert Liao
--
-- INTERFACE:   int getPlayerRole(int teamNumber, int playerID)
--
-- RETURNS: int - returns the role of the player found. -1 if player isn't found.
--
-- DESCRIPTION: Iterates through the player container to find the player's role via
-- the playerID.
------------------------------------------------------------------------------*/
int ServerGameLogic::getPlayerRole(int teamNumber, int playerID)
{
  for (std::vector<Player*>::iterator it = teams[teamNumber].players.begin(); it != teams[teamNumber].players.end(); ++it)
  {
    std::cout << "player id: " << playerID << std::endl;
    std::cout << "client id: " << (*it)->clientID << std::endl;
    if((*it)->clientID == playerID)
    {
      return (*it)->role;
    }
  }

  return -1;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    getPlayerIsAlive
--
-- DATE:        2013/03/22
--
-- DESIGNER:    Albert Liao, Jesse Braham
-- PROGRAMMER:  Albert Liao, Jesse Braham
--
-- INTERFACE:   bool ServerGameLogic::getPlayerIsAlive(int teamNumber, int playerID)
--
-- RETURNS:     Boolean; whether or not the player is alive.
--
-- DESCRIPTION: This function returns the status of the player, whether he is
--              alive or dead.  If the player's Time of Death (tod) is 0, the
--              player is alive.  If it is not, the player is dead.
------------------------------------------------------------------------------*/
bool ServerGameLogic::getPlayerIsAlive(int teamNumber, int playerID)
{
  for (std::vector<Player*>::iterator it = teams[teamNumber].players.begin(); it != teams[teamNumber].players.end(); ++it)
  {
    if((*it)->clientID == playerID)
    {
      return (*it)->tod == 0;
    }
  }

  return -1;
}

/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:  Darry Danzig
-- PROGRAMMER: Darry Danzig
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void ServerGameLogic::updateMaps() {

  mapTeams_[0].build(teams[0]);
  mapTeams_[1].build(teams[1]);
  mapBoth_.merge(mapTeams_[0], mapTeams_[1]);

}

// To test this class use  g++ -DTESTCLASS -g -Wall server_game_logic.cpp ../build/units/*.o
#ifdef TESTCLASS
int main() {

  ServerGameLogic game;

  game.startGame();

  while (1);

}
#endif
