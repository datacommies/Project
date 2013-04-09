/*------------------------------------------------------------------------------
-- FILE:        projectile.cpp
--
-- DATE:        2013/03/11
--
-- MAINTAINERS: Nick Raposo
--
-- FUNCTIONS:   Attack
--              Update
--              Move            
--
-- DESCRIPTION: Base implementation, not complete.
------------------------------------------------------------------------------*/
#include "projectile.h"
#include "unit.h"
#include "creep.h"

using namespace std;

Projectile::Projectile(int uid, Point pos, int hp, int atkdmg, int atkrng,
    int atkspd, int percep, int atkcnt, int spd, Direction direct,
    Point* path, int movespeed): Creep(uid, pos, hp, atkdmg, atkrng, atkspd,
    percep, atkcnt,spd, direct)
{
    //validation
    //psaved is initialized to NULL so that the game doesn't crash!
}
/*------------------------------------------------------------------------------
-- FUNCTION:    Attack
--
-- DATE:        2013/04/05
--
-- DESIGNER:    Nick Raposo
-- PROGRAMMER:  Nick Raposo
--
-- INTERFACE:   void Attack(void)
--
-- RETURNS:     void 
--
-- DESCRIPTION:
--
------------------------------------------------------------------------------*/
void Projectile::Attack(void) 
{
    pTarget->health -= attackDamage;
}
/*------------------------------------------------------------------------------
-- FUNCTION:    CheckTarget
--
-- DATE:        2013/04/05
--
-- DESIGNER:    Nick Raposo
-- PROGRAMMER:  Nick Raposo
--
-- INTERFACE:   void CheckTarget(void) 
--
-- RETURNS:     void 
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void Projectile::CheckTarget(void) 
{
    if(pTarget->health <= 0)
        pTarget = NULL;
}
/*------------------------------------------------------------------------------
-- FUNCTION:    Update
--
-- DATE:        2013/04/05
--
-- DESIGNER:    Nick Raposo, Cody Rossiter
-- PROGRAMMER:  Nick Raposo
--
-- INTERFACE:   void Update(void) 
--
-- RETURNS:     void 
--
-- DESCRIPTION:

------------------------------------------------------------------------------*/
void Projectile::Update(void) 
{
    /* If we have a Target, check their status. */
    if(pTarget != NULL)
        CheckTarget();
    /* If we found a new Target, and they are in range.. */
    if(pTarget != NULL) 
    {
        if(inRange(position, pTarget->getPos(), attackRange))
        {
            Attack();
            health = 0;
        }
        else
        {
            Move(pTarget->getPos());
        }
    }
}
