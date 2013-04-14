/*------------------------------------------------------------------------------
-- FILE:        tower.cpp
--
-- DATE:        2013/03/26
--
-- MAINTAINERS: Callum Styan, Behnam Bastami, Aaron Lee, David Czech
--              Steve Lo, Kevin Tangeman
--
-- FUNCTIONS:   Tower constructor
--              serializeTower
--
-- DESCRIPTION: File contains implementation for the Tower class. Tower will be
--              a base class that specific tower types inherit from.
------------------------------------------------------------------------------*/
#include "tower.h"
#include "unit.h"
#include <string>

using namespace std;

//old ctor - Callum
Tower::Tower(int uid, Point pos, int hp, int atkdmg, int atkrng,
            int atkspd, int percep, int atkcnt, int wall):
            Unit(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt), wallArmour_(wall)
{
    //validation
}

/*------------------------------------------------------------------------------
-- FUNCTION:    Tower
--
-- DATE:        March 26, 2013
--
-- DESIGNER:    Callum Styan, Kevin Tangeman, Steve Lo
-- PROGRAMMER:  Callum Styan, Kevin Tangeman, Steve Lo
--
-- INTERFACE:   Tower::Tower(int uid, int side, Point pos, int hp, int atkdmg, int atkrng,
--                          int atkspd, int percep, int atkcnt, int wall):
--                          Unit(uid, side, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt),
--                          wallArmour_(wall)
--
-- RETURNS:     none
--
-- DESCRIPTION: Creates a new Tower object.  Default values are given.
--              
--              The unit id must be specified, it is generated server side.
--              
--              The starting position must be specified, this should be the first value
--              of the path it is in.
------------------------------------------------------------------------------*/
Tower::Tower(int uid, int side, Point pos, int hp, int atkdmg, int atkrng,
            int atkspd, int percep, int atkcnt, int wall):
            Unit(uid, side, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt), wallArmour_(wall)
{
    //validation
}

/*------------------------------------------------------------------------------
-- FUNCTION:    serializeTower
--
-- DATE:        2013/03/11
--
-- DESIGNER:    Behnam Bastami, Aaron Lee, David Czech
-- PROGRAMMER:  Behnam Bastami, Aaron Lee
--
-- INTERFACE:   Unit::serializeTower()
--
-- RETURNS:     string, the serialized Tower
--
-- DESCRIPTION: Converts the Tower classes members into one string to be sent over
-- the network between client and server.  Uses the unit serialize function.
------------------------------------------------------------------------------*/
string Tower::serializeTower(){
    string s;
    s = Unit::serializeUnit();

    tower_t t;
    t.wallArmour = wallArmour_;
    
    s += string((const char*)&t, sizeof(t));
    
    return s;
}
