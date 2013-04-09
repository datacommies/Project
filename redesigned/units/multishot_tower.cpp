/*------------------------------------------------------------------------------
-- FILE: multishot_tower.cpp
--
-- DATE: 2013/03/20
--
-- PROGRAMMER: Aiko Rose
--
-- FUNCTIONS: inRange
--            Attack
--
-- DESCRIPTION: MultiShotTower inherits from Tower.
--   	MultiShotTower can attack three units at once.
------------------------------------------------------------------------------*/
#include "multishot_tower.h"
#include "unit.h"
#include <string>
#include "../team.h"

using namespace std;

MultiShotTower::MultiShotTower(int uid, Point pos, int hp, int atkdmg, int atkrng,
int atkspd, int percep, int atkcnt, int wall, Team * t):
Tower(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, wall)
,team(t)
{
    //validation
}

/*------------------------------------------------------------------------------
-- FUNCTION: Attack
--
-- DATE: 2013/03/20
--
-- PROGRAMMER: Aiko Rose
--
-- INTERFACE: void Attack(void)
--
-- RETURNS: void
--
-- DESCRIPTION: Function damages three enemy units and players at once.
--  
-- 
------------------------------------------------------------------------------*/
void MultiShotTower::Attack(Team* team)
{
    /* check if we can attack */
    if(attackCount++ < attackSpeed)
        return;
    int j = 0;
    /* reset attackCount and damage pTargetd */
    attackCount = 0;

    /* check for nearby creeps & damage them */
    for (size_t i = 0; i < team->creeps.size(); ++i)
    {
        /* if creep is in range AND is alive AND is not our target (to prevent hitting one target twice) */
        if( inRange( pTarget->getPos(), team->creeps[i].getPos(), attackRange )
            && team->creeps[i].health > 0 && pTarget->id != team->creeps[i].id )
        {
            team->creeps[i].health -= attackDamage;
            j++;
        }
        if(j == 3)
            break;

    }
}
