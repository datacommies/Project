/*
 * Quick tower targets one unit and fires rapidly at it; Low damage tower.
 * - Basic implementation
*/
#include "quick_tower.h"
#include "unit.h"
#include <string>

using namespace std;

QuickTower::QuickTower(int uid, Point pos, int hp, int atkdmg, int atkrng,
            int atkspd, int percep, int atkcnt, int wall):
            Tower(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, wall)
{
    //validation
}

