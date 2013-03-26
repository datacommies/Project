#ifndef QUICK_TOWER_H
#define QUICK_TOWER_H

#include "tower.h"

class QuickTower : public Tower
{
public:

    QuickTower(int uid, Point pos, int hp, int atkdmg, int atkrng,
          int atkspd, int percep, int atkcnt, int wall);
    
    QuickTower(int uid, int side, Point pos, int hp, int atkdmg, int atkrng,
          int atkspd, int percep, int atkcnt, int wall);
    
virtual void Attack(void);
	
private:  
};

#endif
