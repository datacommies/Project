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

MultiShotTower::MultiShotTower(	int uid, Point pos, int hp, int atkdmg, int atkrng,
int atkspd, int percep, int atkcnt, int wall,
Team * t, int mulsdmg, int mulsrng):
Tower(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, wall)
,team(t), multiShotDamage(mulsdmg), multiShotRange(mulsrng)
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
void MultiShotTower::Attack(void)
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
             // repeat three times 
             for(int j = 1; j < 3; j++)
             {
                  /* if creep is in range AND is alive AND is not our target (to prevent hitting one target twice) */
                  if( inRange( pTarget->getPos(), team->creeps[i].getPos(), multiShotRange )
                  && team->creeps[i].health > 0 && pTarget->id != team->creeps[i].id )
                  {
                      team->creeps[i].health -= multiShotDamage;
                  }
	    }
     }

     /* check for nearby players & damage them */
     for (size_t i = 0; i < team->players.size(); ++i)
     {
         // repeat three times 
         for(int j = 1; j < 3; j++)
         {
               /* if player is in range AND is alive AND is not our target (to prevent hitting one target twice) */
               if( inRange( pTarget->getPos(), team->players[i].getPos(), multiShotRange )
               && team->players[i].health > 0
               && pTarget->id != team->players[i].id )
               {
                    team->players[i].health -= multiShotDamage;
               }
         }
     }
    
    
}
