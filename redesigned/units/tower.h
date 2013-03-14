#ifndef TOWER_H
#define TOWER_H

#include "../resource.h"
#include "../types.h"
#include "unit.h"

class Tower : public Unit
{
public:
    int wallArmour_;

    Tower(int uid, Point pos, int hp, int atkdmg, int atkrng,
          int atkspd, int percep, int atkcnt, int wall);

    int getWallArmour() { return wallArmour_; }
    void setWallArmour(const int& amount) { wallArmour_ = amount; }
    std::string serializeTower();

    virtual UnitType getType() const { return CASTLE; }
	virtual size_t getSize() const { return Unit::getSize() + sizeof(tower_t); }
	
private:  
};

#endif
