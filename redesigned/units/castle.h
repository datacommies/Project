#ifndef CASTLE_H
#define CASTLE_H

#include "../resource.h"
#include "../types.h"
#include "tower.h"

class Castle : public Tower
{
public:
    int clientID_; //id of the client/player, likely the socket #

    Castle(int uid, Point pos, int hp, int atkdmg, int atkrng,
        int atkspd, int percep, int atkcnt, int wall, int cid);

    Castle(int uid, int cid, int side, Point pos, int hp=100, int atkdmg=0, 
        int atkrng=0, int atkspd=0, int percep=0, int atkcnt=0, int wall=0);

	virtual UnitType getType() const { return CASTLE; }
	virtual size_t getSize() const { return Tower::getSize(); }

    int getCID() const { return clientID_; } //no setter, should only be set once at start of game

private:  
};

#endif
