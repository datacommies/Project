/*------------------------------------------------------------------------------
-- FILE:        unit.cpp
--
-- DATE:        2013/03/11
--
-- MAINTAINERS: Chris Porter, Nick Raposo, Cody Rossiter
--
-- FUNCTIONS:   inRange
--              hasWeakness
--              hasStrength
--              Attack
--              FindTarget
--              CheckTarget
--              Update
--              Rotate
--              serializeUnit
--
-- DESCRIPTION: File contains implementation for the Unit class. Unit will be
--              a base class that Tower and MobileUnit inherit from. 
------------------------------------------------------------------------------*/
#include "unit.h"
#include <string>
#include <vector>
#include <math.h>
#include "../team.h"

using namespace std;

Unit::Unit(int uid, Point pos, int hp, int atkdmg,
           int atkrng, int atkspd, int percep, int atkcnt):
           id(uid), position(pos), health(hp), attackDamage(atkdmg), attackRange(atkrng),
           attackSpeed(atkspd), perception(percep), attackCount(atkcnt), pTarget(NULL)
{
    //any required validation
    printf("Inside unit constructor, x:%d y:%d\n", position.x, position.y);
}


Unit::Unit(int uid, int side, Point pos, int hp, int atkdmg,
           int atkrng, int atkspd, int percep, int atkcnt):
           id(uid) team(side), position(pos), health(hp), attackDamage(atkdmg), attackRange(atkrng),
           attackSpeed(atkspd), perception(percep), attackCount(atkcnt), pTarget(NULL)
{
    //any required validation
    printf("Inside unit constructor, x:%d y:%d\n", position.x, position.y);
}

/*------------------------------------------------------------------------------
-- FUNCTION:    inRange
--
-- DATE:        2013/03/11
--
-- DESIGNER:    Chris Porter, Nick Raposo
-- PROGRAMMER:  Chris Porter, Nick Raposo, Cody Rossiter
--
-- INTERFACE:   bool inRange(Point p1, Point p2, int distance)
--
-- RETURNS:     boolean: If the target is out of range 
--                       (target distance > distance) return false, otherwise, 
--                       return true
--
-- DESCRIPTION: Function uses the Pythagorean Theorem to calculate the
--              the targets distance. 
------------------------------------------------------------------------------*/
bool Unit::inRange(Point p1, Point p2, int distance) {
    double a = pow(abs(p1.x - p2.x), 2);
    double b = pow(abs(p1.y - p2.y), 2);
    
    if (sqrt(a + b) > distance)
    {
        return false;
    }
    
    return true;
}

/*
* Used to check if the target has a weakness to the Unit's element.
*/
bool Unit::hasWeakness(int iAttack, int iTarget) {
    /*if(iAttack == iTarget + 1 % ELEMENT_COUNT)
        return true;
    return false;*/
	return false;
}

/*
* Used to check if the target has a weakness to the Unit's element.
*/
bool Unit::hasStrength(int iAttack, int iTarget) {
    /*if(iAttack == iTarget - 1 % ELEMENT_COUNT)
        return true;
    return false;*/
	return false;
}

/*
* Attacks the current target. If it has a weakness, it will apply a 75% damage bonus.
* QUESTION - If we attack a element we have a weakness against, do we do LESS damage? 
*/
void Unit::Attack(void) {
    if( attackCount++ < attackSpeed )
        return;

    attackCount = 0;
    if( hasWeakness( iElement, pTarget->iElement ) )
        pTarget->health -= attackDamage * 1.75;
    else if( hasStrength(iElement, pTarget->iElement) )
        pTarget->health -= attackDamage * 0.25;
    else
        pTarget->health -= attackDamage;

    if( pTarget->health <= 0 ) {
        //the game class does not exist, foos!
        //Game::removeUnit( pTarget, pTarget->iTeam );
    }
}

/*
* Finds the next target, will loop through all enemies until one target is found.
* TODO - Add priority. ( Attack players over creeps )
*/
void Unit::FindTarget(Team *team) {
    /* If in range and alive, set as target. */
    for (size_t i = 0; i < team->creeps.size(); ++i)
    {
        if( inRange( position, team->creeps[i].getPos(), perception ) && team->creeps[i].health > 0 ) {
            pTarget = (Unit*)&team->creeps[i];
            return;
        }
    }

    for (size_t i = 0; i < team->towers.size(); ++i)
    {
        if( inRange( position, team->towers[i].getPos(), perception ) && team->towers[i].health > 0 ) {
            pTarget = (Unit*)&team->towers[i];
            return;
        }
    }

    for (size_t i = 0; i < team->players.size(); ++i)
    {
        if( inRange( position, team->players[i].getPos(), perception ) && team->players[i].health > 0 ) {
            pTarget = &team->players[i];
            return;
        }
    }
}

/*
* Check if the target is alive and in range. Set the pTarget to NULL if either are true.
*/
void Unit::CheckTarget(void) {
    /* Target is DEAD. */
    if( pTarget->health <= 0 )
        pTarget = NULL;
    /* Or Target is out of range.  */
    else if (inRange(position, pTarget->getPos(), perception) == false )
        pTarget = NULL;
    
}

/*
* If we have an Unit target, attack.
*/
void Unit::Update(Team& team) {

    /* If we have a Target, check their status. */
    if( pTarget != NULL )
        CheckTarget();

    /* Search for Target. */
    if( pTarget == NULL )
        FindTarget(&team);

    /* If we found a new Target, and they are in range.. */
    if( pTarget != NULL ) {
        Attack();
        Rotate( pTarget->getPos() );
    }
}

/*
* Rotate towards the target. Used for either a path, or a target. 
*/
float Unit::Rotate(Point pt) {
    return atan2( (float)position.y - pt.y, (float)position.x - pt.x );
}


string Unit::serializeUnit()
{
    unit_t u;
    
    u.head.type = MSG_CREATE_UNIT;
    u.unit_type = getType();
    u.head.size = getSize();
    u.id = id;
    u.team = team;
    u.posx = position.x;
    u.posy = position.y;
    u.health = health;
    u.attackDamage = attackDamage;
    u.attackRange = attackRange;
    u.attackSpeed = attackSpeed;
    u.perception = perception;
    u.attackCount = attackCount;
    return string((char*)&u, sizeof(unit_t));
}
