/*
 * Basic tower attacks a single unit; default tower
 * - Basic implementation
*/
#include "basic_tower.h"
#include "unit.h"
#include <string>

using namespace std;

BasicTower::BasicTower(int uid, Point pos, int hp, int atkdmg, int atkrng,
            int atkspd, int percep, int atkcnt, int wall):
            Tower(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, wall)
{
    //validation
}

void BasicTower::Attack(void)
{
    // check if we can attack
    if( attackCount++ < attackSpeed )
        return;
        
    attackCount = 0;
    pTarget->health -= attackDamage;
}

