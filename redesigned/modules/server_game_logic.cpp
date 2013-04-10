#include "server_game_logic.h"
#include "../units/castle.h"
#include "../units/AiController.h"
#include "../units/player.h"
#include "../units/basic_tower.h"
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>
#include <errno.h>
#include <new>
#include <cmath>

#define NOT_FOUND 2

ServerGameLogic * gSGL;

/* Constructor
 *
 * PRE:    
 * POST:    
 * NOTES:   Creates a thread and starts running the module */
  ServerGameLogic::ServerGameLogic()
: gameState_(LOBBY), next_unit_id_(1)
{
  PATH p;
  Point a;
  a.x = 0;
  a.y = 0;
  p.push_back(a);
  a.x = 210;
  a.y = 210;
  p.push_back(a);
  a.x = 100;
  a.y = 200;
  p.push_back(a);
  a.x = 200;
  a.y = 100;
  p.push_back(a);
  teams[0].paths.push_back(p);
  teams[1].paths.push_back(p);
  a.x = 250;
  a.y = 250;
  PATH p2;
  p2.push_back(a);
  a.x = 200;
  a.y = 200;
  p2.push_back(a);
  teams[0].paths.push_back(p2);

  pthread_mutex_init(&unit_mutex, NULL);

  gameMap_ = new GameMap();
  gameMap_->initMap();

#if 0
#ifndef TESTCLASS
  Creep c;
  c.pPath = &teams[1].paths[0][0];
  c.attackRange = 100;
  c.attackDamage = 10;
  c.health = 100;
  c.position.x = 200;
  c.position.y = 200;
  c.moveSpeed = 1;
  teams[0].creeps.push_back(c);


  c.position.x = 250;
  c.position.y = 200;
  c.moveSpeed = 1;
  teams[1].creeps.push_back(c);
  initializeCastles();
  //initializeTeams();

  startGame();
#endif
#endif
}   

ServerGameLogic::~ServerGameLogic()
{
}
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
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
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
void ServerGameLogic::initializeCastles() 
{

  int uid = next_unit_id_++;
  /*Point pos;
  pos.x = 0;
  pos.y = 0;*/

  // Team 0
  Castle *castle1 = new Castle(uid, gameMap_->castle1, INIT_CASTLE_HP, INIT_CASTLE_ATKDMG, INIT_CASTLE_ATKRNG, INIT_CASTLE_ATKSPD,
      INIT_CASTLE_PERCEP, INIT_CASTLE_ATKCNT, INIT_CASTLE_WALL, 0);
  teams[0].towers.push_back(castle1);
  teams[0].units.push_back(castle1);

  Point p = castle1->getPos();
  printf("Castle 1 position..x: %d y: %d\n", p.x, p.y);
  
  // Team 1
  uid = next_unit_id_++;
  //pos.x = MAX_X; // TODO: MAX_X and MAX_Y will  be replaced later when we get map reading functionality working
  //pos.y = MAX_Y; // TODO:
  Castle *castle2 = new Castle(uid, gameMap_->castle2, INIT_CASTLE_HP, INIT_CASTLE_ATKDMG, INIT_CASTLE_ATKRNG, INIT_CASTLE_ATKSPD,
      INIT_CASTLE_PERCEP, INIT_CASTLE_ATKCNT, INIT_CASTLE_WALL, 1);
  teams[1].towers.push_back(castle2);
  teams[1].units.push_back(castle2);

#ifdef TESTCLASS

  p = castle2.getPos();

  printf("Castle 2 position..x: %d y: %d\n", p.x, p.y);

  mapTeams_[0].build(teams[0]);
  mapTeams_[1].build(teams[1]);

  printf("Castle 2 id %d\n", castle2.id);

  printf("Team 0\n");
  mapTeams_[0].printGrid();
  printf("Team 1\n");
  mapTeams_[1].printGrid();

  //mapBoth_.merge(mapTeams_[0], mapTeams_[1]);

  //printf("Both\n");
  //mapBoth_.printGrid();

#endif
}
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
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

  /*Point pos = Point(230, 230);
  int uid = next_unit_id_++;

  int hp = INIT_CREEP_HP;
  int atkdmg = INIT_CREEP_ATKDMG;
  int atkrng = INIT_CREEP_ATKRNG;
  int atkspd = INIT_CREEP_ATKSPD;
  int percep = INIT_CREEP_PERCEP;
  int atkcnt = INIT_CREEP_ATKCNT;
  int spd = INIT_CREEP_SPD;
  Direction direct = Direction();
  Point *path = &teams[0].paths[2][0];
  int movespeed = INIT_CREEP_MOVESPEED;

  // Add creep to team  
  Creep *creep = new Creep(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, spd, direct, path, movespeed);  
  teams[0].addUnit(creep);  

  // Pay for creep
  teams[0].currency -= CREEP_COST;*/
}
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
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

