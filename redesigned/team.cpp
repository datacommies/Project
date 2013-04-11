#include "team.h"

/*------------------------------------------------------------------------------
-- FUNCTION:    addUnit
--
-- DATE:        2013/04/06
--
-- DESIGNER:    Dennis Ho
-- PROGRAMMER:  Dennis Ho
--
-- INTERFACE:   void Team::addUnit(Unit *unit)
--
-- RETURNS:    
--
-- DESCRIPTION: Allocates a unit and adds it to the team
------------------------------------------------------------------------------*/
void Team::addUnit(Unit *unit)
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

/*------------------------------------------------------------------------------
-- FUNCTION:    removeUnit
--
-- DATE:        2013/04/06
--
-- DESIGNER:    Dennis Ho
-- PROGRAMMER:  Dennis Ho
--
-- INTERFACE:   void Team::removeUnit(Unit *unit)
--
-- RETURNS:    
--
-- DESCRIPTION: Removes a unit from the team and deallocates it
------------------------------------------------------------------------------*/
void Team::removeUnit(Unit *unit)
{			
	std::vector<Unit*>::iterator it = find(units.begin(), units.end(), unit);

	if (it != units.end())
	{
		units.erase(it);		
	
		switch(unit->getType())
		{
			case CREEP:
				creeps.erase(find(creeps.begin(), creeps.end(), (Creep*)unit));
				break;
			case TOWER:
				towers.erase(find(towers.begin(), towers.end(), (Tower*)unit));
				break;
			case PLAYER:
				players.erase(find(players.begin(), players.end(), (Player*)unit));
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

	delete unit;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    isAlive
--
-- DATE:        2013/04/06
--
-- DESIGNER:    Dennis Ho
-- PROGRAMMER:  Dennis Ho
--
-- INTERFACE:   bool Team::isAlive() 
--
-- RETURNS:     true if team is alive, false otherwise
--
-- DESCRIPTION: Determines if the team is still alive
------------------------------------------------------------------------------*/
bool Team::isAlive() 
{ 
	return towers.size() > 0 && towers[0]->isAlive(); 
}

/*------------------------------------------------------------------------------
-- FUNCTION:    findUnit
--
-- DATE:        2013/04/06
--
-- DESIGNER:    Dennis Ho
-- PROGRAMMER:  Dennis Ho
--
-- INTERFACE:   Unit* Team::findUnit(int unitId)
--
-- RETURNS:     A pointer to the first unit matching the specified id.
--				NULL if not found
--
-- DESCRIPTION: Finds the specified unit within this team
------------------------------------------------------------------------------*/
Unit* Team::findUnit(int unitId)
{			
	for (std::vector<Unit*>::iterator it = units.begin(); it != units.end(); ++it)
		if ((*it)->id == unitId)
	  		return *it;

	return NULL;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    findPlayer
--
-- DATE:        2013/04/06
--
-- DESIGNER:    Dennis Ho
-- PROGRAMMER:  Dennis Ho
--
-- INTERFACE:   Player* Team::findPlayer(int clientId)
--
-- RETURNS:     A pointer to the first player matching the specified client Id
--				NULL if not found
--
-- DESCRIPTION: Finds the specified player within this team
------------------------------------------------------------------------------*/
Player* Team::findPlayer(int clientId)
{
	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it)
		if ((*it)->clientID == clientId)
	  		return *it;		
	  	
	return NULL;
}