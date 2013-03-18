#ifndef CASTLE_H
#define CASTLE_H

#include "../resource.h"
#include "../types.h"
#include "tower.h"

class Castle : public Tower
{
public:
    int clientID_; 

    Castle(int uidzz, Point pos, int hp, int atkdmg, int atkrng,
           int atkspd, int percep, int atkcnt, int wall, int cid);

	virtual UnitType getType() const { return CASTLE; }
	virtual size_t getSize() const { return Tower::getSize(); }

    int getCID() const { return clientID_; } //no setter, should only be set once at start of game

private:  
};

#endif
