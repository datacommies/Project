#ifndef TOWER_H
#define TOWER_H

#include "../resource.h"
#include "../types.h"
#include "unit.h"

class Tower : public Unit
{
public:
   int getWallArmor() { return wallArmor_; }
   bool setWallArmor(const int& amount) { wallArmor_ = amount; }
   std::string serializeTower(const Tower& tower);

	virtual UnitTypes getType() const { return TYPE_TOWER; }
	virtual size_t getSize() const { return sizeof(Tower); }
	
private: 
   int wallArmor_;
};

#endif
