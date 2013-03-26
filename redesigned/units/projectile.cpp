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
/*
* Attacks the current target. If it has a weakness, it will apply a 75% damage bonus.
* QUESTION - If we attack a element we have a weakness against, do we do LESS damage? 
*/
void Projectile::Attack(void) 
{
    pTarget->health -= attackDamage;
}
/*
* Check if the target is alive and in range. Set the pTarget to NULL if either are true.
*/
void Projectile::CheckTarget(void) 
{
    /* Target is DEAD. */
    if(pTarget->health <= 0)
        pTarget = NULL;
}
/*
* If we have an Unit target, attack.
*/
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
            Rotate(pTarget->getPos());
            //I NEED TO DIE NOW
        }
        else
        {
            Move(pTarget->getPos());
        }
    }
}
