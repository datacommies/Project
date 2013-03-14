#ifndef SPLASH_TOWER_H
#define SPLASH_TOWER_H

#include "tower.h"

class SplashTower : public Tower
{
public:

    SplashTower(int uid, Point pos, int hp, int atkdmg, int atkrng,
				int atkspd, int percep, int atkcnt, int wall);
    
    virtual void Attack(void);
	
private:  
};

#endif
