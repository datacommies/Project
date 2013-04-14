/*------------------------------------------------------------------------------
-- FILE:        castle.cpp
--
-- DATE:        2013/03/26
--
-- MAINTAINERS: Callum Styan, Nick Raposo, Cody Rossiter, Behnam Bastami, 
--              Chris Porter, Kevin Tangeman, Steve Lo
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

#include "castle.h"
#include "tower.h"
#include <string>

using namespace std;


//old ctor - Callum
Castle::Castle(int uid, Point pos, int hp, int atkdmg, int atkrng,
    int atkspd, int percep, int atkcnt, int wall, int cid):
    Tower(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, wall), 
    clientID_(cid)
{
    // validation
}

/*------------------------------------------------------------------------------
-- FUNCTION:    Castle - constructor
--
-- DATE:        March 26, 2013
--
-- DESIGNER:    Kevin Tangeman
-- PROGRAMMER:  Kevin Tangeman, Steve Lo
--
-- INTERFACE:   Castle(int uid, int cid, int side, Point pos, int hp, int atkdmg, int atkrng,
--              int atkspd, int percep, int atkcnt, int wall):
--              Tower(uid, side, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, wall), 
--              clientID_(cid)
--
--              uid: unit id generated by the server
--              pos: starting position when you call the ctor
--
-- RETURNS:     a new Castle object
--
-- DESCRIPTION: Creates a new Castle object.  Default values are given.
--              
--              The unit id must be specified, it is generated server side.
------------------------------------------------------------------------------*/
Castle::Castle(int uid, int cid, int side, Point pos, int hp, int atkdmg, int atkrng,
    int atkspd, int percep, int atkcnt, int wall):
    Tower(uid, side, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt, wall), 
    clientID_(cid)
{
    // validation
}