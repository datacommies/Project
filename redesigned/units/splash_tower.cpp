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

void SplashTower::Attack(void)
{
    // check if we can attack
    if( attackCount++ < attackSpeed )
        return;
        
    attackCount = 0;
    pTarget->health -= attackDamage;
    /* check for nearby enemies & damage them
       for ( enemy units )
       {
           if ( in range )
           {
               damage unit
           }
       }
    */

    // check if target is dead or in range (might have to call this at start of
    // function instead)
    CheckTarget();
}
