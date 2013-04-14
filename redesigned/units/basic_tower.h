#ifndef BASIC_TOWER_H
#define BASIC_TOWER_H

#include "tower.h"

class BasicTower : public Tower
{
public:

    BasicTower(int uid, Point pos, int hp, int atkdmg, int atkrng,
          int atkspd, int percep, int atkcnt, int wall);

    BasicTower(int uid, int side, Point pos, int hp=100, int atkdmg=0, int atkrng=0,
          int atkspd=0, int percep=0, int atkcnt=0, int wall=0);
          
          
          
    virtual void Attack(void);

	
private:  
};

#endif