/* Sets all teams' initial currency.
 *
 * PRE:     2 teams exist
 * POST:    The currency of all teams has been set to an initial value
 * RETURNS:
 * NOTES:    */
void ServerGameLogic::initializeCurrency()
{
  for (int team_i=0; team_i<2; team_i++)
    teams[team_i].currency = INIT_CURRENCY;
}
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
void ServerGameLogic::initializePlayers(std::vector<player_matchmaking_t> players)
{
  for (std::vector<player_matchmaking_t>::iterator it = players.begin(); it != players.end(); ++it) {
    createPlayer(it->team, it->team == 0 ? gameMap_->team0start[0] : gameMap_->team1start[0], it->pid, it->role);
  }
}
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
void ServerGameLogic::initializePaths()
{  
}
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
void ServerGameLogic::initializeTeams(std::vector<player_matchmaking_t> players)
{
  initializePaths(); // Must be done before initializing creeps
  initializeCastles();
  initializeCreeps();
  initializeTowers();
  initializeCurrency();
  initializePlayers(players);

#ifdef TESTCLASS  
  mapTeams_[0].build(teams[0]);
  mapTeams_[1].build(teams[1]);
  mapBoth_.merge(mapTeams_[0], mapTeams_[1]);
  mapBoth_.printGrid();
#endif
}

/* Starts the game.
 *
 * PRE:     Game is in the lobby and players are ready.
 * POST:    Data structures and initialized and game is placed in an active state, with all appropriate modules processing.
 * RETURNS:
 * NOTES:    */
void ServerGameLogic::startGame()
{
  gSGL = this;
  setAlarm();
}

/* Receive and queue a create unit command from a client.
 *
 * PRE:     Game is active.
 * POST:    Command has been queued.
 * RETURNS:
 * NOTES:   No validation is performed here. */
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
/* 
 *
 * PRE: Game is started.
 * POST: Will set point for the spawn place of the creep.
 * PROGRAMMER: Jesse Wright
 * RETURNS: The point where the creep will spawn.
 *          
 * NOTES: Uses the players team and selected path number
 * to discern where the creep will spawn based on map coordinates.
 */
Point ServerGameLogic::FindCreepSpawnPoint(int team_no, int pathID)
{
  Point creepSpawnLocation;
  if(team_no == 2) // team 2
  {
    if(pathID == HIGHPATH)
    {
      creepSpawnLocation.x = gameMap_->topOne[0].x; // first point of the top path.
      creepSpawnLocation.y = gameMap_->topOne[0].y; // first point of the top path.
    }else if(pathID == MIDPATH)
    {
      creepSpawnLocation.x = gameMap_->midOne[0].x; // first point of the top path.
      creepSpawnLocation.y = gameMap_->midOne[0].y; // first point of the top path.
    }else
    {
      creepSpawnLocation.x = gameMap_->botOne[0].x; // first point of the top path.
      creepSpawnLocation.y = gameMap_->botOne[0].y; // first point of the top path.
    }
  } else if(team_no == 1)// team 2
  {
    if(pathID == HIGHPATH)
    {
      creepSpawnLocation.x = gameMap_->topTwo[0].x; // first point of the top path.
      creepSpawnLocation.y = gameMap_->topTwo[0].y; // first point of the top path.
    }else if(pathID == MIDPATH)
    {
      creepSpawnLocation.x = gameMap_->midTwo[0].x; // first point of the top path.
      creepSpawnLocation.y = gameMap_->midTwo[0].y; // first point of the top path.
    }else
    {
      creepSpawnLocation.x = gameMap_->botTwo[0].x; // first point of the top path.
      creepSpawnLocation.y = gameMap_->botTwo[0].y; // first point of the top path.
    }
  }
  return creepSpawnLocation;
}

