#ifndef CASTLE_H
#define CASTLE_H

#include "Unit.h"
#include "Static.h"

class Castle: public StaticUnit {
public:
	explicit Castle(u_int id);
	void run(); 
	int buildTower(int x, int y, string typeTower);
	int buildCreep(int lane, int num, string typeCreep);
	bool upgradeTower(int unitID, string typeTower);
	bool upgradeCreep(int unitID, string typeCreep);
	void setDefenceStrength(int ds);
	int getDefenceStrength();
	int getPlayerID_();

private:
	int playerID_;			// id for human player in this Castle/Commander role
	int defenceStrength_;	// future option - strength multiplier, start at 1.0 or 100%
};

#endif