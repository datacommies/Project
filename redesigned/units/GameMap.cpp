/*------------------------------------------------------------------------------
-- FILE:        GameMap.cpp
--
-- DATE:        2013/04/07
--
-- MAINTAINERS: Callum Styan
--
-- FUNCTIONS:   initPaths
--              initCastlePositions
--              initPlayerPositions
--              initMap
--              _init
--              GameMap
--              min
--              max
--              printGrid
--              ~GameMap
--              isValidPos
--              _helperBuild
--              build
--              reset
--              addUnit
--              removeUnit
--              moveUnit
--              Malloc
--              getUnitFromId
--              getTeamNo
--              getUnit
--              main
--
-- DESCRIPTION: File contains implementation for the GameMap class.  This
--              contains all functions necessary for generating, initializing,
--              and updating the GameMap. 
------------------------------------------------------------------------------*/
#include "GameMap.h"
#include <cmath>

/*------------------------------------------------------------------------------
-- FUNCTION:    initPaths
--
-- DATE:        April 7, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   void GameMap::initPaths()
--
-- RETURNS:     void
--
-- DESCRIPTION: Gets the next point in the creeps path. If the next point is (-1, -1)
-- then the creeps next point it is to move to is not updated.  This means that
-- if the creep is at the last point in it's path it will not move.
------------------------------------------------------------------------------*/
void GameMap::initPaths(){
  //*** team 1 paths ***
  Point a;

  //top lane, left team
  a.x = 55; //castle icon is 25x25
  a.y = 15;
  topOne.push_back(a);
  a.x = 755;
  a.y = 15;
  topOne.push_back(a);
  a.x = 755;
  a.y = 455;
  topOne.push_back(a);
  a.x = -1;
  a.y = -1;
  topOne.push_back(a);

  // left team, bottom lanes
  a.x = 15;
  a.y = 55;
  botOne.push_back(a);
  a.x = 15;
  a.y = 555;
  botOne.push_back(a);
  a.x = 745;
  a.y = 555;
  botOne.push_back(a);
  a.x = -1;
  a.y = -1;
  botOne.push_back(a);


  // left team, mid lane
  for (int x = 40; x <= 800; x+=2)
    midOne.push_back(Point(x, round((double)x * MAP_Y/MAP_X)));
  midOne.push_back(Point(-1,-1));  

  //*** end of team 1 paths ***


  //*** team 2 paths *** RIGHT TEAM
  Point b;

  //top
  b.x = 765;
  b.y = 565;
  topTwo.push_back(b);
  b.x = 765;
  b.y = 15;
  topTwo.push_back(b);
  b.x = 55;
  b.y = 15;
  topTwo.push_back(b);
  b.x = -1;
  b.y = -1;
  topTwo.push_back(b);

  //bottom
  b.x = 745;
  b.y = 560;
  botTwo.push_back(b);
  b.x = 15;
  b.y = 560;
  botTwo.push_back(b);
  b.x = 15;
  b.y = 55;
  botTwo.push_back(b);
  b.x = -1;
  b.y = -1;
  botTwo.push_back(b);

  //middle
  for (int x = 795; x >= 0; x-=2)
    midTwo.push_back(Point(x, round((double)x * MAP_Y/MAP_X)));
  midTwo.push_back(Point(-1,-1));  
  //*** end of team 2 paths ***    
}