/* Receive and queue a move player command from a client.
 *
 * PRE:     Game is active.
 * POST:    Command has been queued.
 * PROGRAMMER:
 * RETURNS:
 * NOTES:   No validation is performed here. */
void ServerGameLogic::receiveMovePlayerCommand(int playerId, Direction direction)
{
  CommandData newCommand;

  newCommand.cmd = MovePlayer;
  newCommand.playerID = playerId;
  newCommand.direction = direction;
  newCommand.unitID = playerId;

  requestedCommands.push(newCommand);
}
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
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
 * PROGRAMMER:
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

/*
 * PRE:  Maps are current
 * PROGRAMMER:
 * RETURNS: 
 * 0 - Team 1
 * 1 - Team 2
 * 2 - Not Found
 */
int ServerGameLogic::WhichTeam(int id) {

  updateMaps();

  //USE THIS UNTIL YOUR MAP STUFF WORKS
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
/*
  if (mapTeams_[0].units_.find(id) != mapTeams_[0].units_.end())
    return 0;

  if (mapTeams_[1].units_.find(id) != mapTeams_[1].units_.end())
    return 1;
  return 2;
  */
}
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
void ServerGameLogic::updateCreate(CommandData& command)
{
  // Passed in command: PlayerId, type, location

  int team_no;

  int x = command.location.x;
  int y = command.location.y;

  if ( !(teams[0].isAlive() && teams[1].isAlive()) ) {
    gameState_ = WON_GAME;
   // fprintf(stderr, "Game is already over!! file: %s line %d\n", __FILE__, __LINE__);
    return;
  }

  if ( ( (team_no = WhichTeam(command.playerID)) == NOT_FOUND) ) {
   // fprintf(stderr, "playerID not found file: %s line %d\n", __FILE__, __LINE__);
    return;
  }

  // If we aren't a builder (role 0) break and don't allow a build.
  if(getPlayerRole(team_no, command.playerID) != 0)
  {
    return;
  }

  updateMaps();
  if (!mapTeams_[0].isValidPos(command.location)) {
  //  fprintf(stderr, "max x: %d max y: %d\n", MAX_X, MAX_Y);
 //   fprintf(stderr, "x: %d, y: %d out of range: %s line %d\n", x, y, __FILE__, __LINE__);
    return; 
  }

  if ( mapBoth_.grid_[x][y] != 0 )
    return; // position is already occupied 

  // Create Unit  
  switch (command.type) {
    case CREEP:
      {

        createCreep(team_no, command.location, command.pathID);    
        break;
      }
    case CASTLE:
    case TOWER:
    case TOWER_ONE:
      {        
        createTower(team_no, command.location);        
        break;
      }
    default:
      fprintf(stderr, "Unknown type %s line:%d\n", __FILE__, __LINE__);
      return;
  }

  mapTeams_[0].build(teams[0]);
  mapTeams_[1].build(teams[1]);
  // Update the our map 
  /*
  Location location;
  location.pos  = command.location;
  location.type = command.type;
  mapTeams_[team_no].units_[next_unit_id_] = location;
  mapTeams_[team_no].grid_[x][y] = next_unit_id_;
  */
}
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
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
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
void ServerGameLogic::updateMovePlayer(CommandData& command)
{
  int team_no;
  Player* temp;
  
  if ( !(teams[0].isAlive() && teams[1].isAlive()) ) {
  //  fprintf(stderr, "Game is already over!! file: %s line %d\n", __FILE__, __LINE__);
    return;
  }
  
  if((team_no = WhichTeam(command.unitID)) == 2)
  {
    return; // not found
  }

  temp = teams[team_no].findPlayer(command.playerID);
  if(temp == 0)
  {
    return;
  }

  temp->direction = command.direction;
 // std::cout << "moving player" << std::endl;

  updateMaps();
}
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
void ServerGameLogic::updateMoveUnit(CommandData& command)
{
  if ( !(teams[0].isAlive() && teams[1].isAlive()) ) {
  //  fprintf(stderr, "Game is already over!! file: %s line %d\n", __FILE__, __LINE__);
    return;
  }


  updateMaps();
}
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
double distance(Point p, Point q)
{
  return sqrt( pow(q.x-p.x,2) + pow(q.y-p.y, 2));
}

