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
   
    //Player(int uid, Point pos, int hp, int atkdmg, int atkrng,
   //       int atkspd, int percep, int atkcnt, int spd, Direction direct,
    //      int cid);
	
    Player(int uid, int cid, Point pos, int role, int hp=200, int atkdmg=10, int atkrng=0,
          int atkspd=0, int percep=0, int atkcnt=0, int spd=0, Direction direct=STATIONARY, time_t tod=0);

    virtual UnitType getType() const { return PLAYER; }
	virtual size_t getSize() const { return MobileUnit::getSize(); }

	virtual std::string serializeMobileUnit() {
	    std::string s = Unit::serializeUnit();
	    
	    mobileunit_t m;
	    m.speed = moveSpeed;
	    m.direction = direction;
	    m.role = role;
	    s += std::string((char*)&m, sizeof(mobileunit_t));
	    return s;
	}

private:
};

#endif
