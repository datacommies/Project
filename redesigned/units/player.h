#ifndef PLAYER_H
#define PLAYER_H

#include "../resource.h"
#include "../types.h"
#include "mobile_unit.h"

class Player : public MobileUnit
{
public:
    int clientID, role;
   
    //Player(int uid, Point pos, int hp, int atkdmg, int atkrng,
   //       int atkspd, int percep, int atkcnt, int spd, Direction direct,
    //      int cid);
	
    Player(int uid, int cid, Point pos, int role, int hp=100, int atkdmg=0, int atkrng=0,
          int atkspd=0, int percep=0, int atkcnt=0, int spd=0, Direction direct=STATIONARY);

    virtual UnitType getType() const { return PLAYER; }
	virtual size_t getSize() const { return MobileUnit::getSize(); }

private:
};

#endif