/*------------------------------------------------------------------------------
-- FUNCTION:    initCastlePositions
--
-- DATE:        April 7, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   void GameMap::initCastlePositions()
--
-- RETURNS:     void
--
-- DESCRIPTION: Initializes the positions of the castles for both teams.
------------------------------------------------------------------------------*/
void GameMap::initCastlePositions(){
    //team 1 castle position, top left corner
    castle1.x = 0;
    castle1.y = 0;

    //team 2 castle position, bottom right corner
    castle2.x = MAP_X - 50;
    castle2.y = MAP_Y - 55;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    initPlayerPositions
--
-- DATE:        April 7, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   void GameMap::initPlayerPositions()
--
-- RETURNS:     void
--
-- DESCRIPTION: Initializes the positions of the players for both teams.
------------------------------------------------------------------------------*/
void GameMap::initPlayerPositions(){
    //*** team 1 player starting positions ***
    Point c;
    c.x = 55;
    c.y = 55;

    team0start[0] = c;

    c.x = 12;
    c.y = 10;

    team0start[1] = c;

    c.x = 14;
    c.y = 8;

    team0start[2] = c;

    c.x = 16;
    c.y = 8;

    team0start[3] = c;
    //*** end of team 1 starting positions ***

    //*** team 2 player starting positions ***
    c.x = 725;
    c.y = 525;

    team1start[0] = c;

    c.x = 580;
    c.y = 680;

    team1start[1] = c;

    c.x = 580;
    c.y = 490;

    team1start[2] = c;

    c.x = 490;
    c.y = 480;

    team1start[3] = c;
    //*** end of team 2 starting positions ***
}

/*------------------------------------------------------------------------------
-- FUNCTION:    initMap
--
-- DATE:        April 7, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   void GameMap::initMap()
--
-- RETURNS:     void
--
-- DESCRIPTION: Initializes the map.  This is done by initializing the paths,
--              player positions, and castle positions.
------------------------------------------------------------------------------*/
void GameMap::initMap(){
    initPaths();
    initPlayerPositions();
    initCastlePositions();
}  

/*------------------------------------------------------------------------------
-- FUNCTION:    _init
--
-- DATE:        April 7, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   void GameMap::_init()
--
-- RETURNS:     void
--
-- DESCRIPTION: Allocates space for the grid_ container, iterates through the
--              container allocating space for each position, and initializes
--              the memory at each position to 0.
------------------------------------------------------------------------------*/
void GameMap::_init() {

  grid_ = (Unit***) Malloc(sizeof(Unit**) * max_x_ + 1);

  for ( int x=0; x <= max_x_; x++) {
    grid_[x] = (Unit**) Malloc(sizeof(Unit*) * max_y_ + 1);
    memset(grid_[x], 0, sizeof(Unit*) * max_y_ + 1);
  }
}

/*------------------------------------------------------------------------------
-- FUNCTION:    GameMap
--
-- DATE:        April 7, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   GameMap::GameMap(int max_x, int max_y): max_x_(max_x), max_y_(max_y)
--
-- RETURNS:     none
--
-- DESCRIPTION: GameMap object constructor.  Takes a maximum x and y value,
--              and calls the _init function to allocate a gride.
------------------------------------------------------------------------------*/
GameMap::GameMap(int max_x, int max_y): max_x_(max_x), max_y_(max_y) {
  _init();
}

int GameMap::min(int a, int b) 
{
  return a < b ? a : b;
}

int GameMap::max(int a, int b) 
{
  return a > b ? a : b;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    printGrid
--
-- DATE:        April 7, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   void GameMap::printGrid()
--
-- RETURNS:     void
--
-- DESCRIPTION: Utility function to test that the grid is allocating and
---             populating correctly; not used as part of normal game operation.
------------------------------------------------------------------------------*/
void GameMap::printGrid() {

  int x, y;
  for (y=0; y<=max_y_; y++) {
    for (x=0; x<=max_x_; x++) {
      
	if (grid_[x][y] == NULL) 
	   printf("  . ");
	else
	   printf(" %2d ", grid_[x][y]->id);

    }
    printf("\n");
  }
}

/*------------------------------------------------------------------------------
-- FUNCTION:    ~GameMap
--
-- DATE:        April 7, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   void GameMap::~GameMap()
--
-- RETURNS:     none
--
-- DESCRIPTION: GameMap object destructor.  Frees allocated memory at each
--              location within the grid_ container, then frees the memory
--              allocated for the grid_ container itself.
------------------------------------------------------------------------------*/
GameMap::~GameMap() {

  for (int x=0; x<= max_x_; x++)
    free (grid_[x]);

  free(grid_);
}

/*------------------------------------------------------------------------------
-- FUNCTION:    isValidPos
--
-- DATE:        April 7, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   bool GameMap::isValidPos(Point pos)
--
-- RETURNS:     Boolean; whether or not the position provided is valid
--
-- DESCRIPTION: This function determines whether or not the position provided
--              as a parameter is valid, then returns the result of this check.
------------------------------------------------------------------------------*/
bool GameMap::isValidPos(Point pos)
{

  return (pos.x >= 0 && pos.x <= max_x_) && (pos.y >= 0 && pos.y <= max_y_);
}

/*------------------------------------------------------------------------------
-- FUNCTION:    _helperBuild
--
-- DATE:        April 7, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   void GameMap::_helperBuild(Unit *unit, UnitType type,
--                                          Point pos, int team_no)
--
-- RETURNS:     void
--
-- DESCRIPTION: This function is a wrapper for building a unit.  It checks if
--              the specified location is valid.  If it is not, it logs an
--              error message.  If the position is valid, the units_ container
--              for the appropriate unit ID is updated with the unit position,
--              the location in the grid_ container for the specified position
--              is updated with the Unit object provided, and the unit's team
--              is set to the specified team number.
------------------------------------------------------------------------------*/
void GameMap::_helperBuild(Unit *unit, UnitType type, Point pos, int team_no) {

  if (!isValidPos(pos)) {
    fprintf(stderr, "Invalid position x: %d y: %d %s line %d\n", pos.x, pos.y, __FILE__, __LINE__);
    return;
  }        

  units_[unit->id] = pos;
  grid_[pos.x][pos.y] = unit;
   
  // set team_no since in case it wasn't done already
  unit->team = team_no;
}
/*------------------------------------------------------------------------------
-- FUNCTION:    build
--
-- DATE:        April 7, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   void GameMap::build(Team teams[])
--
-- RETURNS:     void
--
-- DESCRIPTION: This function iterates through the Creep, Tower and Player
--              containers, and calls the _helperBuild function for each
--              object within these containers with the appropriate values.
------------------------------------------------------------------------------*/
void GameMap::build(Team teams[]) {

  int totalTeams = 2;
  reset();

  for (int i=0; i<totalTeams; i++) {

    int team_no = i;

    for (std::vector<Creep*>::iterator it = teams[i].creeps.begin(); it != teams[i].creeps.end(); ++it)
      _helperBuild( *it, CREEP, (*it)->getPos(), team_no);

    for (std::vector<Tower*>::iterator it = teams[i].towers.begin(); it != teams[i].towers.end(); ++it)
      _helperBuild(*it, TOWER, (*it)->getPos(), team_no);


    for (std::vector<Player*>::iterator it = teams[i].players.begin(); it != teams[i].players.end(); ++it)
      _helperBuild(*it, PLAYER, (*it)->getPos(), team_no);

  }
}

/*------------------------------------------------------------------------------
-- FUNCTION:    reset
--
-- DATE:        April 7, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   void GameMap::reset()
--
-- RETURNS:     void
--
-- DESCRIPTION: This function zeroes out all positions within the grid_ container,
--              and removes all entries from the units_ container.
------------------------------------------------------------------------------*/
void GameMap::reset() {
  // Zero memory
  for (int x=0; x<=max_x_; x++)
    memset(grid_[x], 0, sizeof(Unit*) * max_y_ + 1);

  units_.clear();
} 

/*------------------------------------------------------------------------------
-- FUNCTION:    addUnit
--
-- DATE:        April 7, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   void GameMap::addUnit(Unit *unit, Point pos)
--
-- RETURNS:     void
--
-- DESCRIPTION: This function adds a specified unit to the grid_ container at the
--              specified position if there is no object occupying this space
--              previously.
------------------------------------------------------------------------------*/
void GameMap::addUnit(Unit *unit, Point pos)
{
  if (grid_[pos.x][pos.y] == NULL)
  {
    grid_[pos.x][pos.y] = unit;
    units_[unit->id] = pos;
  }
}

/*------------------------------------------------------------------------------
-- FUNCTION:    removeUnit
--
-- DATE:        April 7, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   void GameMap::removeUnit(Unit *unit)
--
-- RETURNS:     void
--
-- DESCRIPTION: This function removes the specified unit from the units_
--              container.
------------------------------------------------------------------------------*/
void GameMap::removeUnit(Unit *unit) 
{
  std::map<int, Point>::iterator it;

  it = units_.find(unit->id);
  if (it != units_.end()) {

    Point old_pos;
    old_pos = units_[unit->id];
    grid_[old_pos.x][old_pos.y] = NULL;

    units_.erase(it);
  }
}

/*------------------------------------------------------------------------------
-- FUNCTION:    moveUnit
--
-- DATE:        April 7, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   void GameMap::moveUnit(Unit *unit, Point new_pos)
--
-- RETURNS:     void
--
-- DESCRIPTION: This function moves a specified unit to a new position.         
------------------------------------------------------------------------------*/
void GameMap::moveUnit(Unit *unit, Point new_pos)
{
  std::map<int, Point>::iterator it;

  it = units_.find(unit->id);
  if (it != units_.end())
  {
    Point old_pos;
    old_pos = units_[unit->id];
    grid_[old_pos.x][old_pos.y] = NULL;
  }

  grid_[new_pos.x][new_pos.y] = unit;
  units_[unit->id] = new_pos;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    Malloc
--
-- DATE:        April 7, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   void * GameMap::Malloc(size_t size)
--
-- RETURNS:     void *; A pointer to the newly allocated memory.
--
-- DESCRIPTION: This is a wrapper for Malloc, and prints and error message if
--              malloc() returns a NULL pointer.  It then returns the pointer
--              returned by malloc() regardless of success or failure.       
------------------------------------------------------------------------------*/
void * GameMap::Malloc(size_t size) {

  void * p;

  p = malloc(size);

  if (p == NULL)
    fprintf(stderr, "Error calling malloc in %s line %d\n", __FILE__, __LINE__);

  return p;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    getUnitFromId
--
-- DATE:        April 7, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   Unit *GameMap::getUnitFromId(int id)
--
-- RETURNS:     Unit *; A pointer to the unit with the specified ID.
--
-- DESCRIPTION: This function finds the Unit within the units_ container with
--              the ID specified, and returns a pointer to said unit.   
------------------------------------------------------------------------------*/
Unit *GameMap::getUnitFromId(int id)
{
	Unit *unit;

	std::map<int, Point>::iterator it;
	it = units_.find(id);
	
	unit = NULL;
	if (it != units_.end())
  {
		Point pos = it->second;
		unit = grid_[pos.x][pos.y];
	}

	return unit;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    getTeamNo
--
-- DATE:        April 7, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   int GameMap::getTeamNo(int id) 
--
-- RETURNS:     int; The team number of the specified unit.
--
-- DESCRIPTION: This function locates the unit from the units_ container with
--              the specified ID, and returns which team this unit is on.
------------------------------------------------------------------------------*/
int GameMap::getTeamNo(int id)
{
   Unit *unit;
   unit = getUnitFromId(id);

   if (unit == NULL)
	   return TEAM_NOT_FOUND;
   else
     return unit->team;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    getUnit
--
-- DATE:        April 7, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   Unit *GameMap::getUnit(Point pos)
--
-- RETURNS:     Unit *; A pointer to the unit at the specified position.
--
-- DESCRIPTION: This function determines which, if any, unit is present at the
--              specified location, and returns a pointer to said unit if one
--              is located, and a NULL pointer otherwise.
------------------------------------------------------------------------------*/
Unit *GameMap::getUnit(Point pos)
{
  if (!isValidPos(pos))
    return NULL;

  return grid_[pos.x][pos.y];

  // You should use something like this :D - Jesse
  // return (!isValidPos(pos)) ? NULL : grid_[pos.x][pos.y];
}


#ifdef TEST_MAP  
// Test with: g++ GameMap.cpp -DTEST_MAP -g -Wall ../build/units/tower.o ../build/units/unit.o

#include <vector>
#include "tower.h"

int main()
{
	GameMap the_map(10, 10);

	std::vector<Unit*> units;


	// Test add unit
	
	for (int i=0; i<3; i++) {
		
		Point pos;
		pos.x = i;
		pos.y = i;
		
		Tower *tower = new Tower(i, i, pos, i, i, i, i, i, i, i);
		units.push_back(tower);
		
		the_map.addUnit(tower, pos);
		
	}

	
	printf("Test add unit to the map.\n");
	the_map.printGrid();


	// Test move unit
	printf("Test moving units to the right by 2.\n");
	printf("and down by 3.\n");
	for (std::vector<Unit*>::iterator it = units.begin(); it != units.end(); ++it) {
		
		Point pos;
		
		Unit *unit = *it;

		pos = unit->getPos();
		pos.x += 2;
		pos.y += 3;

		the_map.moveUnit(unit, pos);

	}
	the_map.printGrid();

	// Test removing from the map
	for (std::vector<Unit*>::iterator it = units.begin(); it != units.end(); ++it) {

		the_map.removeUnit(*it);
	}

	printf("Test removing units from the map\n");
	the_map.printGrid();


}
#endif
