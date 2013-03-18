/*
 * Quick tower targets one unit and fires rapidly at it; Low damage tower.
 * Essentially a faster firing version of basic tower.
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

void QuickTower::Attack(void)
{
    // check if we can attack
    if( attackCount++ < attackSpeed )
        return;
        
    attackCount = 0;
    pTarget->health -= attackDamage;
}
