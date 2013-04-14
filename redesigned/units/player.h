#ifndef PLAYER_H
#define PLAYER_H

#include "../resource.h"
#include "../types.h"
#include "mobile_unit.h"
#include <time.h>

class Player : public MobileUnit
{
public:
    int clientID, role;
    time_t tod;
   
    Player(int uid, int cid, Point pos, int role, int hp=200, int atkdmg=10, int atkrng=0,
          int atkspd=0, int percep=0, int atkcnt=0, int spd=0, Direction direct=STATIONARY, time_t tod=0);
    // returns the type PLAYER
    virtual UnitType getType() const { return PLAYER; }
    // return the size of a MobileUnit
	virtual size_t getSize() const { return MobileUnit::getSize(); }
	virtual std::string serializeMobileUnit();

private:
};

#endif
