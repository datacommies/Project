#ifndef CASTLE_H
#define CASTLE_H

#include "StaticUnit.h"

class Castle: public StaticUnit {
public:
	Castle(const int& teamID, const int& hp, const int& xPos, const int& yPos, const int& playerID);

	virtual void Run(); 
	int buildTower(int x, int y, int typeTower);
	int buildCreep(int lane, int num, int typeCreep);
	bool upgradeTower(int unitID, int typeTower);
	bool upgradeCreep(int unitID, int typeCreep);
	int getPlayerID_();



private:
	int playerID_;			// id for human player in this Castle/Commander role
};

#endif