#ifndef BASIC_TOWER_H
#define BASIC_TOWER_H

#include "tower.h"

class BasicTower : public Tower
{
public:

    BasicTower(const int& uid, Point pos, const int& hp, const int& atkdmg, const int& atkrng,
          const int& atkspd, const int& percep, const int& atkcnt, const int& wall);

	
private:  
};

#endif
