#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include "resource.h"
#include "units/player.h"
#include "units/creep.h"
#include "units/tower.h"
#include "units/projectile.h"

class Team
{
public:
	std::vector<Creep*> creeps;
	std::vector<Tower*> towers;
	std::vector<Player*> players;
	std::vector<Unit*> units;
	std::vector<PATH> paths;
	std::vector<Projectile*> projectiles;
	int currency;
	int teamId;

	void addUnit(Unit *unit)
	{
		units.push_back(unit);

		switch(unit->getType())
		{
			case CREEP:
				creeps.push_back((Creep*)unit);
				break;
			case TOWER:
				towers.push_back((Tower*)unit);
				break;
			case PLAYER:
				players.push_back((Player*)unit);
				break;
			case CREEP_ONE:
			case CREEP_TWO:
			case CREEP_THREE:
			case TOWER_ONE:
			case TOWER_TWO:        // added to remove warnings
			case TOWER_THREE:
			case CASTLE:
			case PROJECTILE:
				break;
		}   	
	}

	bool isAlive() { return towers.size() > 0 && towers[0]->isAlive(); }
private:
};

#endif
