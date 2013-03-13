#ifndef CASTLE_H
#define CASTLE_H

#include "../resource.h"
#include "../types.h"
#include "tower.h"

class Castle : public Tower
{
public:
    int clientID_; 

    Castle(const int& uid, Point pos, const int& hp, const int& atkdmg, const int& atkrng,
           const int& atkspd, const int& percep, const int& atkcnt, const int& wall, const int& cid);

	std::string serializeCastle();

	virtual UnitTypes getType() const { return TYPE_CASTLE; }
	virtual size_t getSize() const { return Tower::getSize(); }

    int getCID() const { return clientID_; } //no setter, should only be set once at start of game

private:  
};

#endif
