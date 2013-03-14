/*
 * Basic tower attacks a single unit; default tower
 * - Basic implementation
*/
#include "basic_tower.h"
#include "unit.h"
#include <string>

using namespace std;

BasicTower::BasicTower(const int& uid, Point pos, const int& hp, const int& atkdmg, const int& atkrng,
            const int& atkspd, const int& percep, const int& atkcnt, const int& wall):
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
    
    // check if target is dead or in range (might have to call this at start of
    // function instead)
    CheckTarget();
}

