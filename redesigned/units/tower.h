#ifndef TOWER_H
#define TOWER_H

#include "../resource.h"
#include "../types.h"
#include "unit.h"


/*
    please fix this class so that it is using members
    inherited from it's base classes
    for example: unit has an ID, but you're creating another
    id in here

    there are so many of these :/
*/
class Tower : public Unit
{
private:
public:
    int wallArmour_; //reduces damage somehow?
    Tower(int uid, Point pos, int hp, int atkdmg, int atkrng,
          int atkspd, int percep, int atkcnt, int wall);
	
    Tower(int uid, int side, Point pos, int hp=100, int atkdmg=0, int atkrng=0,
          int atkspd=0, int percep=0, int atkcnt=0, int wall=0);
    std::string serializeTower();

    virtual UnitType getType() const { return CASTLE; }
	virtual size_t getSize() const { return Unit::getSize() + sizeof(tower_t); }
};
#endif

