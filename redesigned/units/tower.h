#ifndef TOWER_H
#define TOWER_H

#include "../resource.h"
#include "unit.h"

class Tower : public Unit
{
public:
   int getWallArmor() { return wallArmor_; }
   bool setWallArmor(const int& amount) { wallArmor_ = amount; }
   void serializeTower(const Tower& tower);
private: 
   int wallArmor_;
};

#endif
