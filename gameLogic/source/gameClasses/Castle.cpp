#include "Castle.h"
#include <iostream>
using namespace std;


Castle::Castle(const int& teamID, const int& hp, const int& xPos, const int& yPos, const int& playerID): StaticUnit(teamID, hp, xPos, yPos), playerID_(playerID){
		cout << "Castle created for Team " << teamID << endl;
	}
	
void Castle::Run()
{
	// 1) check for attacks from enemy units, adjust healthPoints if needed
	//		- how do we keep track of this?
	
	// 2) check castle's healthPoints, if zero then loses game
	if(isDead()){
		//call an endGame() or surrender() function
		cout << "End game." << endl;
	}
	
	// 3) check for user input (from Commander role) 
	//if(there is input){
		//handle input such as build a tower or creeps
	//}
	
	// 4) call updateServer()
	//updateStats(struct castleStruct);
}

int Castle::buildTower(int x, int y, int typeTower)		
{
	cout << "Building tower at position " << x << ", " << y << endl;
	// 1) FIRST validate that the x, y position is valid and available on the game map ** 
	// 2) if resources available, generate unitID and build tower
	// 3) set teamID, typeTower, posX, posY, healthPoints, attack radius, damage and speed
	// 4) send all initial info on new unit to server
	// 5) if all successful, return 1, else return -1 and set error message
	// 6) adjust team resources as appropriate
	//	NOTE: For basic requirements, typeTower will default to "basic". Upgrades will later 
	//		provide possibility to upgrade towers using upgradeTower() function.
}

bool Castle::upgradeTower(int unitID, int typeTower)		// future option
{
	cout << "Upgrading tower" << endl;
	// 1) if resources available and typeTower specified is a legitimate upgrade, change current
	//		typeTower to the newly specified one
	// 2) update attackRadius_, attackSpeed_ and attackDamage_ as per new type of unit
	// 3) if successful upgrade, return TRUE
	// 4) adjust team resources as appropriate
	// NOTE: updated info sent to server on regular update
}

int Castle::buildCreep(int lane, int num, int typeCreep)		
{
	cout << "Building creep in lane " << lane << endl;
	// 1) if resources available, generate unitID and build a creep "num" times (num default = 1)
	// 2) set teamID, typeCreep, posX, posY, healthPoints, attack attributes and movement speed
	// 3) send all initial info on new unit to server
	// 4) if all successful, return unitID
	// 5) adjust team resources as appropriate
	//	NOTE: For basic requirements, typeCreep will default to "basic". Upgrades will later 
	//		provide possibility to upgrade creeps using upgradeCreep() function.
}

bool Castle::upgradeCreep(int unitID, int typeCreep)		// future option
{
	cout << "Upgrading creep" << endl;
	// 1) if resources available and typeCreep specified is a legitimate upgrade, change current
	//		typeCreep to the newly specified one
	// 2) update movementSpeed_ and other creep attributes as per new type of unit
	// 3) if successful upgrade, return TRUE
	// 4) adjust team resources as appropriate
	// NOTE: updated info sent to server on regular update
}

int Castle::getPlayerID_()
{
	return playerID_;	// return unit's human player's playerID
}

/* To test to see if this class compiles type:
 * g++ -Wall -DTESTCOMPILE Castle.cpp */
#ifdef TESTCOMPILE

int main() {
    return 0;
}

#endif
