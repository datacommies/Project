/*------------------------------------------------------------------------------
-- FILE:        unit.cpp
--
-- DATE:        2013/03/11
--
-- MAINTAINERS: Callum Styan, Nick Raposo, Cody Rossiter, Behnam Bastami, 
-- 				Chris Porter, Kevin Tangeman
--
-- FUNCTIONS:   Unit constructor
--              inRange
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


//old constructor - Callum
Unit::Unit(int uid, Point pos, int hp, int atkdmg,
           int atkrng, int atkspd, int percep, int atkcnt):
           id(uid), position(pos), health(hp), attackDamage(atkdmg), attackRange(atkrng),
           attackSpeed(atkspd), perception(percep), attackCount(atkcnt), pTarget(NULL)
{
    //any required validation
}

/*------------------------------------------------------------------------------
-- FUNCTION:    Unit constructor
--
-- DATE:        March 26, 2013
--
-- DESIGNER:    Callum Styan, Steve Lo, Kevin Tangeman
-- PROGRAMMER:  Callum Styan, Steve Lo, Kevin Tangeman
--
-- INTERFACE:   Unit::Unit(int uid, int side, Point pos, int hp, int atkdmg,
--                         int atkrng, int atkspd, int percep, int atkcnt)
--
-- RETURNS:     a new Unit object
--
-- DESCRIPTION: Builds a new Unit
--
-- NOTES: all parameters after Point pos
------------------------------------------------------------------------------*/
Unit::Unit(int uid, int side, Point pos, int hp, int atkdmg,
           int atkrng, int atkspd, int percep, int atkcnt):
           id(uid), team(side), position(pos), health(hp), attackDamage(atkdmg), attackRange(atkrng),
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

//Everything below here, except serialize, is AI code, will probably be need to be
//over ridden in the player class once we write that

/*------------------------------------------------------------------------------
-- FUNCTION:    hasWeakness
--
-- DATE:        2013/04/05
--
-- DESIGNER:    Chris Porter
-- PROGRAMMER:  Chris Porter
--
-- INTERFACE:   bool hasWeakness(int iAttack, int iTarget) 
--
-- RETURNS:     bool: returns true if they are weaker.
--
-- DESCRIPTION: Checks if a current unit has an advantage over the target. 
------------------------------------------------------------------------------*/
bool Unit::hasWeakness(int iAttack, int iTarget) {
    /*if(iAttack == iTarget + 1 % ELEMENT_COUNT)
        return true;
    return false;*/
	return false;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    hasStrength
--
-- DATE:        2013/04/05
--
-- DESIGNER:    Chris Porter
-- PROGRAMMER:  Chris Porter
--
-- INTERFACE:   bool hasStrength(int iAttack, int iTarget) 
--
-- RETURNS:     bool: returns true if they are stronger.
--
-- DESCRIPTION: Checks if a unit has an advantage over the current. 
------------------------------------------------------------------------------*/
bool Unit::hasStrength(int iAttack, int iTarget) {
    /*if(iAttack == iTarget - 1 % ELEMENT_COUNT)
        return true;
    return false;*/
	return false;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    Attack
--
-- DATE:        2013/04/05
--
-- DESIGNER:    Chris Porter
-- PROGRAMMER:  Chris Porter
--
-- INTERFACE:   void Attack(void)
--
-- RETURNS:     void 
--
-- DESCRIPTION: Attack will attempt to attack the target. If they the target
--				has a weakness to the current unit's element, it will do a 
--				bonus 75% damage. If they are a weaker type, they will do only
--				25% their base damage. Otherwise, they will do 100% their damage.
------------------------------------------------------------------------------*/
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
        //pTarget = NULL;
    }
}

/*------------------------------------------------------------------------------
-- FUNCTION:    Find Target
--
-- DATE:        2013/04/05
--
-- DESIGNER:    Nick Raposo, Chris Porter
-- PROGRAMMER:  Nick Raposo, Chris Porter
--
-- INTERFACE:   void FindTarget(Team *team)
--
-- RETURNS:     void 
--
-- DESCRIPTION: Finds another target through the other team's list of creeps,
--				towers and players. 
------------------------------------------------------------------------------*/
void Unit::FindTarget(Team *team) {
    /* If in range and alive, set as target. */
    for (size_t i = 0; i < team->creeps.size(); ++i)
    {
        if( inRange( position, team->creeps[i]->getPos(), perception ) && team->creeps[i]->health > 0 ) {
            pTarget = team->creeps[i];
            return;
        }
    }

    for (size_t i = 0; i < team->towers.size(); ++i)
    {
        if( inRange( position, team->towers[i]->getPos(), perception ) && team->towers[i]->health > 0 ) {
            pTarget = team->towers[i];
            return;
        }
    }

    for (size_t i = 0; i < team->players.size(); ++i)
    {
        if( inRange( position, team->players[i]->getPos(), perception ) && team->players[i]->health > 0 ) {
            pTarget = team->players[i];
            return;
        }
    }
}

/*------------------------------------------------------------------------------
-- FUNCTION:    CheckTarget
--
-- DATE:        2013/04/05
--
-- DESIGNER:    Chris Porter
-- PROGRAMMER:  Chris Porter
--
-- INTERFACE:   void CheckTarget(void)
--
-- RETURNS:     void 
--
-- DESCRIPTION: Checks if a target is within the current unit's perception 
--				and if they are still alive. 
------------------------------------------------------------------------------*/
void Unit::CheckTarget(void) {
    /* Target is DEAD. */
    if( pTarget->health <= 0 )
        pTarget = NULL;
    /* Or Target is out of range.  */
    else if (inRange(position, pTarget->getPos(), perception) == false )
        pTarget = NULL;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    Update
--
-- DATE:        2013/04/05
--
-- DESIGNER:    Chris Porter
-- PROGRAMMER:  Chris Porter
--
-- INTERFACE:   void Update(Team& team)
--
-- RETURNS:     void 
--
-- DESCRIPTION: Logical steps for a unit to go through each turn to either
--				attack an existing target, or find a new one.
------------------------------------------------------------------------------*/
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
    }
}

/*------------------------------------------------------------------------------
-- FUNCTION:    Rotate
--
-- DATE:        2013/04/05
--
-- DESIGNER:    Chris Porter
-- PROGRAMMER:  Chris Porter
--
-- INTERFACE:   float Rotate(Point pt)
--
-- RETURNS:     float: the degrees of the needed rotation. 
--
-- DESCRIPTION: A function to calculate the rotation between two points.
--				Used for graphics to make towers look at their targets.
------------------------------------------------------------------------------*/
void Unit::Rotate(Point pt) {
    fRotate = atan2( (float)position.y - pt.y, (float)position.x - pt.x );
}

/*------------------------------------------------------------------------------
-- FUNCTION:    serializeUnit
--
-- DATE:        2013/03/11
--
-- DESIGNER:    Behnam Bastami, Aaron Lee
-- PROGRAMMER:  Behnam Bastami, Aaron Lee, David Czech
--
-- INTERFACE:   Unit::serializeUnit()
--
-- RETURNS:     string, the serialized Unit
--
-- DESCRIPTION: Converts the Unit classes members into one string to be sent over
-- the network between client and server. 
------------------------------------------------------------------------------*/
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
