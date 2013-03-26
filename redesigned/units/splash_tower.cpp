/*------------------------------------------------------------------------------
-- FILE:        splash_tower.cpp
--
-- DATE:        2013/03/12
--
-- MAINTAINERS: Cody Rossiter
--
-- FUNCTIONS:   Attack
--
-- DESCRIPTION: File contains implementation for the SplashTower class.
--              SplashTower inherits from Tower.
--              SplashTower attacks a single unit and damage spreads to nearby
--              units. 
------------------------------------------------------------------------------*/
#include "splash_tower.h"
#include "unit.h"
#include <string>
#include "../team.h"

using namespace std;

SplashTower::SplashTower(	int uid, Point pos, int hp, int atkdmg, int atkrng,
							int atkspd, int percep, int atkcnt, int wall,
							Team * t, int spldmg, int splrng):
				Tower(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, wall)
				     ,team(t), splashDamage(spldmg), splashRange(splrng)
{
    //validation
}

/*------------------------------------------------------------------------------
-- FUNCTION:    Attack
--
-- DATE:        2013/03/12
--
-- DESIGNER:    Cody Rossiter
-- PROGRAMMER:  Cody Rossiter
--
-- INTERFACE:   void Attack(void)
--
-- RETURNS:     void
--
-- DESCRIPTION: Function damages pTarget and then goes through enemy units and
--              players. If they are in splash damage range (near pTarget), then
--              they are also damaged.
------------------------------------------------------------------------------*/
void SplashTower::Attack(void)
{
    /* check if we can attack */
    if( attackCount++ < attackSpeed )
        return;
        
    /* reset attackCount and damage pTargetd */
    attackCount = 0;
    pTarget->health -= attackDamage;
    
    /* check for nearby creeps & damage them */
    for (size_t i = 0; i < team->creeps.size(); ++i)
    {
        /* if creep is in range AND is alive AND is not our target (to prevent hitting one target twice) */
        if( inRange( pTarget->getPos(), team->creeps[i].getPos(), splashRange ) 
            && team->creeps[i].health > 0 
            && pTarget->id != team->creeps[i].id ) 
        {
            team->creeps[i].health -= splashDamage;
        }
    }
    
    /* check for nearby players & damage them */
    for (size_t i = 0; i < team->players.size(); ++i)
    {
        /* if player is in range AND is alive AND is not our target (to prevent hitting one target twice) */
        if( inRange( pTarget->getPos(), team->players[i].getPos(), splashRange )
            && team->players[i].health > 0
            && pTarget->id != team->players[i].id ) 
        {
            team->players[i].health -= splashDamage;
        }
    }
}
