/*------------------------------------------------------------------------------
-- FILE:        mobile_unit.cpp
--
-- DATE:        March 11, 2013
--
-- MAINTAINERS: Callum Styan
--
-- FUNCTIONS:   MobileUnit constructor
--              serializeUnit
--
-- DESCRIPTION: File contains implementation for the Mobile Unit class. Mobile Unit 
--              will be a base class that Creep and Player inherit from. 
------------------------------------------------------------------------------*/
#include "mobile_unit.h"
#include <string>

using namespace std;

//old constructor - Callum
MobileUnit::MobileUnit(int uid, Point pos, int hp, int atkdmg, int atkrng,
                       int atkspd, int percep, int atkcnt, int spd, Direction direct):
                       Unit(uid, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt), moveSpeed(spd), direction(direct)
{
    //validation
}


/*------------------------------------------------------------------------------
-- FUNCTION:    MobileUnit - constructor
--
-- DATE:        March 26, 2013
--
-- DESIGNER:    Callum Styan
-- PROGRAMMER:  Callum Styan
--
-- INTERFACE:   MobileUnit(int uid, int side, Point pos, int hp=100, int atkdmg=0, int atkrng=0,
--                         int atkspd=0, int percep=0, int atkcnt=0, int movespeed = 10, 
--                         Direction direct = UP)
--
-- RETURNS:     a new MobileUnit
--
-- DESCRIPTION: Creates a new MobileUnit object.  Default values are given.
--              
--              The unit id must be specified, it is generated server side.
--              
--              The team must be sepcified, either 0 or 1.
--              
--              The starting position must be specified.
--              From the map, each lane has a starting point, and each player has
--              a defined starting point.
------------------------------------------------------------------------------*/
MobileUnit::MobileUnit(int uid, int side, Point pos, int hp, int atkdmg, int atkrng,
           int atkspd, int percep, int atkcnt, int movespeed, Direction direct):
           Unit(uid, side, pos, hp, atkdmg, atkrng, atkspd, percep, atkcnt), moveSpeed(movespeed), direction(direct)
{
    //validation?
}

/*------------------------------------------------------------------------------
-- FUNCTION:    serializeMobileUnit
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
-- DESCRIPTION: Converts the MobileUnit classes members into one string to be sent over
-- the network between client and server. 
------------------------------------------------------------------------------*/
string MobileUnit::serializeMobileUnit()
{
    string s = Unit::serializeUnit();
    
    mobileunit_t m;
    m.speed = moveSpeed;
    m.direction = direction;
    s += string((char*)&m, sizeof(mobileunit_t));
    return s;
}
