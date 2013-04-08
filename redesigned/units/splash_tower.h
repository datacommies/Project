#ifndef SPLASH_TOWER_H
#define SPLASH_TOWER_H

#include "tower.h"


class SplashTower : public Tower
{
public:
    int    splashDamage;
    int    splashRange;  // Range in which we can damage other units   
    
    SplashTower(int uid, Point pos, int hp, int atkdmg, int atkrng,
				int atkspd, int percep, int atkcnt, int wall, int spldmg, int splrng);

    SplashTower(int uid, int side, Point pos, int hp, int atkdmg, int atkrng,
                int atkspd, int percep, int atkcnt, int wall, int spldmg, int splrng);
    
    virtual void Attack(Team * team);
    void Update(Team&);
	
private:  
};

#endif