void ServerGameLogic::updateMovement (int team, int otherteam) {
for (unsigned int i = 0; i < teams[team].players.size(); ++i) {
    bool collided = false;
    int dir = teams[team].players[i]->direction;

    if (dir & UP)
      teams[team].players[i]->position.y-= teams[team].players[i]->moveSpeed;
    if (dir & DOWN)
      teams[team].players[i]->position.y+= teams[team].players[i]->moveSpeed;
    if (dir & LEFT)
      teams[team].players[i]->position.x-= teams[team].players[i]->moveSpeed;
    if (dir & RIGHT)
      teams[team].players[i]->position.x+= teams[team].players[i]->moveSpeed;


    for (unsigned int j = 0; j < teams[otherteam].players.size(); ++j) {
      if (distance(teams[team].players[i]->position, teams[otherteam].players[j]->position) < 25) {
        teams[otherteam].players[j]->health -= 1;
        collided = true;
        break;
      }
    }

    for (unsigned int j = 0; j < teams[otherteam].creeps.size(); ++j) {
      if (distance(teams[team].players[i]->position, teams[otherteam].creeps[j]->position) < 25) {
        teams[otherteam].creeps[j]->health -= 1;
        collided = true;
        break;
      }
    }

    for (unsigned int j = 0; j < teams[otherteam].towers.size(); ++j) {
      if (distance(teams[team].players[i]->position, teams[otherteam].towers[j]->position) < 25) {
        teams[otherteam].towers[j]->health -= 1;
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

/* Processes all waiting commands.
 *
 * PRE:    
 * POST:    Command queue is cleared.
 * PROGRAMMER:
 * RETURNS:
 * NOTES:   Perform validation here.
 *          Nice to have: send a fail message if command is invalid */
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

/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
void ServerGameLogic::updateTimer(int i)
{
  signal(SIGALRM, updateTimer);

#ifndef TESTCLASS
  AiUpdate(gSGL->teams[0], gSGL->teams[1]);
#endif

  gSGL->update();

  gSGL->handleDeaths();

  // Call network update function
  ServerGameLogic::setAlarm();
}
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
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


/* Creates a creep.
 *
 * PRE:     Teams are initialized.
 * POST:    A creep has been created and added to the specified team. The team's currency has been
 *          decremented accordingly.
 * PROGRAMMER:
 * RETURNS:
 * NOTES:   
 *
 * REVISIONS: Kevin - Only creates creep if there is enough currency.

 */
void ServerGameLogic::createCreep(int team_no, Point location, int path_no)
{  
  int uid = next_unit_id_++;
  
  int hp = INIT_CREEP_HP;
  int atkdmg = INIT_CREEP_ATKDMG;
  int atkrng = INIT_CREEP_ATKRNG * 4;
  int atkspd = INIT_CREEP_ATKSPD;
  int percep = INIT_CREEP_PERCEP * 10;
  int atkcnt = INIT_CREEP_ATKCNT;
  int spd = INIT_CREEP_SPD;
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


/* Creates a tower.
 *
 * PRE:     Teams are initialized.
 * POST:    A tower has been created and added to the specified team. The team's currency has been
 *          decremented accordingly.
 * PROGRAMMER:
 * RETURNS:
 * NOTES:   
 *
 * REVISIONS: Kevin - Only creates tower if the chosen location is within the team's half
 *                  of the map AND there is enough currency.
 *                  - changed to calling BasicTower constructor & sending team_no
 */
void ServerGameLogic::createTower(int team_no, Point location)
{
   Point castleLoc;   
  double distX, distY;
  int maxTowerDist, dist;
  
  // calculate maxDist tower can be created from the castle 
  //    based on (((MAPWIDTH + MAPHEIGHT) / 2) - initial tower attack range)
  maxTowerDist = (((MAPWIDTH + MAPHEIGHT) / 2) - INIT_TOWER_ATKRNG);
  
  // get location of team's castle                 
  for(std::vector<Tower*>::iterator it = teams[team_no].towers.begin(); it != teams[team_no].towers.end(); ++it)
    if ((*it)->getType() == CASTLE) // then this is the team's castle
      castleLoc = (*it)->getPos();  // castle location
    
  // get distance of proposed location from castle
  dist = distance( castleLoc, location);

  // if( chosen distance from player's team's castle is <= maxTowerDist && 
  //       TOWER_COST <= team currency ) then carry on and create a tower
  if((dist <= maxTowerDist) && (TOWER_COST <= teams[team_no].currency)){
  
    int uid = next_unit_id_++;

    // create new tower
//    Tower *tower = new Tower(uid, location, INIT_TOWER_HP, INIT_TOWER_ATKDMG, INIT_TOWER_ATKRNG, 
//                           INIT_TOWER_ATKSPD, INIT_TOWER_PERCEP, INIT_TOWER_ATKCNT, INIT_TOWER_WALL);
//    Tower *tower = new Tower(uid, team_no, location, INIT_TOWER_HP, INIT_TOWER_ATKDMG, INIT_TOWER_ATKRNG, 
//                           INIT_TOWER_ATKSPD, INIT_TOWER_PERCEP, INIT_TOWER_ATKCNT, INIT_TOWER_WALL);                           
    BasicTower *tower = new BasicTower(uid, team_no, location, INIT_TOWER_HP, INIT_TOWER_ATKDMG, INIT_TOWER_ATKRNG, 
                           INIT_TOWER_ATKSPD, INIT_TOWER_PERCEP, INIT_TOWER_ATKCNT, INIT_TOWER_WALL);
        
                           
    // Add tower to team
    teams[team_no].addUnit(tower);

    // Pay for tower
    teams[team_no].currency -= TOWER_COST;

    // Update the Map!
    gameMap_->addUnit(tower, location);
  }
}


/* Creates a player.
 *
 * PRE:     Teams are initialized.
 * POST:    A player has been created, and added to a team.
 * PROGRAMMER:
 * RETURNS:
 * NOTES:   findPlayer
 */
void ServerGameLogic::createPlayer(int team_no, Point location, int client_id, int role)
{
  int uid = next_unit_id_++;

  Player *player = new Player(uid, client_id, location, role);
  player->setSpeed(5);
  player->team = team_no;
  teams[team_no].addUnit(player);
  std::cout << "adding player: " << player->clientID << " team: " << team_no << std::endl;
}
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
void ServerGameLogic::respawnPlayer(Player* player, Point location)
{
  player->position = location;
  player->health = 100;
  player->pendingDelete = false;
}
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
void ServerGameLogic::giveTeamBonus(int team_no, int amount)
{
  teams[team_no].currency += amount;
}
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
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
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
void ServerGameLogic::handlePlayerDeath(Player *player)
{
  // Respawn
  respawnPlayer(player, player->team == 0 ? gameMap_->team0start[0] : gameMap_->team1start[0]);

  // Give other team some monies
  giveTeamBonus(player->team == 0 ? 1 : 0, PLAYER_KILL_BONUS);  
}
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
void ServerGameLogic::handleCreepDeath(Creep *creep)
{
  // Remove creep
  teams[creep->team].removeUnit(creep);

  // Give other team some monies
  giveTeamBonus(creep->team == 0 ? 1 : 0, CREEP_KILL_BONUS);
}
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
void ServerGameLogic::handleTowerDeath(Tower *tower)
{
  // Remove tower
  teams[tower->team].removeUnit(tower);

  // Give other team some monies
  giveTeamBonus(tower->team == 0 ? 1 : 0, TOWER_KILL_BONUS);
}
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
void ServerGameLogic::handleCastleDeath()
{
  // Game over
  gameState_ = GAME_END;
}

// Returns the role given a playerID and team number;
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
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
/* 
 *
 * PRE:     
 * POST:    
 * PROGRAMMER:
 * RETURNS: 
 *          
 * NOTES: 
 */
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

  while (1)
    ;

}
#endif
