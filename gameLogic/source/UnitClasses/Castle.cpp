#include "Castle.h"
using namespace std;

class Castle inherits from StaticUnit{

	Castle(int uID, int pID): unitID(uID), playerID_(pID){	// constructor initializes playerID_
		// set xPos and yPos
		cout << "Castle created. "
	}
	
	void run()
	{
		// 1) check for attacks from enemy units, adjust healthPoints if needed
		//		- how do we keep track of this?
		
		// 2) check castle's healthPoints, if zero then loses game
		if(isDead()){
			//call an endGame() or surrender() function
			cout << "End game." << endl;
		}
		
		// 3) check for user input (from Commander role) 
		if(there is input){
			//handle input such as build a tower or creeps
		}
		
		// 4) call updateServer()
		updateStats(struct castleStruct);
	}

	int buildTower(int x, int y, string typeTower)		
	{
		// 1) FIRST validate that the x, y position is valid and available on the game map ** 
		// 2) if resources available, generate unitID and build tower
		// 3) set teamID, typeTower, posX, posY, healthPoints, attack radius, damage and speed
		// 4) send all initial info on new unit to server
		// 5) if all successful, return 1, else return -1 and set error message
		// 6) adjust team resources as appropriate
		//	NOTE: For basic requirements, typeTower will default to "basic". Upgrades will later 
		//		provide possibility to upgrade towers using upgradeTower() function.
	}
	
	bool upgradeTower(int unitID, string typeTower)		// future option
	{
		// 1) if resources available and typeTower specified is a legitimate upgrade, change current
		//		typeTower to the newly specified one
		// 2) update attackRadius_, attackSpeed_ and attackDamage_ as per new type of unit
		// 3) if successful upgrade, return TRUE
		// 4) adjust team resources as appropriate
		// NOTE: updated info sent to server on regular update
	}
	
	int buildCreep(int lane, int num, string typeCreep)		
	{
		// 1) if resources available, generate unitID and build a creep "num" times (num default = 1)
		// 2) set teamID, typeCreep, posX, posY, healthPoints, attack attributes and movement speed
		// 3) send all initial info on new unit to server
		// 4) if all successful, return unitID
		// 5) adjust team resources as appropriate
		//	NOTE: For basic requirements, typeCreep will default to "basic". Upgrades will later 
		//		provide possibility to upgrade creeps using upgradeCreep() function.
	}
	
	bool upgradeCreep(int unitID, string typeCreep)		// future option
	{
		// 1) if resources available and typeCreep specified is a legitimate upgrade, change current
		//		typeCreep to the newly specified one
		// 2) update movementSpeed_ and other creep attributes as per new type of unit
		// 3) if successful upgrade, return TRUE
		// 4) adjust team resources as appropriate
		// NOTE: updated info sent to server on regular update
	}
	
	// another possible future option: upgradeCastle()
	//		could upgrade type &/or defenceStrength
	
	void setDefenceStrength(int ds)	// defence strength factor - future option
	{
		defenceStrength_ *= ds;	 	// increase or decrease by factor or %
	}
	
	int getDefenceStrength()		// future option
	{
		return defenceStrength_;	// return unit's current defenceStrength
	}
	
	int getPlayerID_()
	{
		return playerID_;	// return unit's human player's playerID
	}


}
