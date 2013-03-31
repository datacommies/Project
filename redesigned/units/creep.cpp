/*------------------------------------------------------------------------------
-- FILE:        creep.cpp
--
-- DATE:        March 11, 2013
--
-- MAINTAINERS: Callum Styan, Chris Porter, Nick Raposo
--
-- FUNCTIONS:   Creep
--              getTargetDirection
--              Update
--              Move   
--              serializeCreep         
--
-- DESCRIPTION: Base functions for creeps. Movement, updating and target
--                direction.
------------------------------------------------------------------------------*/
#include "unit.h"
#include "creep.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

//old constructor
Creep::Creep(int uid, Point pos, int hp, int atkdmg, int atkrng,
         int atkspd, int percep, int atkcnt, int spd, Direction direct,
         Point* path, int movespeed): MobileUnit(uid, pos, hp, atkdmg, atkrng, atkspd,
         percep, atkcnt, spd, direct), pPath(path), pSaved(NULL)
{
    //validation
    //psaved is initialized to NULL so that the game doesn't crash!
}

/*------------------------------------------------------------------------------
-- FUNCTION:    Creep - constructor
--
-- DATE:        March 26, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   Creep(int uid, int side, Point pos, Point* path, int hp = 100, int atkdmg = 10, int atkrng = 10,
                      int atkspd = 10, int percep = 10, int atkcnt = 30, int movespeed = 10,
                      Direct direct = Direction())

                uid: unit id generated by the server
                pos: starting position when you call the ctor
                path: pointer to all the points for the creeps pathing
--
-- RETURNS:     a new Creep object
--
-- DESCRIPTION: Creates a new Creep object.  Default values are given.
--              
--              The unit id must be specified, it is generated server side.
--              
--              The starting position must be specified, this should be the first value
--              of the path it is in.
--              
--              The *path must be specified, this stores the points for the lane that the
--              creep will move through.
------------------------------------------------------------------------------*/
Creep::Creep(int uid, int side, Point pos, Point* path, int hp, int atkdmg, int atkrng,
             int atkspd, int percep, int atkcnt, int movespeed, Direction direct):
             MobileUnit(uid, side, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, movespeed, direct),
             pPath(path)
{
    //any required validation
}

/*
* Function to return the difference in two points. Used for movement. 
*/
int Creep::getTargetDirection(int p1, int p2) {
    if(p1 < p2) /*Target is below or right. */
        return 1;
    else if (p1 > p2)  /* Target is above or left. */
        return -1;
    else /* Target on the same level. */
        return 0;
}
    

/*
* Check if we're at the next path point, if we are, update the path target.
* If we can find an attackable target, attack or move towards them.
* If not, move along the path. 
*/
void Creep::Update(Team& team) {
    /* Check if we are at the next path point.  */
    if(pPath->x == position.x && pPath->y == position.y) {
        nextPoint();
    }
    
    /*If we have a Target check their stats. */
    if(pTarget != NULL) 
        CheckTarget();
    
    /* Search for Target. */
    if(pTarget == NULL) {
        FindTarget(&team);
    if(pTarget != NULL && pSaved == NULL)
        pSaved = &position;
    
    }
    
    /* If we found a new Target. */
    if(pTarget != NULL){
        if(inRange(position, pTarget->position, attackRange))
            Attack();
        else 
            Move(pTarget->getPos());
        Rotate(pTarget->getPos());
    }
    else
    { /*No target. Move along path. */
        if(pSaved == 0)
            Move(*pPath);
        else
            Move(*pSaved);
        Rotate( *pPath );
    }
}

void Creep::Move( Point pt ) {
    position.x += getTargetDirection(position.x, pt.x) * moveSpeed;
    position.y += getTargetDirection(position.y, pt.y) * moveSpeed;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    serializeCreep
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
-- DESCRIPTION: Converts the Creep classes members into one string to be sent over
-- the network between client and server.  Uses the mobile unit serialize function.
------------------------------------------------------------------------------*/
string Creep::serializeCreep()
{
    string s = MobileUnit::serializeMobileUnit();
    return s;
}

