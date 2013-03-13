#ifndef QUICK_TOWER_H
#define QUICK_TOWER_H

#include "tower.h"

class QuickTower : public Tower
{
public:

    QuickTower(const int& uid, Point pos, const int& hp, const int& atkdmg, const int& atkrng,
          const int& atkspd, const int& percep, const int& atkcnt, const int& wall);

	
private:  
};

#endif
