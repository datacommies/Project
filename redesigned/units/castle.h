#ifndef CASTLE_H
#define CASTLE_H

#include "../resource.h"
#include "../types.h"
#include "tower.h"

class Castle : public Tower
{
public:
    Castle(const int& uid. const Point& position, const int& hp, const int& range
           const int & speed const int& damage, const int& armour, const int& cid):
        clientID_(cid);

	std::string serializeCastle(const Castle& castle);

	virtual UnitTypes getType() const { return TYPE_CASTLE; }
	virtual size_t getSize() const { return sizeof(Castle); }

    int getCID(); //no setter, should only be set once at start of game

private:  
    int clientID_; 
};

#endif
