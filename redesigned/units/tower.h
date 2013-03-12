#ifndef TOWER_H
#define TOWER_H

#include "../resource.h"
#include "../types.h"
#include "unit.h"

class Tower : public Unit
{
public:
    int wallArmour_;

    Tower(const int& uid, const int& pos, const int& hp, const int& atkdmg, const int& atkrng,
          const int& atkspd, const int& percep, const int& atkcnt, const int& wall);

    int getWallArmour() { return wallArmour_; }
    bool setWallArmour(const int& amount) { wallArmour_ = amount; }
    std::string serializeTower(const Tower& tower);

    virtual UnitTypes getType() const { return TYPE_TOWER; }
	virtual size_t getSize() const { return sizeof(Tower); }
	
private:  
};

#endif
