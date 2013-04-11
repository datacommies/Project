/*------------------------------------------------------------------------------
-- FILE:        electro_tower.cpp
--
-- DATE:        2013/03/11
--
-- MAINTAINERS: Nick Raposo
--
-- FUNCTIONS:   Attack
--              Update          
--
-- DESCRIPTION: Base function for electric attacks to target multiple units.
------------------------------------------------------------------------------*/
#include "electro_tower.h"
#include "unit.h"
#include <string>
#include "../team.h"

using namespace std;


ElectroTower::ElectroTower(int uid, Point pos, int hp, int atkdmg, int atkrng,
            int atkspd, int percep, int atkcnt, int wall):
            Tower(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, wall)
{
    //validation
    pendingDelete = false; // !!!
}

ElectroTower::ElectroTower(int uid, int side, Point pos, int hp, int atkdmg,
           int atkrng, int atkspd, int percep, int atkcnt, int wall):
           Tower(uid, side, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, wall)
{
    //any required validation
    pendingDelete = false;
}


/*------------------------------------------------------------------------------
-- FUNCTION:    ElectroTower::Attack
--
-- DATE:        March 26, 2013
--
-- DESIGNER:    Nick Raposo
-- PROGRAMMER:  Nick Raposo
--
-- INTERFACE:   void ElectroTower::Attack(Team* team)
--
-- RETURNS:     void
--
-- DESCRIPTION: Causes the ElectroTower to attack the enemy/enemies in range.
--              If more than one enemy unit is in range, the attack will chain
--              to the next closest enemy, repeating while there are enemy
--              units in range.
------------------------------------------------------------------------------*/
void ElectroTower::Attack(Team* team)
{
   if( attackCount++ < attackSpeed )
        return;
    int tempDamage = attackDamage * 3;
    Unit* temp[4] = {pTarget, pTarget, pTarget, pTarget};
    Unit* tempTarget;

    attackCount = 0;
    
    pTarget->health -= tempDamage;
    tempDamage /= 2;

    temp[0] = pTarget;
    tempTarget = pTarget;

    for(int j = 1; j < 4; j++)
    {
        for (size_t i = 0; i < team->creeps.size(); ++i)
        {

            if( inRange( tempTarget->getPos(), team->creeps[i]->getPos(), attackRange) && team->creeps[i]->health > 0) 
            {
                if(team->creeps[i]->id == temp[0]->id || 
                    team->creeps[i]->id == temp[1]->id || 
                    team->creeps[i]->id == temp[2]->id || 
                    team->creeps[i]->id == temp[3]->id)
                {
                    continue;
                }
                else
                {
                    tempTarget = team->creeps[i];
                    temp[j] = tempTarget;
                    tempTarget->health -= attackDamage;
                    tempDamage /= 2;
                    break;
                }       
            }
        }
    }
}


/*------------------------------------------------------------------------------
-- FUNCTION:    ElectroTower::Update
--
-- DATE:        March 26, 2013
--
-- DESIGNER:    Nick Raposo
-- PROGRAMMER:  Nick Raposo
--
-- INTERFACE:   void ElectroTower::Update(Team& team)
--
-- RETURNS:     void
--
-- DESCRIPTION: Updates the state of the tower.  If there is currently a target,
--              check the status of said target to determine the next action.
--              If there is no current target, search for a new target.  If we
--              found a new target, and they are in range, attack them.
------------------------------------------------------------------------------*/
