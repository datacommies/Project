#ifndef STATICUNIT_H
#define STATICUNIT_H

#include "Unit.h"

class StaticUnit: public Unit {
public:
	StaticUnit(const int& teamID, const int& hp, const int& xPos, const int& yPos):
		Unit(teamID, hp, xPos, yPos){
			// initialize here if needed
	}

	void setDefenceStrength(const int& ds){
		defenceStrength_ = ds;
	}
	
	int getDefenceStrength(){
		return defenceStrength_;
	}
	
	virtual void Run(){
        //unit.Run()
    }

private:
	int defenceStrength_;	// strength multiplier, start at 1.0 or 100%
};

#endif