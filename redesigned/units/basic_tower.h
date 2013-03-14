#ifndef BASIC_TOWER_H
#define BASIC_TOWER_H

#include "tower.h"

class BasicTower : public Tower
{
public:

    BasicTower(int uid, Point pos, int hp, int atkdmg, int atkrng,
          int atkspd, int percep, int atkcnt, int wall);
          
    virtual void Attack(void);

	
private:  
};

#endif
