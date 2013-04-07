#include "GameMap.h"


void GameMap::initMap(){
    //team 1 castle position, top left corner
    castle1.x = 0;
    castle1.y = 0;

    //team 2 castle position, bottom right corner
    castle2.x = 500;
    castle2.y = 500;

    //*** team 1 paths ***
    Point a;

    a.x = 30; //castle icon is 25x25
    a.y = 0;
    topOne.push_back(a);
    a.x = 500;
    a.y = 0;
    topOne.push_back(a);
    a.x = 500;
    a.y = 470;
    topOne.push_back(a);

    a.x = 0;
    a.y = 30;
    botOne.push_back(a);
    a.x = 0;
    a.y = 500;
    botOne.push_back(a);
    a.x = 470;
    a.y = 500;
    botOne.push_back(a);

    a.x = 30;
    a.y = 30;
    midOne.push_back(a);
    a.x = 250;
    a.y = 250;
    midOne.push_back(a);
    a.x = 470;
    a.y = 470; 
    midOne.push_back(a);
    //*** end of team 1 paths ***


    //*** team 2 paths ***
    Point b;

    b.x = 500;
    b.y = 470;
    topTwo.push_back(b);
    b.x = 500;
    b.y = 0;
    topTwo.push_back(b);
    b.x = 30;
    b.y = 0;
    topTwo.push_back(b);

    b.x = 470;
    b.y = 500;
    botTwo.push_back(b);
    b.x = 0;
    b.y = 500;
    botTwo.push_back(b);
    b.x = 0;
    b.y = 30;
    botTwo.push_back(b);

    b.x = 470;
    b.y = 470;
    midTwo.push_back(b);
    b.x = 250;
    b.y = 250;
    midTwo.push_back(b);
    b.x = 30;
    b.y = 30;
    midTwo.push_back(b);
    //*** end of team 2 paths ***

    //*** team 1 player starting positions ***
    Point c;
    c.x = 10;
    c.y = 10;

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
    c.x = 490;
    c.y = 490;

    team1start[0] = c;

    c.x = 480;
    c.y = 480;

    team1start[1] = c;

    c.x = 480;
    c.y = 490;

    team1start[2] = c;

    c.x = 490;
    c.y = 480;

    team1start[3] = c;
    //*** end of team 2 starting positions ***
}   
	void GameMap::_init() {

		grid_ = (Unit***) Malloc(sizeof(Unit**) * max_x_ + 1);

		for ( int x=0; x <= max_x_; x++) {
			grid_[x] = (Unit**) Malloc(sizeof(Unit*) * max_y_ + 1);
			memset(grid_[x], 0, sizeof(Unit*) * max_y_ + 1);
		}
	}

	GameMap::GameMap(int max_x = MAX_X, int max_y = MAX_Y): max_x_(max_x), max_y_(max_y) {
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

	/*
	 * This merges two maps together. eg, both = GameLogicMap(map1, map2);
	 */
	GameMap::GameMap(GameMap& map1, GameMap& map2)
		: max_x_(max(map1.max_x_, map2.max_x_)), max_y_(max(map1.max_y_, map2.max_y_))
	{
		_init();
		merge(map1, map2);
	}

	void GameMap::merge(GameMap& map1, GameMap& map2)
	{

		reset ();
		int x, y;

		// Okay, yes, I know, in this game, both maps will be the same size....
		int min_x = min(map1.max_x_, map2.max_x_);
		int min_y = min(map1.max_y_, map2.max_y_);

		// add units_s together ...
		for(std::map<Unit*, Point>::const_iterator it = map1.units_.begin(), it_end = map1.units_.end(); it != it_end; ++it)
			units_.insert(*it);
		for(std::map<Unit*, Point>::const_iterator it = map2.units_.begin(), it_end = map2.units_.end(); it != it_end; ++it)
			units_.insert(*it);

		// add grid_s together
		for (x=0; x<=min_x; x++)
			for (y=0; y<=min_y; y++) {

				if (map1.grid_[x][y] != 0 && map2.grid_[x][y] != 0) {
					fprintf(stderr, "!!!Error..more than one object occuping the same space!!! %s line: %d\n", __FILE__, __LINE__);
				}

				grid_[x][y] = map1.grid_[x][y] != NULL ? map1.grid_[x][y] : map2.grid_[x][y];
			}
	}

	// I write this so that I might be able to see if things work correctly
	void GameMap::printGrid() {

		int x, y;
		for (y=0; y<=max_y_; y++) {
			for (x=0; x<=max_x_; x++)
				printf("%2d ", grid_[x][y]->id);
			printf("\n");
		}
	}

	GameMap::~GameMap() {

		for (int x=0; x<= max_x_; x++)
			free (grid_[x]);

		free(grid_);
	}

	bool GameMap::isValidPos(Point pos)
	{

		//fprintf(stderr, "isValidPos(): max x: %d, max y: %d\n", max_x_, max_y_);


		return (pos.x >= 0 && pos.x <= max_x_) && (pos.y >= 0 && pos.y <= max_y_);
	}

	void GameMap::_helperBuild(Unit *unit, UnitType type, Point pos) {

		if (!isValidPos(pos)) {
			fprintf(stderr, "Invalid position x: %d y: %d %s line %d\n", pos.x, pos.y, __FILE__, __LINE__);
			return;
		}        

		units_[unit] = pos;
		grid_[pos.x][pos.y] = unit;
	}

	// This builds everything based on the Team class
	void GameMap::build(Team &team) {

		reset();

		for (std::vector<Creep*>::iterator it = team.creeps.begin(); it != team.creeps.end(); ++it)
			_helperBuild(*it, CREEP, (*it)->getPos());

		for (std::vector<Tower*>::iterator it = team.towers.begin(); it != team.towers.end(); ++it) {
			_helperBuild(*it, TOWER, (*it)->getPos());
		}

		for (std::vector<Player*>::iterator it = team.players.begin(); it != team.players.end(); ++it) {
			_helperBuild(*it, PLAYER, (*it)->getPos());
		}
	}

	void GameMap::build(Team teams[], size_t size) {

		reset();

		for (size_t i=0; i<size; i++) {

			for (std::vector<Creep*>::iterator it = teams[i].creeps.begin(); it != teams[i].creeps.end(); ++it)
				_helperBuild( *it, CREEP, (*it)->getPos());

			for (std::vector<Tower*>::iterator it = teams[i].towers.begin(); it != teams[i].towers.end(); ++it)
				_helperBuild(*it, TOWER, (*it)->getPos());


			for (std::vector<Player*>::iterator it = teams[i].players.begin(); it != teams[i].players.end(); ++it)
				_helperBuild(*it, PLAYER, (*it)->getPos());
			
		}
	}

	void GameMap::reset() {
		// Zero memory
		for (int x=0; x<=max_x_; x++)
			memset(grid_[x], 0, sizeof(Unit*) * max_y_ + 1);

		units_.clear();
	} 

	void GameMap::addUnit(Unit *unit, Point pos) {
		
		if (grid_[pos.x][pos.y] == NULL)
		{
			grid_[pos.x][pos.y] = unit;
			units_[unit] = pos;

		}

	}

	void GameMap::removeUnit(Unit *unit) {

		std::map<Unit*, Point>::iterator it;

		it = units_.find(unit);
		if (it != units_.end()) {
		
			Point old_pos;
			old_pos = units_[unit];
			grid_[old_pos.x][old_pos.y] = NULL;


			units_.erase(it);
		}
	}
	
	void GameMap::moveUnit(Unit *unit, Point new_pos) {
			
		std::map<Unit*, Point>::iterator it;

		it = units_.find(unit);
		if (it != units_.end()) {
		
			Point old_pos;
			old_pos = units_[unit];
			grid_[old_pos.x][old_pos.y] = NULL;
		}
			
		grid_[new_pos.x][new_pos.y] = unit;
		units_[unit] = new_pos;
	}

	void * GameMap::Malloc(size_t size) {

		void * p;

		p = malloc(size);

		if (p == NULL)
			fprintf(stderr, "Error calling malloc in %s line %d\n", __FILE__, __LINE__);

		return p;
	}

#ifdef TEST_MAP  
int main() {



}
#endif

