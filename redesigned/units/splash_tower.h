#ifndef SPLASH_TOWER_H
#define SPLASH_TOWER_H

#include "tower.h"


class SplashTower : public Tower
{
public:
    Team * team;            // other team for splash damage calculations
    int    splashDamage;
    int    splashRange;  // Range in which we can damage other units   
    
    SplashTower(int uid, Point pos, int hp, int atkdmg, int atkrng,
				int atkspd, int percep, int atkcnt, int wall, Team * t,
				int spldmg, int splrng);
    
    virtual void Attack(void);
	
private:  
};

#endif
