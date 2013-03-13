/*
 * Splash Damage tower attacks single unit and damage spreads to nearby units
 * - Basic implementation
*/
#include "splash_tower.h"
#include "unit.h"
#include <string>

using namespace std;

SplashTower::SplashTower(	int uid, Point pos, int hp, int atkdmg, int atkrng,
							int atkspd, int percep, int atkcnt, int wall):
				Tower(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, wall)
{
    //validation
}

