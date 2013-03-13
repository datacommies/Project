#ifndef SPLASH_TOWER_H
#define SPLASH_TOWER_H

#include "tower.h"

class SplashTower : public Tower
{
public:

    SplashTower(const int& uid, Point pos, const int& hp, const int& atkdmg, const int& atkrng,
          const int& atkspd, const int& percep, const int& atkcnt, const int& wall);

	
private:  
};

#endif
